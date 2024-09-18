#ifndef TINY_ARRAY_HPP
#define TINY_ARRAY_HPP

#include <cstddef>
#include <stdexcept>

namespace Tiny {
template <typename T, std::size_t N> class Array {
  static_assert(N > 0, "Array size must be greater than 0.");

private:
  T m_data[N];

public:
  Array() = default;
  Array(const Array &other) = default;
  Array(Array &&other) = default;
  Array &operator=(const Array &other) = default;
  Array &operator=(Array &&other) = default;
  ~Array() = default;

  T &operator[](std::size_t index);
  const T &operator[](std::size_t index) const;

  T *data();
  const T *data() const;

  std::size_t size() const;

  void fill(const T &value);

  T front() const;
  T back() const;

  T &at(std::size_t index);
  const T &at(std::size_t index) const;
};
} // namespace Tiny

template <typename T, std::size_t N>
T &Tiny::Array<T, N>::operator[](std::size_t index) {
  return m_data[index];
}

template <typename T, std::size_t N>
const T &Tiny::Array<T, N>::operator[](std::size_t index) const {
  return m_data[index];
}

template <typename T, std::size_t N> T *Tiny::Array<T, N>::data() {
  return m_data;
}

template <typename T, std::size_t N> const T *Tiny::Array<T, N>::data() const {
  return m_data;
}

template <typename T, std::size_t N>
std::size_t Tiny::Array<T, N>::size() const {
  return N;
}

template <typename T, std::size_t N>
void Tiny::Array<T, N>::fill(const T &value) {
  for (std::size_t i = 0; i < N; i++) {
    m_data[i] = value;
  }
}

template <typename T, std::size_t N> T Tiny::Array<T, N>::front() const {
  return m_data[0];
}

template <typename T, std::size_t N> T Tiny::Array<T, N>::back() const {
  return m_data[N - 1];
}

template <typename T, std::size_t N>
T &Tiny::Array<T, N>::at(std::size_t index) {
  if (index >= N) {
    throw std::out_of_range("Array::at");
  }

  return m_data[index];
}

template <typename T, std::size_t N>
const T &Tiny::Array<T, N>::at(std::size_t index) const {
  if (index >= N) {
    throw std::out_of_range("Array::at");
  }

  return m_data[index];
}

#endif // TINY_ARRAY_HPP