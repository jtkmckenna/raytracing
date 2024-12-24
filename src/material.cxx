

#include "material.hpp"
bool material::scatter(const ray &r_in [[maybe_unused]],
                       const hit_record &rec [[maybe_unused]],
                       colour &attenuation [[maybe_unused]],
                       ray &scattered [[maybe_unused]]) const {
  return false;
}

lambertian::lambertian(const colour &albedo) : albedo(albedo) {}

bool lambertian::scatter(const ray &r_in [[maybe_unused]],
                         const hit_record &rec, colour &attenuation,
                         ray &scattered) const {
  auto scatter_direction = rec.normal + random_unit_vector();

  // Catch degenerate scatter direction
  if (scatter_direction.near_zero())
    scatter_direction = rec.normal;

  scattered = ray(rec.p, scatter_direction);
  attenuation = albedo;
  return true;
}

metal::metal(const colour &albedo, double fuzz)
    : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

bool metal::scatter(const ray &r_in, const hit_record &rec, colour &attenuation,
                    ray &scattered) const {
  vec3 reflected = reflect(r_in.direction(), rec.normal);
  reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
  scattered = ray(rec.p, reflected);
  attenuation = albedo;
  return (dot(scattered.direction(), rec.normal) > 0);
}

dielectric::dielectric(double refraction_index)
    : refraction_index(refraction_index) {}

bool dielectric::scatter(const ray &r_in, const hit_record &rec,
                         colour &attenuation, ray &scattered) const {
  attenuation = colour(1.0, 1.0, 1.0);
  CONST_VAR double ri =
      rec.front_face ? (1.0 / refraction_index) : refraction_index;

  vec3 unit_direction = unit_vector(r_in.direction());
  CONST_VAR double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
  CONST_VAR double one_cos_theta_2 = 1.0 - cos_theta * cos_theta;
  ASSUME(one_cos_theta_2 >= 0);
  CONST_VAR double sin_theta = std::sqrt(one_cos_theta_2);

  CONST_VAR bool cannot_refract = ri * sin_theta > 1.0;
  vec3 direction;

  if (cannot_refract || reflectance(cos_theta, ri) > random_double())
    direction = reflect(unit_direction, rec.normal);
  else
    direction = refract(unit_direction, rec.normal, ri);

  scattered = ray(rec.p, direction);
  return true;
}
