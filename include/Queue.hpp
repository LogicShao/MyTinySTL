#ifndef TINY_QUEUE_HPP
#define TINY_QUEUE_HPP

#include "List.hpp"
#include "Vector.hpp"
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

template <typename T> class Queue {
public:
  Queue() = default;
  Queue(const Queue &other) = default;
  Queue(Queue &&other) = default;
  Queue &operator=(const Queue &other) = default;
  Queue &operator=(Queue &&other) = default;
  ~Queue() = default;

  void push(const T &value) { m_list.push_back(value); }
  void push(T &&value) { m_list.push_back(std::move(value)); }

  void pop() { m_list.pop_front(); }

  T front() const { return m_list.front(); }
  T back() const { return m_list.back(); }

  std::size_t size() const { return m_list.size(); }

  bool empty() const { return m_list.empty(); }

  void clear() { m_list.clear(); }

private:
  forwardList<T> m_list;
};

template <typename T> class Priority_Queue {
public:
  Priority_Queue() = default;
  Priority_Queue(const Priority_Queue &other) = default;
  Priority_Queue(Priority_Queue &&other) = default;
  Priority_Queue &operator=(const Priority_Queue &other) = default;
  Priority_Queue &operator=(Priority_Queue &&other) = default;
  ~Priority_Queue() = default;

  void push(const T &value) {
    m_vector.push_back(value);
    _heapify_up(m_vector.size() - 1);
  }

  void push(T &&value) {
    m_vector.push_back(std::move(value));
    _heapify_up(m_vector.size() - 1);
  }

  void pop() {
    m_vector[0] = std::move(m_vector[m_vector.size() - 1]);
    m_vector.pop_back();
    _heapify_down(0);
  }

  T top() const { return m_vector[0]; }

  std::size_t size() const { return m_vector.size(); }

  bool empty() const { return m_vector.empty(); }

  void clear() { m_vector.clear(); }

private:
  void _heapify_up(std::size_t i) {
    if (i == 0) {
      return;
    }

    std::size_t parent = (i - 1) / 2;
    if (m_vector[i] < m_vector[parent]) {
      std::swap(m_vector[i], m_vector[parent]);
      _heapify_up(parent);
    }
  }

  void _heapify_down(std::size_t i) {
    std::size_t left = 2 * i + 1;
    std::size_t right = 2 * i + 2;
    std::size_t smallest = i;

    if (left < m_vector.size() && m_vector[left] < m_vector[smallest]) {
      smallest = left;
    }

    if (right < m_vector.size() && m_vector[right] < m_vector[smallest]) {
      smallest = right;
    }

    if (smallest != i) {
      std::swap(m_vector[i], m_vector[smallest]);
      _heapify_down(smallest);
    }
  }

  Vector<T> m_vector;
  std::size_t m_size;
};
} // namespace Tiny

#endif // TINY_QUEUE_HPP