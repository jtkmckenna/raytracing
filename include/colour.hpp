#ifndef colour_H
#define colour_H

#include "interval.hpp"
#include "rtweekend.hpp"
#include "vec3.hpp"

#include <iostream>

using colour = vec3;

inline double linear_to_gamma(CONST_VAR double linear_component) {
  if (linear_component > 0) {
    ASSUME(linear_component >= 0);
    return std::sqrt(linear_component);
  }
  return 0;
}

inline void write_colour(std::ostream &out, const colour &pixel_colour,
                         interval &intensity) {
  auto r = pixel_colour.x();
  auto g = pixel_colour.y();
  auto b = pixel_colour.z();

  // Apply a linear to gamma transform for gamma 2
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  // Write out the pixel colour components.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif