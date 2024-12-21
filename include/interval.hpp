#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
  double min, max;

  interval() : min(+infinity), max(-infinity) {} // Default interval is empty

  interval(double min, double max) : min(min), max(max) {}

  double size() CONST_FUNC { return max - min; }

  bool contains(double x) CONST_FUNC { return min <= x && x <= max; }

  bool surrounds(double x) CONST_FUNC { return min < x && x < max; }

  double clamp(double x) CONST_FUNC {
    if (x < min)
      return min;
    if (x > max)
      return max;
    return x;
  }

  static CONST_VAR interval empty, universe;
};

CONST_VAR interval interval::empty = interval(+infinity, -infinity);
CONST_VAR interval interval::universe = interval(-infinity, +infinity);

#endif