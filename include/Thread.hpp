#ifndef TINY_THREAD_HPP
#define TINY_THREAD_HPP

namespace Tiny {
using _Thrd_id_t = unsigned int; // 线程ID类型

struct _Thrd_t // 线程类型
{
  void *_Hnd;     // 指向线程的句柄
  _Thrd_id_t _Id; // 线程ID
};

class Thread {
private:
  _Thrd_t _Thrd; // 线程类型

public:
  Thread() noexcept
      : _Thrd{nullptr, 0} {} // 默认构造函数 构造不关联线程的线程对象

  Thread(Thread &&_Other) noexcept
      : _Thrd{_Other._Thrd} // 移动构造函数
  {
    _Other._Thrd._Hnd = nullptr;
    _Other._Thrd._Id = 0;
  }

  Thread(const Thread &) = delete; // 禁用拷贝构造函数

  template <typename _Fn, typename... _Args>
  explicit Thread(_Fn &&_Fx, _Args &&..._Ax) // 构造函数
  {
    _Thrd._Hnd = nullptr;
    _Thrd._Id = 0;
    _Thrd_create(&_Thrd, _Fx, _Ax...);
  }

  ~Thread() noexcept // 析构函数
  {
    if (_Thrd._Hnd != nullptr) {
      _Thrd_join(_Thrd);
    }
  }

  _Thrd_id_t id() const noexcept // 获取线程ID
  {
    return _Thrd._Id;
  }

  template <typename _Fn, typename... _Args>
  void _Thrd_create(_Thrd_t &_Thrd, _Fn &&_Fx, _Args &&..._Ax);

  void _Thrd_join(_Thrd_t &_Thrd);
};
} // namespace Tiny

#endif // TINY_THREAD_HPP