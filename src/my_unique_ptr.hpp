#ifndef MY_UNIQUE_PTR_HPP
#define MY_UNIQUE_PTR_HPP

namespace MySTD
{
    template <typename T>
    class MyDefaultDeleter
    {
    public:
        void operator()(T *ptr) const;
    };

    template <typename T, typename Deleter = MyDefaultDeleter<T>>
    class MyUniquePtr
    {
    private:
        T *m_ptr;
        Deleter m_deleter;

    public:
        MyUniquePtr(T *ptr = nullptr, Deleter deleter = Deleter());
        MyUniquePtr(const MyUniquePtr &other) = delete;
        MyUniquePtr(MyUniquePtr &&other);
        ~MyUniquePtr();

        MyUniquePtr &operator=(const MyUniquePtr &other) = delete;
        MyUniquePtr &operator=(MyUniquePtr &&other);

        T &operator*() const;
        T *operator->() const;

        T *get() const;
        T *release();
        void reset(T *ptr = nullptr);
    };

    template <typename T, typename Deleter = MyDefaultDeleter<T>, typename... Args>
    MyUniquePtr<T, Deleter> make_unique(Args &&...args)
    {
        return MyUniquePtr<T, Deleter>(new T(std::forward<Args>(args)...));
    }
}

template <typename T>
void MySTD::MyDefaultDeleter<T>::operator()(T *ptr) const
{
    if (ptr)
    {
        delete ptr;
    }
}

template <typename T, typename Deleter>
MySTD::MyUniquePtr<T, Deleter>::MyUniquePtr(T *ptr, Deleter deleter)
    : m_ptr(ptr), m_deleter(deleter)
{
}

template <typename T, typename Deleter>
MySTD::MyUniquePtr<T, Deleter>::MyUniquePtr(MyUniquePtr &&other)
    : m_ptr(other.m_ptr), m_deleter(other.m_deleter)
{
    other.m_ptr = nullptr;
}

template <typename T, typename Deleter>
MySTD::MyUniquePtr<T, Deleter>::~MyUniquePtr()
{
    m_deleter(m_ptr);
}

template <typename T, typename Deleter>
MySTD::MyUniquePtr<T, Deleter> &MySTD::MyUniquePtr<T, Deleter>::operator=(MyUniquePtr &&other)
{
    if (this != &other)
    {
        m_deleter(m_ptr);
        m_ptr = other.m_ptr;
        m_deleter = other.m_deleter;
        other.m_ptr = nullptr;
    }

    return *this;
}

template <typename T, typename Deleter>
T &MySTD::MyUniquePtr<T, Deleter>::operator*() const
{
    return *m_ptr;
}

template <typename T, typename Deleter>
T *MySTD::MyUniquePtr<T, Deleter>::operator->() const
{
    return m_ptr;
}

template <typename T, typename Deleter>
T *MySTD::MyUniquePtr<T, Deleter>::get() const
{
    return m_ptr;
}

template <typename T, typename Deleter>
T *MySTD::MyUniquePtr<T, Deleter>::release()
{
    T *ptr = m_ptr;
    m_ptr = nullptr;
    return ptr;
}

template <typename T, typename Deleter>
void MySTD::MyUniquePtr<T, Deleter>::reset(T *ptr)
{
    m_deleter(m_ptr);
    m_ptr = ptr;
}

#endif // MY_UNIQUE_PTR_HPP