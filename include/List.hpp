#ifndef TINY_LIST_HPP
#define TINY_LIST_HPP

#include <cstddef>
#include <ostream>

namespace Tiny {
template <typename T, std::size_t N> class tpForwardList {
  static_assert(N >= 0, "List size must be non-negative");

public:
  tpForwardList() = default;

  template <typename... Args>
  tpForwardList(T &&data, Args &&...args)
      : data(std::forward<T>(data)), list(std::forward<Args>(args)...) {}

  tpForwardList(T &&data, tpForwardList<T, N - 1> &&list)
      : data(std::forward<T>(data)),
        list(std::forward<tpForwardList<T, N - 1>>(list)) {}

  tpForwardList(const tpForwardList<T, N> &other)
      : data(other.data), list(other.list) {}

  tpForwardList(tpForwardList<T, N> &&other)
      : data(std::move(other.data)), list(std::move(other.list)) {}

  tpForwardList<T, N> &operator=(const tpForwardList<T, N> &other) {
    if (this != &other) {
      data = other.data;
      list = other.list;
    }
    return *this;
  }

  tpForwardList<T, N> &operator=(tpForwardList<T, N> &&other) {
    if (this != &other) {
      data = std::move(other.data);
      list = std::move(other.list);
    }
    return *this;
  }

  // O(N) 访问
  T &operator[](std::size_t index) {
    if (index == 0) {
      return data;
    } else {
      return list[index - 1];
    }
  }

  const T &operator[](std::size_t index) const {
    if (index == 0) {
      return data;
    } else {
      return list[index - 1];
    }
  }

  static constexpr std::size_t size() { return N; }

  T front() const { return data; }
  T back() const { return list[N - 1]; } // O(N) 访问

  tpForwardList<T, N + 1> insertToTail(const T &&val) const {
    return tpForwardList<T, N + 1>(std::forward<T>(data),
                                   list.insertToTail(val));
  }

  // 插入在index位置之前
  tpForwardList<T, N + 1> insert(const T &&val, std::size_t index) const {
    if (index == 0) {
      return tpForwardList<T, N + 1>(std::forward<T>(val), *this);
    } else {
      return tpForwardList<T, N + 1>(data, list.insert(val, index - 1));
    }
  }

  tpForwardList<T, N - 1> removeHead() const { return list; }

  tpForwardList<T, N - 1> removeTail() const { return list.removeTail(); }

  tpForwardList<T, N - 1> remove(std::size_t index) const {
    if (index == 0) {
      return list;
    } else {
      return tpForwardList<T, N - 1>(data, list.remove(index - 1));
    }
  }

  tpForwardList<T, N> reverse() const {
    return list.reverse().insertToTail(data);
  }

  tpForwardList<T, N> &reverse() {
    list.reverse();
    list = list.insertToTail(data);
    return *this;
  }

  template <typename U, std::size_t first, std::size_t second>
  friend bool operator==(const tpForwardList<U, first> &lhs,
                         const tpForwardList<U, second> &rhs);

  template <typename U, std::size_t first, std::size_t second>
  friend bool operator!=(const tpForwardList<U, first> &lhs,
                         const tpForwardList<U, second> &rhs);

  // 重载输出运算符
  template <class CharT, class Traits, typename U, std::size_t M>
  friend std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> &os,
             const tpForwardList<U, M> &list);

private:
  T data;
  tpForwardList<T, N - 1> list;
};

template <typename T> class tpForwardList<T, 0> {
public:
  tpForwardList() = default;

  T &operator[](std::size_t) { throw std::out_of_range("Index out of range"); }

  const T &operator[](std::size_t) const {
    throw std::out_of_range("Index out of range");
  }

  static constexpr std::size_t size() { return 0; }

  T front() const { throw std::out_of_range("Index out of range"); }
  T back() const { throw std::out_of_range("Index out of range"); }

  tpForwardList<T, 1> insertToTail(const T &&val) const {
    return tpForwardList<T, 1>(std::forward<T>(val));
  }

  tpForwardList<T, 1> insert(const T &&val, std::size_t index) const {
    if (index == 0) {
      return tpForwardList<T, 1>(std::forward<T>(val));
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  tpForwardList<T, 0> removeHead() const {
    throw std::out_of_range("Index out of range");
  }

  tpForwardList<T, 0> removeTail() const {
    throw std::out_of_range("Index out of range");
  }

  tpForwardList<T, 0> remove(std::size_t index) const {
    throw std::out_of_range("Index out of range");
  }

  tpForwardList<T, 0> reverse() const { return *this; }

  tpForwardList<T, 0> &reverse() { return *this; }

  template <typename U, std::size_t first, std::size_t second>
  friend bool operator==(const tpForwardList<U, first> &lhs,
                         const tpForwardList<U, second> &rhs);

  template <typename U, std::size_t first, std::size_t second>
  friend bool operator!=(const tpForwardList<U, first> &lhs,
                         const tpForwardList<U, second> &rhs);

  // 重载输出运算符
  template <class CharT, class Traits, typename U, std::size_t M>
  friend std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> &os,
             const tpForwardList<U, M> &list);
};

template <typename T, std::size_t first, std::size_t second>
bool operator==(const tpForwardList<T, first> &lhs,
                const tpForwardList<T, second> &rhs) {
  if constexpr (first != second) {
    return false;
  } else {
    return lhs.data == rhs.data && lhs.list == rhs.list;
  }
}

template <typename T, std::size_t first, std::size_t second>
bool operator!=(const tpForwardList<T, first> &lhs,
                const tpForwardList<T, second> &rhs) {
  return not(lhs == rhs);
}

template <class CharT, class Traits, typename T, std::size_t N>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os,
           const tpForwardList<T, N> &list) {
  os << list.data << ' ';
  os << list.list;
  return os;
}

template <class CharT, class Traits, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os,
           const tpForwardList<T, 0> &list) {
  os << "null list";
  return os;
}
} // namespace Tiny

#endif // TINY_LIST_HPP