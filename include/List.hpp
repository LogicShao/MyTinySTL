#ifndef TINY_LIST_HPP
#define TINY_LIST_HPP

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace Tiny {
template <typename T> struct ListNode {
  ListNode() : next(nullptr), prev(nullptr) {}
  ListNode(const T &data) : data(data), next(nullptr), prev(nullptr) {}
  ListNode(T &&data) : data(std::move(data)), next(nullptr), prev(nullptr) {}

  T data;
  ListNode *next;
  ListNode *prev;

  ListNode &operator=(const ListNode &other) {
    if (this != &other) {
      data = other.data;
      next = other.next;
      prev = other.prev;
    }
    return *this;
  }

  ListNode &operator=(ListNode &&other) {
    if (this != &other) {
      data = std::move(other.data);
      next = other.next;
      prev = other.prev;

      other.next = nullptr;
      other.prev = nullptr;
    }
    return *this;
  }

  ListNode &operator=(T &&val) {
    data = std::forward(val);
    return *this;
  }

  T prevData() const {
    if (prev) {
      return prev->data;
    } else {
      throw std::out_of_range("No previous node");
    }
  }

  T nextData() const {
    if (next) {
      return next->data;
    } else {
      throw std::out_of_range("No next node");
    }
  }

  explicit operator T() const { return data; }

  template <typename U>
  friend bool operator==(const ListNode<U> &lhs, const ListNode<U> &rhs) {
    return lhs.data == rhs.data && lhs.next == rhs.next && lhs.prev == rhs.prev;
  }

  template <typename U>
  friend bool operator!=(const ListNode<U> &lhs, const ListNode<U> &rhs) {
    return not(lhs == rhs);
  }

  template <typename U> friend class List;
};

template <typename T> class List { // 双向链表
public:
  using element_type = T;
  using iterator = ListNode<T> *;
  using const_iterator = const ListNode<T> *;

  List() : m_size(0) {
    m_head = new ListNode<T>();
    m_tail = m_head;
  }

  List(const List &other) {
    if (other.m_head) {
      m_head = new ListNode<T>(other.m_head->data);
      ListNode<T> *curr = m_head;
      ListNode<T> *otherCurr = other.m_head;
      while (otherCurr->next) {
        curr->next = new ListNode<T>(otherCurr->next->data);
        curr->next->prev = curr;
        curr = curr->next;
        otherCurr = otherCurr->next;
      }
      m_tail = curr;
    }
  }

  List(List &&other) {
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_size = other.m_size;

    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
  }

  List &operator=(const List &other) {
    if (this != &other) {
      if (other.m_head) {
        m_head = new ListNode<T>(other.m_head->data);
        ListNode<T> *curr = m_head;
        ListNode<T> *otherCurr = other.m_head;
        while (otherCurr->next) {
          curr->next = new ListNode<T>(otherCurr->next->data);
          curr->next->prev = curr;
          curr = curr->next;
          otherCurr = otherCurr->next;
        }
        m_tail = curr;
      }
    }
    return *this;
  }

  List &operator=(List &&other) {
    if (this != &other) {
      m_head = other.m_head;
      m_tail = other.m_tail;
      m_size = other.m_size;

      other.m_head = nullptr;
      other.m_tail = nullptr;
      other.m_size = 0;
    }
    return *this;
  }

  ~List() {
    ListNode<T> *curr = m_head;
    while (curr) {
      ListNode<T> *next = curr->next;
      delete curr;
      curr = next;
    }
  }

  T front() const { return m_head->data; }

  T &front() { return m_head->data; }

  T back() const { return m_tail->data; }

  T &back() { return m_tail->data; }

  void push_front(T &&val) {
    ListNode<T> *newNode = new ListNode<T>(std::forward(val));
    newNode->next = m_head;
    m_head->prev = newNode;
    m_head = newNode;
    ++m_size;
  }

  void push_back(T &&val) {
    if (m_head) {
      m_tail->next = new ListNode<T>(std::forward(val));
      m_tail->next->prev = m_tail;
      m_tail = m_tail->next;
      ++m_size;
    } else {
      m_head = new ListNode<T>(std::forward(val));
      m_tail = m_head;
      ++m_size;
    }
  }

  void pop_front() {
    if (m_head == nullptr) {
      throw std::out_of_range("List is empty");
    }
    ListNode<T> *next = m_head->next;
    delete m_head;
    m_head = next;
    if (m_head) {
      m_head->prev = nullptr;
    } else {
      m_tail = nullptr;
    }
    --m_size;
  }

  void pop_back() {
    if (m_head == nullptr) {
      throw std::out_of_range("List is empty");
    }
    ListNode<T> *prev = m_tail->prev;
    delete m_tail;
    m_tail = prev;
    if (m_tail) {
      m_tail->next = nullptr;
    } else {
      m_head = nullptr;
    }
    --m_size;
  }

  void insert(T &&val, std::size_t index) {
    /**
      * @brief 在index位置之前插入元素
      * @param val 要插入的元素
      * @param index 插入位置
      * @throw std::out_of_range 如果index超出范围

      * @note 时间复杂度O(N)
      * @note 索引从0开始
      * @note 如果index等于链表长度，则插入到链表尾部
      */
    if (index > m_size) {
      throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
      push_front(std::forward(val));
    } else if (index == m_size) {
      push_back(std::forward(val));
    } else {
      ListNode<T> *curr = m_head;
      for (std::size_t i = 0; i < index; ++i) {
        curr = curr->next;
      }
      ListNode<T> *newNode = new ListNode<T>(std::forward(val));
      curr->insert(newNode);
      ++m_size;
    }
  }

  void remove(std::size_t index) {
    /**
      * @brief 删除index位置的元素
      * @param index 要删除的元素的位置
      * @throw std::out_of_range 如果index超出范围

      * @note 时间复杂度O(N)
      * @note 索引从0开始
      */
    if (index >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
      pop_front();
    } else if (index == m_size - 1) {
      pop_back();
    } else {
      ListNode<T> *curr = m_head;
      for (std::size_t i = 0; i < index; ++i) {
        curr = curr->next;
      }
      curr->remove();
      --m_size;
    }
  }

  void clear() {
    ListNode<T> *curr = m_head;
    while (curr) {
      ListNode<T> *next = curr->next;
      delete curr;
      curr = next;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
  }

  std::size_t size() const { return m_size; }

  bool empty() const { return m_size == 0; }

  iterator begin() { return m_head; }

  iterator end() { return nullptr; }

  const_iterator begin() const { return m_head; }

  const_iterator end() const { return nullptr; }

  const_iterator cbegin() const { return m_head; }

  const_iterator cend() const { return nullptr; }

  T &operator[](std::size_t index) {
    if (index >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    ListNode<T> *curr = m_head;
    for (std::size_t i = 0; i < index; ++i) {
      curr = curr->next;
    }
    return curr->data;
  }

  const T &operator[](std::size_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    ListNode<T> *curr = m_head;
    for (std::size_t i = 0; i < index; ++i) {
      curr = curr->next;
    }
    return curr->data;
  }

  void reverse() {
    ListNode<T> *curr = m_head;
    ListNode<T> *prev = nullptr;
    while (curr) {
      ListNode<T> *next = curr->next;
      curr->next = prev;
      curr->prev = next;
      prev = curr;
      curr = next;
    }
    m_tail = m_head;
    m_head = prev;
  }

  List<T> &operator+=(const List<T> &other) {
    if (other.m_head) {
      m_tail->next = new ListNode<T>(other.m_head->data);
      m_tail->next->prev = m_tail;
      ListNode<T> *curr = m_tail->next;
      ListNode<T> *otherCurr = other.m_head;
      while (otherCurr->next) {
        curr->next = new ListNode<T>(otherCurr->next->data);
        curr->next->prev = curr;
        curr = curr->next;
        otherCurr = otherCurr->next;
      }
      m_tail = curr;
      m_size += other.m_size;
    }
    return *this;
  }

  template <typename U>
  friend bool operator==(const List<U> &lhs, const List<U> &rhs) {
    if (lhs.m_size != rhs.m_size) {
      return false;
    }
    ListNode<U> *lhsCurr = lhs.m_head;
    ListNode<U> *rhsCurr = rhs.m_head;
    while (lhsCurr) {
      if (lhsCurr->data != rhsCurr->data) {
        return false;
      }
      lhsCurr = lhsCurr->next;
      rhsCurr = rhsCurr->next;
    }
    return true;
  }

  template <typename U>
  friend bool operator!=(const List<U> &lhs, const List<U> &rhs) {
    return not(lhs == rhs);
  }

  // 重载输出运算符
  template <class CharT, class Traits, typename U>
  friend std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> &os, const List<U> &list) {
    ListNode<U> *curr = list.m_head;
    while (curr) {
      os << curr->data << ' ';
      curr = curr->next;
    }
    return os;
  }

private:
  ListNode<T> *m_head;
  ListNode<T> *m_tail;
  std::size_t m_size;
};

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

  T &front() { return data; }

  T back() const { return list[N - 1]; } // O(N) 访问

  T &back() { return list[N - 1]; }      // O(N) 访问

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

constexpr const char *NULL_LIST_STR = "{null}";

template <class CharT, class Traits, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os,
           const tpForwardList<T, 0> &list) {
  os << NULL_LIST_STR;
  return os;
}
} // namespace Tiny

#endif // TINY_LIST_HPP