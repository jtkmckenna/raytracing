#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "rtweekend.hpp"

class vec3 {
public:
  double e[3];

  vec3();
  CONSTEXPR vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  CONSTEXPR double x() const { return e[0]; }
  CONSTEXPR double y() const { return e[1]; }
  CONSTEXPR double z() const { return e[2]; }

  CONSTEXPR vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  CONSTEXPR double operator[](const int i) const { return e[i]; }
  double &operator[](const int i);

  vec3 &operator+=(const vec3 &v);

  vec3 &operator*=(double t);

  vec3 &operator/=(double t);

  CONSTEXPR double length() const { return std::sqrt(length_squared()); }

  CONSTEXPR double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  bool near_zero() const;

  static vec3 random();

  static vec3 random(const double min, const double max);
};

// point3 is just an alias for vec3, but useful for geometric clarity in the
// code.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

CONSTEXPR_OR_INLINE vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

CONSTEXPR_OR_INLINE vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

CONSTEXPR_OR_INLINE vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

CONSTEXPR_OR_INLINE vec3 operator*(const double t, const vec3 &v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

CONSTEXPR_OR_INLINE vec3 operator*(const vec3 &v, const double t) {
  return t * v;
}

CONSTEXPR_OR_INLINE vec3 operator/(const vec3 &v, const double t) {
  return (1 / t) * v;
}

CONSTEXPR_OR_INLINE double dot(const vec3 &u, const vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

CONSTEXPR_OR_INLINE vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

CONSTEXPR_OR_INLINE vec3 unit_vector(const vec3 &v) { return v / v.length(); }

inline vec3 random_in_unit_disk() {
  while (true) {
    CONST_VAR auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
    if (p.length_squared() < 1)
      return p;
  }
}

inline vec3 random_unit_vector() {
  while (true) {
    CONST_VAR auto p = vec3::random(-1, 1);
    CONST_VAR auto lensq = p.length_squared();
    ASSUME(lensq >= 0);
    if (1e-160 < lensq && lensq <= 1)
      return p / sqrt(lensq);
  }
}

inline vec3 random_on_hemisphere(const vec3 &normal) {
  CONST_VAR vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}

CONSTEXPR_OR_INLINE vec3 reflect(const vec3 &v, const vec3 &n) {
  return v - 2 * dot(v, n) * n;
}

CONSTEXPR_OR_INLINE vec3 refract(const vec3 &uv, const vec3 &n,
                                 double etai_over_etat) {
  CONST_VAR auto cos_theta = std::fmin(dot(-uv, n), 1.0);
  CONST_VAR vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
  CONST_VAR double r_out_parallel_2 =
      std::fabs(1.0 - r_out_perp.length_squared());
  ASSUME(r_out_parallel_2 >= 0);
  CONST_VAR vec3 r_out_parallel = -std::sqrt(r_out_parallel_2) * n;
  return r_out_perp + r_out_parallel;
}

#endif