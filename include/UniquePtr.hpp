#ifndef TINY_UNIQUE_PTR_HPP
#define TINY_UNIQUE_PTR_HPP

#include <utility>

namespace Tiny {
template <typename T> class DefaultDeleter {
public:
  void operator()(T *ptr) const;
};

template <typename T, typename Deleter = DefaultDeleter<T>> class UniquePtr {
private:
  T *m_ptr;
  Deleter m_deleter;

public:
  UniquePtr(T *ptr = nullptr, Deleter deleter = Deleter());
  UniquePtr(const UniquePtr &other) = delete;
  UniquePtr(UniquePtr &&other);
  ~UniquePtr();

  UniquePtr &operator=(const UniquePtr &other) = delete;
  UniquePtr &operator=(UniquePtr &&other);

  T &operator*() const;
  T *operator->() const;

  T *get() const;
  T *release();
  void reset(T *ptr = nullptr);

  explicit operator bool() const { return m_ptr != nullptr; }
};

template <typename T, typename Deleter = DefaultDeleter<T>, typename... Args>
UniquePtr<T, Deleter> makeUnique(Args &&...args) {
  return UniquePtr<T, Deleter>(new T(std::forward<Args>(args)...));
}
} // namespace Tiny

template <typename T> void Tiny::DefaultDeleter<T>::operator()(T *ptr) const {
  if (ptr) {
    delete ptr;
  }
}

template <typename T, typename Deleter>
Tiny::UniquePtr<T, Deleter>::UniquePtr(T *ptr, Deleter deleter)
    : m_ptr(ptr), m_deleter(deleter) {}

template <typename T, typename Deleter>
Tiny::UniquePtr<T, Deleter>::UniquePtr(UniquePtr &&other)
    : m_ptr(other.m_ptr), m_deleter(other.m_deleter) {
  other.m_ptr = nullptr;
}

template <typename T, typename Deleter>
Tiny::UniquePtr<T, Deleter>::~UniquePtr() {
  m_deleter(m_ptr);
}

template <typename T, typename Deleter>
Tiny::UniquePtr<T, Deleter> &
Tiny::UniquePtr<T, Deleter>::operator=(UniquePtr &&other) {
  if (this != &other) {
    m_deleter(m_ptr);
    m_ptr = other.m_ptr;
    m_deleter = other.m_deleter;
    other.m_ptr = nullptr;
  }

  return *this;
}

template <typename T, typename Deleter>
T &Tiny::UniquePtr<T, Deleter>::operator*() const {
  return *m_ptr;
}

template <typename T, typename Deleter>
T *Tiny::UniquePtr<T, Deleter>::operator->() const {
  return m_ptr;
}

template <typename T, typename Deleter>
T *Tiny::UniquePtr<T, Deleter>::get() const {
  return m_ptr;
}

template <typename T, typename Deleter>
T *Tiny::UniquePtr<T, Deleter>::release() {
  T *ptr = m_ptr;
  m_ptr = nullptr;
  return ptr;
}

template <typename T, typename Deleter>
void Tiny::UniquePtr<T, Deleter>::reset(T *ptr) {
  m_deleter(m_ptr);
  m_ptr = ptr;
}

#endif // TINY_UNIQUE_PTR_HPP