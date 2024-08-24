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
        template <typename U>
        friend class MySharedPtr;

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
        RefCount<T> *m_refCnt_ptr;
        std::size_t id;
        inline static std::size_t count = 0;

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
    if (m_ptr != nullptr)
    {
        delete m_ptr;
    }
}

template <typename T>
MySTD::MySharedPtr<T>::MySharedPtr(T *ptr)
    : m_refCnt_ptr(new RefCount<T>(ptr)), id(++count)
{
}

template <typename T>
MySTD::MySharedPtr<T>::MySharedPtr(const MySharedPtr &other)
    : m_refCnt_ptr(other.m_refCnt_ptr), id(++count)
{
    ++m_refCnt_ptr->m_refCount;
}

template <typename T>
MySTD::MySharedPtr<T>::MySharedPtr(MySharedPtr &&other)
    : m_refCnt_ptr(other.m_refCnt_ptr), id(++count)
{
    other.m_refCnt_ptr = nullptr;
}

template <typename T>
MySTD::MySharedPtr<T>::~MySharedPtr()
{
    if (m_refCnt_ptr != nullptr && --m_refCnt_ptr->m_refCount == 0)
    {
        delete m_refCnt_ptr;
    }
}

template <typename T>
MySTD::MySharedPtr<T> &MySTD::MySharedPtr<T>::operator=(const MySharedPtr &other)
{
    if (this != &other)
    {
        if (m_refCnt_ptr != nullptr && --m_refCnt_ptr->m_refCount == 0)
        {
            delete m_refCnt_ptr;
        }

        m_refCnt_ptr = other.m_refCnt_ptr;
        ++m_refCnt_ptr->m_refCount;
    }

    return *this;
}

template <typename T>
MySTD::MySharedPtr<T> &MySTD::MySharedPtr<T>::operator=(MySharedPtr &&other)
{
    if (this != &other)
    {
        if (m_refCnt_ptr != nullptr && --m_refCnt_ptr->m_refCount == 0)
        {
            delete m_refCnt_ptr;
        }

        m_refCnt_ptr = other.m_refCnt_ptr;
        other.m_refCnt_ptr = nullptr;
    }

    return *this;
}

template <typename T>
T &MySTD::MySharedPtr<T>::operator*() const
{
    return *m_refCnt_ptr->m_ptr;
}

template <typename T>
T *MySTD::MySharedPtr<T>::operator->() const
{
    return m_refCnt_ptr->m_ptr;
}

template <typename T>
T *MySTD::MySharedPtr<T>::get() const
{
    return m_refCnt_ptr->m_ptr;
}

#endif // MY_SHARED_PTR_HPP