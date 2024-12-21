#include "rtweekend.hpp"

#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"

#include <iostream>

double hit_sphere(const point3 &center, double radius, const ray &r) {
  vec3 oc = center - r.origin();
  auto a = r.direction().length_squared();
  auto h = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = h * h - a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (h - std::sqrt(discriminant)) / a;
  }
}

int main() {

  // Image
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // Calculate the image height, and ensure that it's at least 1.
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // World

  hittable_list world;
  auto material_ground = std::make_shared<lambertian>(colour(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<lambertian>(colour(0.1, 0.2, 0.5));
  auto material_left = std::make_shared<dielectric>(1.00 / 1.33);
  auto material_right = std::make_shared<metal>(colour(0.8, 0.6, 0.2), 1.0);

  world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0,
                                     material_ground));
  world.add(
      std::make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(
      std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(
      std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);
}
