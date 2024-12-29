#ifndef RAY_H
#define RAY_H

#include "rtweekend.hpp"
#include "vec3.hpp"

class ray {
public:
  ray();

  ray(const point3 &origin, const vec3 &direction);

  const point3 &origin() const;
  point3 &origin();
  const vec3 &direction() const;
  vec3 &direction();

  point3 at(const double t) const;

private:
  point3 orig;
  vec3 dir;
};

#endif