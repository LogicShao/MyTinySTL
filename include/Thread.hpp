#ifndef TINY_THREAD_HPP
#define TINY_THREAD_HPP

#include <cstddef>
#include <exception>
#include <functional>
#include <memory>
#include <pthread.h>
#include <system_error>
#include <tuple>
#include <utility>

namespace Tiny {
class Thread {
public:
  class id;
  using native_handle_type = pthread_t;

  Thread() noexcept = default;

  template <typename Function, typename... Args>
  Thread(Function &&f, Args &&...args) {
    // 使用std::decay_t移除引用和cv限定符
    using Tuple_t = std::tuple<std::decay_t<Function>, std::decay_t<Args>...>;
    // 使用std::make_unique创建一个Tuple_t对象
    auto decay_copy = std::make_unique<Tuple_t>(std::forward<Function>(f),
                                                std::forward<Args>(args)...);
    // 生成调用函数的函数指针
    auto invoke_proc =
        start<Tuple_t>(std::make_index_sequence<1 + sizeof...(Args)>());
    // 创建线程
    if (int error =
            pthread_create(&tid, nullptr, invoke_proc, decay_copy.get());
        error != 0) {
      throw std::system_error(error, std::generic_category());
    }
    // 释放decay_copy的所有权
    decay_copy.release();
  }

  // 调用函数的函数指针
  template <class Tuple, std::size_t... Indices>
  static void *Invoke(void *RawVals) noexcept {
    const std::unique_ptr<Tuple> FnVals(static_cast<Tuple *>(RawVals));
    Tuple &Tup = *FnVals.get();
    std::invoke(std::move(std::get<Indices>(Tup))...);
    return nullptr;
  }

  // 生成调用函数的函数指针
  template <typename Tuple, std::size_t... Indices>
  static constexpr auto start(std::index_sequence<Indices...>) noexcept {
    return &Invoke<Tuple, Indices...>;
  }

  Thread(const Thread &) = delete; // 删除拷贝构造函数

  Thread &operator=(const Thread &) = delete; // 删除拷贝赋值运算符

  Thread(Thread &&other) noexcept
      : tid(std::exchange(other.tid, {})) {} // 移动构造函数

  Thread &operator=(Thread &&other) noexcept { // 移动赋值运算符
    if (joinable()) {
      std::terminate();
    }
    tid = std::exchange(other.tid, {});
    return *this;
  }

  ~Thread() {
    if (joinable()) {
      std::terminate(); // 未调用join或detach时终止程序
    }
  }

  bool joinable() const noexcept { return tid != 0; }

  void swap(Thread &other) noexcept { std::swap(tid, other.tid); }

  void join() {           // 等待线程结束
    if (not joinable()) { // 如果线程不可连接
      throw std::system_error(EINVAL, std::generic_category()); // 抛出异常
    }
    if (int error = pthread_join(tid, nullptr); error != 0) { // 等待线程结束
      throw std::system_error(error, std::generic_category());
    }
    tid = {}; // 线程结束后，将tid置空
  }

  void detach() {         // 分离线程
    if (not joinable()) { // 如果线程不可连接
      throw std::system_error(EINVAL, std::generic_category()); // 抛出异常
    }
    if (int error = pthread_detach(tid); error != 0) { // 分离线程
      throw std::system_error(error, std::generic_category());
    }
    tid = {}; // 线程分离后，将tid置空
  }

  id get_id() const noexcept; // 获取线程id

  native_handle_type native_handle() { return tid; } // 获取线程句柄

private:
  pthread_t tid;
};

namespace This_Thread {
[[nodiscard]] Thread::id get_id() noexcept; // 获取当前线程id
} // namespace This_Thread

class Thread::id {
public:
  id() noexcept = default;

private:
  pthread_t tid;

  explicit id(pthread_t other_id) noexcept : tid(other_id) {}

  friend id Thread::get_id() const noexcept;
  friend id This_Thread::get_id() noexcept;

  friend bool operator==(id lhs, id rhs) noexcept {
    return pthread_equal(lhs.tid, rhs.tid) != 0;
  }

  friend bool operator!=(id lhs, id rhs) noexcept {
    return not(lhs == rhs);
  } // 重载!=运算符

  // 输出线程id
  template <typename CharT, typename Traits>
  friend std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> &os, id i) {
    return os << i.tid;
  }
};

[[nodiscard]] inline Thread::id Thread::get_id() const noexcept {
  return Thread::id(tid);
}

[[nodiscard]] inline Thread::id This_Thread::get_id() noexcept {
  return Thread::id(pthread_self()); // 调用posix接口获取当前线程id
}
} // namespace Tiny

#endif // TINY_THREAD_HPP