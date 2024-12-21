#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

// Common Headers

#include "colour.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#endif