#ifndef TINY_QUEUE_HPP
#define TINY_QUEUE_HPP

#include "List.hpp"
#include <cstddef>
#include <utility>

namespace Tiny {
template <typename T> class Deque {
public:
  Deque() = default;
  Deque(const Deque &other) = default;
  Deque(Deque &&other) = default;
  Deque &operator=(const Deque &other) = default;
  Deque &operator=(Deque &&other) = default;
  ~Deque() = default;

  void push_front(const T &value) { m_list.push_front(value); }
  void push_front(T &&value) { m_list.push_front(std::move(value)); }

  void push_back(const T &value) { m_list.push_back(value); }
  void push_back(T &&value) { m_list.push_back(std::move(value)); }

  void pop_front() { m_list.pop_front(); }
  void pop_back() { m_list.pop_back(); }

  T &front() { return m_list.front(); }
  const T &front() const { return m_list.front(); }

  T &back() { return m_list.back(); }
  const T &back() const { return m_list.back(); }

  std::size_t size() const { return m_list.size(); }

  bool empty() const { return m_list.empty(); }

  void clear() { m_list.clear(); }

private:
  List<T> m_list;
};

template <typename T> class Queue {};

template <typename T> class Priority_Queue {};
} // namespace Tiny

#endif // TINY_QUEUE_HPP