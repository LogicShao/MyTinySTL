#ifndef TINY_SHARED_PTR_HPP
#define TINY_SHARED_PTR_HPP

#include <cstddef>
#include <utility>

namespace Tiny {
template <typename T> class RefCount {
private:
  T *m_ptr;
  std::size_t m_refCount;

public:
  RefCount(T *ptr = nullptr);
  RefCount(const RefCount &other) = delete;
  RefCount &operator=(const RefCount &other) = delete;
  RefCount(RefCount &&other) = delete;
  RefCount &operator=(RefCount &&other) = delete;
  ~RefCount();

  template <typename U> friend class SharedPtr;
};

template <typename T> class SharedPtr {
private:
  RefCount<T> *m_refCnt_ptr;

public:
  SharedPtr(T *ptr = nullptr);
  SharedPtr(const SharedPtr &other);
  SharedPtr(SharedPtr &&other);
  ~SharedPtr();

  SharedPtr &operator=(const SharedPtr &other);
  SharedPtr &operator=(SharedPtr &&other);

  T &operator*() const;
  T *operator->() const;
  T *get() const;

  std::size_t use_count() const;

  explicit operator bool() const { return m_refCnt_ptr != nullptr; }
};

template <typename T, typename... Args> SharedPtr<T> makeShared(Args &&...args);
} // namespace Tiny

template <typename T>
Tiny::RefCount<T>::RefCount(T *ptr) : m_ptr(ptr), m_refCount(1) {}

template <typename T> Tiny::RefCount<T>::~RefCount() {
  if (m_ptr != nullptr) {
    delete m_ptr;
  }
}

template <typename T>
Tiny::SharedPtr<T>::SharedPtr(T *ptr) : m_refCnt_ptr(new RefCount<T>(ptr)) {}

template <typename T>
Tiny::SharedPtr<T>::SharedPtr(const SharedPtr &other)
    : m_refCnt_ptr(other.m_refCnt_ptr) {
  ++m_refCnt_ptr->m_refCount;
}

template <typename T>
Tiny::SharedPtr<T>::SharedPtr(SharedPtr &&other)
    : m_refCnt_ptr(other.m_refCnt_ptr) {
  other.m_refCnt_ptr = nullptr;
}

template <typename T> Tiny::SharedPtr<T>::~SharedPtr() {
  if (m_refCnt_ptr != nullptr && --m_refCnt_ptr->m_refCount == 0) {
    delete m_refCnt_ptr;
  }
}

template <typename T>
Tiny::SharedPtr<T> &Tiny::SharedPtr<T>::operator=(const SharedPtr &other) {
  if (this != &other) {
    if (m_refCnt_ptr != nullptr && --m_refCnt_ptr->m_refCount == 0) {
      delete m_refCnt_ptr;
    }

    m_refCnt_ptr = other.m_refCnt_ptr;
    ++m_refCnt_ptr->m_refCount;
  }

  return *this;
}

template <typename T>
Tiny::SharedPtr<T> &Tiny::SharedPtr<T>::operator=(SharedPtr &&other) {
  if (this != &other) {
    if (m_refCnt_ptr != nullptr && --m_refCnt_ptr->m_refCount == 0) {
      delete m_refCnt_ptr;
    }

    m_refCnt_ptr = other.m_refCnt_ptr;
    other.m_refCnt_ptr = nullptr;
  }

  return *this;
}

template <typename T> T &Tiny::SharedPtr<T>::operator*() const {
  return *m_refCnt_ptr->m_ptr;
}

template <typename T> T *Tiny::SharedPtr<T>::operator->() const {
  return m_refCnt_ptr->m_ptr;
}

template <typename T> T *Tiny::SharedPtr<T>::get() const {
  return m_refCnt_ptr->m_ptr;
}

template <typename T> std::size_t Tiny::SharedPtr<T>::use_count() const {
  return m_refCnt_ptr->m_refCount;
}

template <typename T, typename... Args>
Tiny::SharedPtr<T> Tiny::makeShared(Args &&...args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif // TINY_SHARED_PTR_HPP