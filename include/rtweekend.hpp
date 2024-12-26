#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// Common Macros

#if DISABLE_CONST_VAR
#define CONST_VAR
#else
#define CONST_VAR const
#endif

#ifdef DISABLE_NOEXCEPT
#define noexcept
#endif

#if DISABLE_ASSUME
#define ASSUME(expr) // no-op
#else
#if defined(_MSC_VER)
#define ASSUME(cond) __assume(cond)
#elif defined(__clang__)
#define ASSUME(cond) __builtin_assume(cond)
#elif defined(__GNUC__)
#define ASSUME(cond) [[assume(cond)]]
#endif
#endif

#if CONSTEXPR_NOT_INLINE
#define CONSTEXPR_OR_INLINE constexpr
#define CONSTEXPR constexpr
#else
#define CONSTEXPR_OR_INLINE inline
#define CONSTEXPR
#endif

// Constants

CONST_VAR double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility Functions

CONSTEXPR_OR_INLINE double degrees_to_radians(const double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double random_double(const double min, const double max) {
  // Returns a random real in [min,max).
  return min + (max - min) * random_double();
}

#endif
