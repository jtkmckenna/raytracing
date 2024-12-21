#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.hpp"

#include <memory>
#include <vector>

class hittable_list : public hittable {
public:
  std::vector<std::shared_ptr<hittable>> objects;

  hittable_list() {}
  hittable_list(std::shared_ptr<hittable> object) { add(object); }

  void clear() { objects.clear(); }

  void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

  bool hit(CONST_INPUT ray &r, interval ray_t,
           hit_record &rec) CONST_FUNC override {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_t.max;

    for (CONST_VAR auto &object : objects) {
      if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }

    return hit_anything;
  }
};

#endif