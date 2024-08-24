#ifndef MY_SHARED_PTR_HPP
#define MY_SHARED_PTR_HPP

namespace MySTD
{
    template <typename T>
    class RefCount
    {
    private:
        T *m_ptr;
        std::size_t m_refCount;

    public:
        RefCount(T *ptr = nullptr);
        RefCount(const RefCount &other) = delete;
        RefCount &operator=(const RefCount &other) = delete;
        RefCount(RefCount &&other) = delete;
        RefCount &operator=(RefCount &&other) = delete;
    };
}

template <typename T>
MySTD::RefCount<T>::RefCount(T *ptr)
    : m_ptr(ptr), m_refCount(1)
{
}

#endif // MY_SHARED_PTR_HPP