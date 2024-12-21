#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"

class material;

class hit_record {
public:
  point3 p;
  vec3 normal;
  std::shared_ptr<material> mat;
  double t;
  bool front_face;

  void set_face_normal(CONST_VAR ray &r, CONST_VAR vec3 &outward_normal) {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
public:
  virtual ~hittable() = default;

  virtual bool hit(CONST_VAR ray &r, interval ray_t,
                   hit_record &rec) CONST_FUNC = 0;
};

#endif