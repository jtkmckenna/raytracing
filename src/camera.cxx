#include "camera.hpp"
#include "rtweekend.hpp"

void camera::render(const hittable &world) {
  initialize();
  // Translate the [0,1] component values to the byte range [0,255].
  interval intensity(0.000, 0.999);

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; i++) {
      colour pixel_colour(0, 0, 0);
      for (int sample = 0; sample < samples_per_pixel; sample++) {
        CONST_VAR ray r = get_ray(i, j);
        pixel_colour += ray_colour(r, max_depth, world);
      }
      write_colour(std::cout, pixel_samples_scale * pixel_colour, intensity);
    }
  }

  std::clog << "\rDone.                 \n";
}

void camera::initialize() {
  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  center = lookfrom;

  // Determine viewport dimensions.
  CONST_VAR auto theta = degrees_to_radians(vfov);
  CONST_VAR auto h = std::tan(theta / 2);
  CONST_VAR auto viewport_height = 2 * h * focus_dist;
  CONST_VAR auto viewport_width =
      viewport_height * (double(image_width) / image_height);

  // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
  w = unit_vector(lookfrom - lookat);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  // Calculate the vectors across the horizontal and down the vertical
  // viewport edges.
  CONST_VAR vec3 viewport_u =
      viewport_width * u; // Vector across viewport horizontal edge
  CONST_VAR vec3 viewport_v =
      viewport_height * -v; // Vector down viewport vertical edge

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;
  // Calculate the location of the upper left pixel.
  CONST_VAR auto viewport_upper_left =
      center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Calculate the camera defocus disk basis vectors.
  CONST_VAR auto defocus_radius =
      focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
  defocus_disk_u = u * defocus_radius;
  defocus_disk_v = v * defocus_radius;
}

ray camera::get_ray(int i, int j) const {
  // Construct a camera ray originating from the defocus disk and directed at
  // a randomly sampled point around the pixel location i, j.

  CONST_VAR auto offset = sample_square();
  CONST_VAR auto pixel_sample = pixel00_loc +
                                ((i + offset.x()) * pixel_delta_u) +
                                ((j + offset.y()) * pixel_delta_v);

  CONST_VAR auto ray_origin =
      (defocus_angle <= 0) ? center : defocus_disk_sample();
  CONST_VAR auto ray_direction = pixel_sample - ray_origin;

  return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const {
  // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit
  // square.
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

point3 camera::defocus_disk_sample() const {
  // Returns a random point in the camera defocus disk.
  CONST_VAR auto p = random_in_unit_disk();
  return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

colour camera::ray_colour(const ray &r, int depth,
                          const hittable &world) const {
  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    return colour(0, 0, 0);
  hit_record rec;

  if (world.hit(r, interval(0.001, std::numeric_limits<double>::infinity()),
                rec)) {
    ray scattered;
    colour attenuation;
    if (rec.mat->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_colour(scattered, depth - 1, world);
    return colour(0, 0, 0);
  }

  CONST_VAR vec3 unit_direction = unit_vector(r.direction());
  CONST_VAR auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}
