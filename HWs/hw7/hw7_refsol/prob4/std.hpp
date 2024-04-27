#ifndef EXPR_STD_HPP
#define EXPR_STD_HPP

#include <memory>
#include <string>
#include <cmath>

class NodeBase {
 public:
  NodeBase() = default;
  virtual double eval(double x) const = 0;
  virtual double derivative(double x) const = 0;
  virtual std::string rep() const = 0;
  virtual ~NodeBase() = default;
};

class Expr {
  std::shared_ptr<NodeBase> m_ptr;

  Expr(std::shared_ptr<NodeBase> ptr) : m_ptr{ptr} {}

 public:
  Expr(double value);
  double eval(double x) const {
    return m_ptr->eval(x);
  }
  double derivative(double x) const {
    return m_ptr->derivative(x);
  }
  std::string rep() const {
    return m_ptr->rep();
  }

  static const Expr x;

  friend Expr operator-(const Expr &);
  friend Expr operator+(const Expr &);
  friend Expr operator+(const Expr &, const Expr &);
  friend Expr operator-(const Expr &, const Expr &);
  friend Expr operator*(const Expr &, const Expr &);
  friend Expr operator/(const Expr &, const Expr &);
  friend Expr sin(const Expr &);
  friend Expr cos(const Expr &);
  friend Expr tan(const Expr &);
  friend Expr exp(const Expr &);
  friend Expr log(const Expr &);
};

class Variable : public NodeBase {
  double eval(double x) const override {
    return x;
  }
  double derivative(double) const override {
    return 1;
  }
  std::string rep() const override {
    return "x";
  }
};

class Constant : public NodeBase {
  double m_value;

  double eval(double) const override {
    return m_value;
  }
  double derivative(double) const override {
    return 0;
  }
  std::string rep() const override {
    return std::to_string(m_value);
  }

 public:
  Constant(double value) : m_value{value} {}
};

class UnaryOperator : public NodeBase {
  char m_op;
  Expr m_operand;

  double eval(double x) const override {
    return m_op == '+' ? m_operand.eval(x) : -m_operand.eval(x);
  }
  double derivative(double x) const override {
    return m_op == '+' ? m_operand.derivative(x) : -m_operand.derivative(x);
  }
  std::string rep() const override {
    return m_op + ('(' + m_operand.rep() + ')');
  }

 public:
  UnaryOperator(char op, const Expr &operand) : m_op{op}, m_operand{operand} {}
};

class BinaryOperator : public NodeBase {
 protected:
  Expr m_left;
  Expr m_right;

 public:
  BinaryOperator(const Expr &left, const Expr &right)
      : m_left{left}, m_right{right} {}
};

class PlusOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  double eval(double x) const override {
    return m_left.eval(x) + m_right.eval(x);
  }
  double derivative(double x) const override {
    return m_left.derivative(x) + m_right.derivative(x);
  }
  std::string rep() const override {
    return '(' + m_left.rep() + ") + (" + m_right.rep() + ')';
  }
};

class MinusOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  double eval(double x) const override {
    return m_left.eval(x) - m_right.eval(x);
  }
  double derivative(double x) const override {
    return m_left.derivative(x) - m_right.derivative(x);
  }
  std::string rep() const override {
    return '(' + m_left.rep() + ") - (" + m_right.rep() + ')';
  }
};

class MultiplyOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  double eval(double x) const override {
    return m_left.eval(x) * m_right.eval(x);
  }
  double derivative(double x) const override {
    return m_left.derivative(x) * m_right.eval(x) +
           m_left.eval(x) * m_right.derivative(x);
  }
  std::string rep() const override {
    return '(' + m_left.rep() + ") * (" + m_right.rep() + ')';
  }
};

class DivideOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  double eval(double x) const override {
    return m_left.eval(x) / m_right.eval(x);
  }
  double derivative(double x) const override {
    auto right_val = m_right.eval(x);
    return (m_left.derivative(x) * right_val -
            m_left.eval(x) * m_right.derivative(x)) /
           (right_val * right_val);
  }
  std::string rep() const override {
    return '(' + m_left.rep() + ") / (" + m_right.rep() + ')';
  }
};

const Expr Expr::x{std::make_shared<Variable>()};

inline Expr::Expr(double value) : m_ptr{std::make_shared<Constant>(value)} {}

inline Expr operator-(const Expr &operand) {
  return {std::make_shared<UnaryOperator>('-', operand)};
}

inline Expr operator+(const Expr &operand) {
  return {std::make_shared<UnaryOperator>('+', operand)};
}

inline Expr operator+(const Expr &left, const Expr &right) {
  return {std::make_shared<PlusOp>(left, right)};
}

inline Expr operator-(const Expr &left, const Expr &right) {
  return {std::make_shared<MinusOp>(left, right)};
}

inline Expr operator*(const Expr &left, const Expr &right) {
  return {std::make_shared<MultiplyOp>(left, right)};
}

inline Expr operator/(const Expr &left, const Expr &right) {
  return {std::make_shared<DivideOp>(left, right)};
}

/// The following are not required but are interesting and helpful.

// These are *user-defined literal suffixes*, with which you can write
//   auto f = 2_ex * 3_ex;
// and it is equivalent to
//   auto f = Expr(2) * expr(3);
inline Expr operator""_ex(unsigned long long x) {
  return {static_cast<double>(x)};
}
inline Expr operator""_ex(long double x) {
  return {static_cast<double>(x)};
}

class Function : public NodeBase {
  using func_type = double(double);

 protected:
  func_type *m_funcPtr;
  std::string m_funcName;
  Expr m_arg;

 public:
  Function(func_type *ptr, std::string name, const Expr &arg)
      : m_funcPtr{ptr}, m_funcName{std::move(name)}, m_arg{arg} {}

  double eval(double x) const override {
    return m_funcPtr(x);
  }
  std::string rep() const override {
    return m_funcName + '(' + m_arg.rep() + ')';
  }
};

class SinFunc : public Function {
  double derivative(double x) const override {
    return std::cos(m_arg.eval(x)) * m_arg.derivative(x);
  }

 public:
  SinFunc(const Expr &arg) : Function(std::sin, "sin", arg) {}
};

class CosFunc : public Function {
  double derivative(double x) const override {
    return -std::sin(m_arg.eval(x)) * m_arg.derivative(x);
  }

 public:
  CosFunc(const Expr &arg) : Function(std::cos, "cos", arg) {}
};

class TanFunc : public Function {
  double derivative(double x) const override {
    return m_arg.derivative(x) / std::pow(std::cos(m_arg.eval(x)), 2);
  }

 public:
  TanFunc(const Expr &arg) : Function(std::tan, "tan", arg) {}
};

class ExpFunc : public Function {
  double derivative(double x) const override {
    return eval(x) * m_arg.derivative(x);
  }

 public:
  ExpFunc(const Expr &arg) : Function(std::exp, "exp", arg) {}
};

class LogFunc : public Function {
  double derivative(double x) const override {
    return m_arg.derivative(x) / m_arg.eval(x);
  }

 public:
  LogFunc(const Expr &arg) : Function(std::log, "log", arg) {}
};

inline Expr sin(const Expr &arg) {
  return {std::make_shared<SinFunc>(arg)};
}

inline Expr cos(const Expr &arg) {
  return {std::make_shared<CosFunc>(arg)};
}

inline Expr tan(const Expr &arg) {
  return {std::make_shared<TanFunc>(arg)};
}

inline Expr exp(const Expr &arg) {
  return {std::make_shared<ExpFunc>(arg)};
}

inline Expr log(const Expr &arg) {
  return {std::make_shared<LogFunc>(arg)};
}

#endif // EXPR_STD_HPP