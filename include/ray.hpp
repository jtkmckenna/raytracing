#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
public:
  ray() {}

  ray(CONST_INPUT point3 &origin, CONST_INPUT vec3 &direction)
      : orig(origin), dir(direction) {}

  CONST_FUNC point3 &origin() CONST_FUNC { return orig; }
  CONST_FUNC vec3 &direction() CONST_FUNC { return dir; }

  point3 at(CONST_INPUT double t) CONST_FUNC { return orig + t * dir; }

private:
  point3 orig;
  vec3 dir;
};

#endif