#ifndef TINY_STACK_HPP
#define TINY_STACK_HPP

#include "Vector.hpp"
#include <utility>

namespace Tiny {
template <typename T> class Stack {
public:
  Stack() = default;
  Stack(const Stack<T> &) = default;
  Stack(Stack<T> &&) = default;
  Stack<T> &operator=(const Stack<T> &) = default;
  Stack<T> &operator=(Stack<T> &&) = default;
  ~Stack() = default;

  bool empty() const { return data.empty(); }

  std::size_t size() const { return data.size(); }

  const T top() const { return data.back(); }

  void push(const T &value) { data.push_back(value); }

  void push(T &&value) { data.push_back(std::move(value)); }

  void pop() { data.pop_back(); }

private:
  Vector<T> data;
};
} // namespace Tiny

#endif // TINY_STACK_HPP