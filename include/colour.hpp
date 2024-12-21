#ifndef colour_H
#define colour_H

#include "interval.hpp"
#include "vec3.hpp"

#include <iostream>

using colour = vec3;

void write_colour(std::ostream &out, const colour &pixel_colour) {
  auto r = pixel_colour.x();
  auto g = pixel_colour.y();
  auto b = pixel_colour.z();

  // Translate the [0,1] component values to the byte range [0,255].
  static const interval intensity(0.000, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  // Write out the pixel colour components.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif