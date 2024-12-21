#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.hpp"

class material {
public:
  virtual ~material() = default;

  virtual bool scatter(CONST_INPUT ray &r_in [[maybe_unused]],
                       CONST_INPUT hit_record &rec [[maybe_unused]],
                       colour &attenuation [[maybe_unused]],
                       ray &scattered [[maybe_unused]]) CONST_FUNC {
    return false;
  }
};

class lambertian : public material {
public:
  lambertian(CONST_INPUT colour &albedo) : albedo(albedo) {}

  bool scatter(CONST_INPUT ray &r_in [[maybe_unused]],
               CONST_INPUT hit_record &rec, colour &attenuation,
               ray &scattered) CONST_FUNC override {
    auto scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero())
      scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

private:
  colour albedo;
};

class metal : public material {
public:
  metal(CONST_INPUT colour &albedo, double fuzz)
      : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

  bool scatter(CONST_INPUT ray &r_in, CONST_INPUT hit_record &rec,
               colour &attenuation, ray &scattered) CONST_FUNC override {
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

private:
  colour albedo;
  double fuzz;
};

class dielectric : public material {
public:
  dielectric(double refraction_index) : refraction_index(refraction_index) {}

  bool scatter(CONST_INPUT ray &r_in, CONST_INPUT hit_record &rec,
               colour &attenuation, ray &scattered) CONST_FUNC override {
    attenuation = colour(1.0, 1.0, 1.0);
    CONST_VAR double ri =
        rec.front_face ? (1.0 / refraction_index) : refraction_index;

    vec3 unit_direction = unit_vector(r_in.direction());
    CONST_VAR double cos_theta =
        std::fmin(dot(-unit_direction, rec.normal), 1.0);
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

private:
  // Refractive index in vacuum or air, or the ratio of the material's
  // refractive index over the refractive index of the enclosing media
  double refraction_index;

  static double reflectance(CONST_INPUT double cosine,
                            CONST_INPUT double refraction_index) {
    // Use Schlick's approximation for reflectance.
    CONST_VAR auto r0 = (1 - refraction_index) / (1 + refraction_index);
    CONST_VAR auto r0_2 = r0 * r0;
#if DISABLE_POW
    CONST_VAR auto pow_5 = (1 - cosine) * (1 - cosine) * (1 - cosine) *
                           (1 - cosine) * (1 - cosine);
#else
    CONST_VAR auto pow_5 = std::pow(1 - cosine, 5);
#endif
    return r0_2 + (1 - r0_2) * pow_5;
  }
};

#endif