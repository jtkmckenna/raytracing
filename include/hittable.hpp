#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "rtweekend.hpp"
#include "vec3.hpp"

class material;
class interval;

class hit_record {
public:
  point3 p;
  vec3 normal;
  std::shared_ptr<material> mat;
  double t;
  bool front_face;

  void set_face_normal(const ray &r, const vec3 &outward_normal);
};

class hittable {
public:
  virtual ~hittable() = default;

  virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};

#endif