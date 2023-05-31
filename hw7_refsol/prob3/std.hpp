#ifndef POLYNOMIAL_STD_HPP
#define POLYNOMIAL_STD_HPP

#include <algorithm>
#include <vector>
#include <iterator>
#include <type_traits>

class Polynomial {
  friend Polynomial operator*(const Polynomial &, const Polynomial &);
  friend bool operator==(const Polynomial &, const Polynomial &);

  std::vector<double> m_coeffs;

  static double isZero(double x) {
    static constexpr auto eps = 1e-8;
    return x < eps && -x < eps;
  }

  void adjust() {
    while (!m_coeffs.empty() && isZero(m_coeffs.back()))
      m_coeffs.pop_back();
    if (m_coeffs.empty())
      m_coeffs.push_back(0);
  }

 public:
  Polynomial() : m_coeffs(1, 0.0) {}

  template <
      typename InputIterator,
      typename = std::enable_if_t<std::is_base_of_v<
          std::input_iterator_tag,
          typename std::iterator_traits<InputIterator>::iterator_category>>>
  Polynomial(InputIterator begin, InputIterator end) : m_coeffs(begin, end) {
    adjust();
  }

  explicit Polynomial(std::vector<double> coeffs)
      : m_coeffs(std::move(coeffs)) {
    adjust();
  }

  int deg() const {
    return m_coeffs.size() - 1;
  }

  void setCoeff(std::size_t i, double x) {
    if (i >= m_coeffs.size())
      m_coeffs.resize(i + 1, 0);
    m_coeffs[i] = x;
    adjust();
  }
  double operator[](std::size_t i) const {
    return m_coeffs[i];
  }

  double operator()(double x) const {
    auto result = 0.0, tmp = 1.0;
    for (auto a : m_coeffs) {
      result += a * tmp;
      tmp *= x;
    }
    return result;
  }
  Polynomial derivative() const {
    if (deg() == 0)
      return {};
    std::vector coeffs(m_coeffs.size() - 1, 0.0);
    for (std::size_t i = 0; i != coeffs.size(); ++i)
      coeffs[i] = m_coeffs[i + 1] * (i + 1);
    return Polynomial(std::move(coeffs));
  }
  Polynomial integral() const {
    std::vector coeffs(m_coeffs.size() + 1, 0.0);
    for (std::size_t i = 1; i != coeffs.size(); ++i)
      coeffs[i] = m_coeffs[i - 1] / i;
    return Polynomial(std::move(coeffs));
  }

  Polynomial &operator+=(const Polynomial &rhs) {
    auto len = std::min(m_coeffs.size(), rhs.m_coeffs.size());
    for (std::size_t i = 0; i != len; ++i)
      m_coeffs[i] += rhs.m_coeffs[i];
    if (rhs.m_coeffs.size() > m_coeffs.size())
      m_coeffs.insert(m_coeffs.end(), rhs.m_coeffs.begin() + m_coeffs.size(),
                      rhs.m_coeffs.end());
    adjust();
    return *this;
  }
  Polynomial operator-() const {
    auto ret = *this;
    for (auto &a : ret.m_coeffs)
      a = -a;
    return ret;
  }
  Polynomial &operator-=(const Polynomial &rhs) {
    return *this += -rhs;
  }
  Polynomial &operator*=(const Polynomial &rhs) {
    return *this = *this * rhs;
  }
};

inline Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
  return Polynomial{lhs} += rhs;
}

inline Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) {
  return Polynomial{lhs} -= rhs;
}

Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) {
  Polynomial result;
  result.m_coeffs.resize(lhs.deg() + rhs.deg() + 1, 0);
  for (auto i = 0; i <= lhs.deg(); ++i)
    for (auto j = 0; j <= rhs.deg(); ++j)
      result.m_coeffs[i + j] += lhs[i] * rhs[j];
  result.adjust();
  return result;
}

inline bool operator==(const Polynomial &lhs, const Polynomial &rhs) {
  auto diff = lhs - rhs;
  return diff.deg() == 0 && Polynomial::isZero(diff[0]);
}
inline bool operator!=(const Polynomial &lhs, const Polynomial &rhs) {
  return !(lhs == rhs);
}

#endif // POLYNOMIAL_STD_HPP