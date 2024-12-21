#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
public:
  double e[3];

  vec3() : e{0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() CONST_FUNC { return e[0]; }
  double y() CONST_FUNC { return e[1]; }
  double z() CONST_FUNC { return e[2]; }

  vec3 operator-() CONST_FUNC { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) CONST_FUNC { return e[i]; }
  double &operator[](int i) { return e[i]; }

  vec3 &operator+=(CONST_VAR vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3 &operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3 &operator/=(double t) { return *this *= 1 / t; }

  double length() CONST_FUNC { return std::sqrt(length_squared()); }

  double length_squared() CONST_FUNC {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  bool near_zero() CONST_FUNC {
    // Return true if the vector is close to zero in all dimensions.
    CONST_VAR auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
           (std::fabs(e[2]) < s);
  }

  static vec3 random() {
    return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
  }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the
// code.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream &operator<<(std::ostream &out, CONST_VAR vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(CONST_VAR vec3 &u, CONST_VAR vec3 &v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(CONST_VAR vec3 &u, CONST_VAR vec3 &v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(CONST_VAR vec3 &u, CONST_VAR vec3 &v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, CONST_VAR vec3 &v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(CONST_VAR vec3 &v, double t) { return t * v; }

inline vec3 operator/(CONST_VAR vec3 &v, double t) { return (1 / t) * v; }

inline double dot(CONST_VAR vec3 &u, CONST_VAR vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(CONST_VAR vec3 &u, CONST_VAR vec3 &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(CONST_VAR vec3 &v) { return v / v.length(); }

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
inline vec3 random_on_hemisphere(CONST_VAR vec3 &normal) {
  CONST_VAR vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}

inline vec3 reflect(CONST_VAR vec3 &v, CONST_VAR vec3 &n) {
  return v - 2 * dot(v, n) * n;
}

inline vec3 refract(CONST_VAR vec3 &uv, CONST_VAR vec3 &n,
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