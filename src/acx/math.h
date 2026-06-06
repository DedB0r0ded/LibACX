#pragma once


#include <cmath>


namespace acx {


  // Floating-point double precision comparison
  inline bool is_close(double a, double b, double rel_tol = 1e-6,
    double abs_tol = 0.0) {
    double a_abs = std::abs(a);
    double b_abs = std::abs(b);
    return std::abs(a - b) <= std::max(rel_tol * std::max(a_abs, b_abs), abs_tol);
  }

  // Floating-point comparison
  inline bool is_close(float a, float b, float rel_tol = 1e-6,
    float abs_tol = 0.0) {
    float a_abs = std::abs(a);
    float b_abs = std::abs(b);
    return std::abs(a - b) <= std::max(rel_tol * std::max(a_abs, b_abs), abs_tol);
  }


}