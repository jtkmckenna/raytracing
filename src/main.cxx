#include "rtweekend.hpp"

#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"

#include <iostream>

void help(const camera &cam) {

  std::clog << "Options:\n";
  std::clog << "  -h, --help\t\tShow this help message\n";
  std::clog << "  -w, --width\t\tSet image width (default: " << cam.image_width
            << " \n";
  std::clog << "  -s, --samples\t\tSet samples per pixel (default: "
            << cam.samples_per_pixel << ")\n";
  std::clog << "  -d, --depth\t\tSet max depth (default: " << cam.max_depth
            << ")\n";
  std::clog << std::flush;
}

int main(int argc, char **argv) {

  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1200;
  cam.samples_per_pixel = 500;
  cam.max_depth = 50;

  // Command line options
  for (int i = 1; i < argc; i++) {
    const std::string arg(argv[i]);
    if (arg == "-h" or arg == "--help") {
      std::clog << "Usage: " << argv[0] << " [-h]\n";
      help(cam);
      return 0;
    } else if (arg == "-w" or arg == "--width") {
      if (i + 1 < argc) {
        cam.image_width = std::stoi(argv[++i]);
        std::clog << "Setting width to " << cam.image_width << '\n';
      }
    } else if (arg == "-s" or arg == "--samples") {
      if (i + 1 < argc) {
        cam.samples_per_pixel = std::stoi(argv[++i]);
        std::clog << "Setting samples per pixel to " << cam.samples_per_pixel
                  << '\n';
      }
    } else if (arg == "-d" or arg == "--depth") {
      if (i + 1 < argc) {
        cam.max_depth = std::stoi(argv[++i]);
        std::clog << "Setting max depth to " << cam.max_depth << '\n';
      }
    } else {
      std::cerr << "Unknown option: " << arg << '\n';
      help(cam);
      return 1;
    }
  }

  // World

  hittable_list world;
  auto ground_material = std::make_shared<lambertian>(colour(0.5, 0.5, 0.5));
  world.add(
      std::make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        std::shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = colour::random() * colour::random();
          sphere_material = std::make_shared<lambertian>(albedo);
          world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = colour::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = std::make_shared<metal>(albedo, fuzz);
          world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = std::make_shared<dielectric>(1.5);
          world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = std::make_shared<dielectric>(1.5);
  world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<lambertian>(colour(0.4, 0.2, 0.1));
  world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<metal>(colour(0.7, 0.6, 0.5), 0.0);
  world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  cam.vfov = 20;
  cam.lookfrom = point3(13, 2, 3);
  cam.lookat = point3(0, 0, 0);
  cam.vup = vec3(0, 1, 0);

  cam.defocus_angle = 0.6;
  cam.focus_dist = 10.0;
  cam.render(world);
}
