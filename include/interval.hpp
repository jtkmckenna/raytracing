#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.hpp"

class interval {
public:
  double min, max;

  interval();

  interval(const double min, const double max);

  double size() const;

  bool contains(const double x) const;

  bool surrounds(const double x) const;

  double clamp(const double x) const;
};

#endif