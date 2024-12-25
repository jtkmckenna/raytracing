#include "ray.hpp"
ray::ray() {}

ray::ray(const point3 &origin, const vec3 &direction)
    : orig(origin), dir(direction) {}

const point3 &ray::origin() const { return orig; }
point3 &ray::origin() { return orig; }
const vec3 &ray::direction() const { return dir; }
vec3 &ray::direction() { return dir; }

point3 ray::at(const double t) const { return orig + t * dir; }
