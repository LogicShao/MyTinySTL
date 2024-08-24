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

        // MySharedPtr needs to access private members of RefCount
        friend class MySharedPtr<T>;

    public:
        RefCount(T *ptr = nullptr);
        RefCount(const RefCount &other) = delete;
        RefCount &operator=(const RefCount &other) = delete;
        RefCount(RefCount &&other) = delete;
        RefCount &operator=(RefCount &&other) = delete;
        ~RefCount();
    };

    template <typename T>
    class MySharedPtr
    {
    private:
        RefCount<T> *m_refCount;

    public:
        MySharedPtr(T *ptr = nullptr);
        MySharedPtr(const MySharedPtr &other);
        MySharedPtr(MySharedPtr &&other);
        ~MySharedPtr();

        MySharedPtr &operator=(const MySharedPtr &other);
        MySharedPtr &operator=(MySharedPtr &&other);

        T &operator*() const;
        T *operator->() const;

        T *get() const;
    };
}

template <typename T>
MySTD::RefCount<T>::RefCount(T *ptr)
    : m_ptr(ptr), m_refCount(1)
{
}

template <typename T>
MySTD::RefCount<T>::~RefCount()
{
    --m_refCount;
    if (m_refCount == 0 && m_ptr)
    {
        delete m_ptr;
    }
}

template <typename T>
MySTD::MySharedPtr<T>::MySharedPtr(T *ptr)
    : m_refCount(new RefCount<T>(ptr))
{
}

template <typename T>
MySTD::MySharedPtr<T>::MySharedPtr(const MySharedPtr &other)
    : m_refCount(other.m_refCount)
{
    ++m_refCount->m_refCount;
}

template <typename T>
MySTD::MySharedPtr<T>::MySharedPtr(MySharedPtr &&other)
    : m_refCount(other.m_refCount)
{
    other.m_refCount = nullptr;
}

template <typename T>
MySTD::MySharedPtr<T>::~MySharedPtr()
{
    
}

template <typename T>
MySTD::MySharedPtr<T> &MySTD::MySharedPtr<T>::operator=(const MySharedPtr &other)
{
    if (this != &other)
    {
        if (m_refCount)
        {
            delete m_refCount;
        }

        m_refCount = other.m_refCount;
        ++m_refCount->m_refCount;
    }

    return *this;
}

template <typename T>
MySTD::MySharedPtr<T> &MySTD::MySharedPtr<T>::operator=(MySharedPtr &&other)
{
    if (this != &other)
    {
        if (m_refCount)
        {
            delete m_refCount;
        }

        m_refCount = other.m_refCount;
        other.m_refCount = nullptr;
    }

    return *this;
}

template <typename T>
T &MySTD::MySharedPtr<T>::operator*() const
{
    return *m_refCount->m_ptr;
}

template <typename T>
T *MySTD::MySharedPtr<T>::operator->() const
{
    return m_refCount->m_ptr;
}

template <typename T>
T *MySTD::MySharedPtr<T>::get() const
{
    return m_refCount->m_ptr;
}

#endif // MY_SHARED_PTR_HPP