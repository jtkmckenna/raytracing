#ifndef colour_H
#define colour_H

#include "vec3.hpp"

#include <iostream>

using colour = vec3;

void write_colour(std::ostream &out, const colour &pixel_colour) {
  auto r = pixel_colour.x();
  auto g = pixel_colour.y();
  auto b = pixel_colour.z();

  // Translate the [0,1] component values to the byte range [0,255].
  int rbyte = int(255.999 * r);
  int gbyte = int(255.999 * g);
  int bbyte = int(255.999 * b);

  // Write out the pixel colour components.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif