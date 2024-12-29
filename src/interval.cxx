
#include "interval.hpp"

interval::interval()
    : min(+std::numeric_limits<double>::infinity()),
      max(-std::numeric_limits<double>::infinity()) {
} // Default interval is empty

interval::interval(const double min, const double max) : min(min), max(max) {}

double interval::size() const { return max - min; }

bool interval::contains(const double x) const { return min <= x && x <= max; }

bool interval::surrounds(const double x) const { return min < x && x < max; }

double interval::clamp(const double x) const {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}
