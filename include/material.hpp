#ifndef MATERIAL_H
#define MATERIAL_H

#include "colour.hpp"
#include "hittable.hpp"
#include "rtweekend.hpp"

class material {
public:
  virtual ~material() = default;

  virtual bool scatter(const ray &r_in [[maybe_unused]],
                       const hit_record &rec [[maybe_unused]],
                       colour &attenuation [[maybe_unused]],
                       ray &scattered [[maybe_unused]]) const;
};

class lambertian : public material {
public:
  lambertian(const colour &albedo);

  bool scatter(const ray &r_in [[maybe_unused]], const hit_record &rec,
               colour &attenuation, ray &scattered) const override;

private:
  colour albedo;
};

class metal : public material {
public:
  metal(const colour &albedo, double fuzz);

  bool scatter(const ray &r_in, const hit_record &rec, colour &attenuation,
               ray &scattered) const override;

private:
  colour albedo;
  double fuzz;
};

class dielectric : public material {
public:
  dielectric(double refraction_index);

  bool scatter(const ray &r_in, const hit_record &rec, colour &attenuation,
               ray &scattered) const override;

private:
  // Refractive index in vacuum or air, or the ratio of the material's
  // refractive index over the refractive index of the enclosing media
  double refraction_index;

  static double reflectance(const double cosine,
                            const double refraction_index) {
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