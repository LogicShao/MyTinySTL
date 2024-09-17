#ifndef TINY_THREAD_HPP
#define TINY_THREAD_HPP

#include <cstddef>
#include <exception>
#include <memory>
#include <pthread.h>
#include <functional>
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
    using Tuple_t = std::tuple<std::decay_t<Function>, std::decay_t<Args>...>;
    auto decay_copy = std::make_unique<Tuple_t>(std::forward<Function>(f),
                                                std::forward<Args>(args)...);
    auto invoke_proc = start<Tuple_t>(std::make_index_sequence<1 + sizeof...(Args)>());
    if (int error = pthread_create(&tid, nullptr, invoke_proc, decay_copy.get());
        error != 0) {
      throw std::system_error(error, std::generic_category());
    }
    decay_copy.release();
  }

  template <class Tuple, std::size_t... Indices>
  static void *Invoke(void *RawVals) noexcept {
    const std::unique_ptr<Tuple> FnVals(static_cast<Tuple *>(RawVals));
    Tuple &Tup = *FnVals.get();
    std::invoke(std::move(std::get<Indices>(Tup))...);
    return nullptr;
  }

  template <typename Tuple, std::size_t... Indices>
  static constexpr auto start(std::index_sequence<Indices...>) noexcept {
    return &Invoke<Tuple, Indices...>;
  }

  Thread(const Thread &) = delete; // 删除拷贝构造函数

  Thread &operator=(const Thread &) = delete; // 删除拷贝赋值运算符

  Thread(Thread &&other) noexcept : tid(std::exchange(other.tid, {})) {}

  Thread &operator=(Thread &&other) noexcept {
    if (joinable()) {
      std::terminate();
    }
    tid = std::exchange(other.tid, {});
    return *this;
  }

  ~Thread() {
    if (joinable()) {
      std::terminate();
    }
  }

  bool joinable() const noexcept { return tid != 0; }

  void swap(Thread &other) noexcept { std::swap(tid, other.tid); }

  void join() {
    if (not joinable()) {
      throw std::system_error(EINVAL, std::generic_category());
    }
    if (int error = pthread_join(tid, nullptr); error != 0) {
      throw std::system_error(error, std::generic_category());
    }
    tid = {};
  }

  void detach() {
    if (not joinable()) {
      throw std::system_error(EINVAL, std::generic_category());
    }
    if (int error = pthread_detach(tid); error != 0) {
      throw std::system_error(error, std::generic_category());
    }
    tid = {};
  }

  id get_id() const noexcept;

  native_handle_type native_handle() { return tid; }

private:
  pthread_t tid;
};

namespace This_Thread {
[[nodiscard]] Thread::id get_id() noexcept;
}

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

  friend bool operator!=(id lhs, id rhs) noexcept { return not(lhs == rhs); }

  friend bool operator<(id lhs, id rhs) noexcept {
    return pthread_equal(lhs.tid, rhs.tid) < 0;
  }

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
  return Thread::id(pthread_self());
}
} // namespace Tiny

#endif // TINY_THREAD_HPP