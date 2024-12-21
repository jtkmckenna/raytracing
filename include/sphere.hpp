#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable {
public:
  sphere(const point3 &center, double radius, std::shared_ptr<material> mat)
      : center(center), radius(std::fmax(0, radius)), mat(mat) {}

  bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
    vec3 oc = center - r.origin();
    CONST_VAR auto a = r.direction().length_squared();
    CONST_VAR auto h = dot(r.direction(), oc);
    CONST_VAR auto c = oc.length_squared() - radius * radius;

    CONST_VAR auto discriminant = h * h - a * c;
    if (discriminant < 0)
      return false;
    ASSUME(discriminant >= 0);
    CONST_VAR auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
      root = (h + sqrtd) / a;
      if (!ray_t.surrounds(root))
        return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    CONST_VAR vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;
    return true;
  }

private:
  point3 center;
  double radius;
  std::shared_ptr<material> mat;
};

#endif