#include "std.hpp"

#include <iostream>

int main() {
  auto &x = Expr::x;
  auto f = exp(x) * (sin(x) + 2_ex * cos(x));
  auto g = exp(x) * (-sin(x) + 3_ex * cos(x)); // g = f'
  std::cout << f.rep() << std::endl;
  std::cout << g.rep() << std::endl;
  std::cout << f.derivative(5) << std::endl;
  std::cout << g.eval(5) << std::endl;
  return 0;
}