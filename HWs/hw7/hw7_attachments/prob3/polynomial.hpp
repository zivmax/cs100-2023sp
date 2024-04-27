#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <vector>

class Polynomial {
  // `m_coeffs` stores the coefficients.
  // Note: This is not the unique correct implementation.
  // For example, you may separate the constant term from others,
  // and store the constant term using another variable.
  std::vector<double> m_coeffs;

  static auto isZero(double x) {
    static constexpr auto eps = 1e-8;
    return x < eps && -x < eps;
  }

  // Remove trailing zeros, to ensure that the coefficient of the term with
  // the highest order is non-zero.
  // Note that a polynomial should have at least one term, which is the
  // constant. It should not be removed even if it is zero.
  // If m_coeffs is empty, adjust() should also insert a zero into m_coeffs.
  void adjust() {
    // YOUR CODE HERE
  }

  // Other members ...
};

// Add non-member functions if you need.

#endif // POLYNOMIAL_HPP