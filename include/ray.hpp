#ifndef RAY_H
#define RAY_H

#include "rtweekend.hpp"
#include "vec3.hpp"

class ray {
public:
  ray() {}

  ray(const point3 &origin, const vec3 &direction)
      : orig(origin), dir(direction) {}

  const point3 &origin() const { return orig; }
  point3 &origin() { return orig; }
  const vec3 &direction() const { return dir; }
  vec3 &direction() { return dir; }

  point3 at(const double t) const { return orig + t * dir; }

private:
  point3 orig;
  vec3 dir;
};

#endif