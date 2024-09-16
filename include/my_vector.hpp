#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

namespace MySTD
{
    template <typename value_type>
    class MyVector
    {
    private:
        using val_reference = value_type &;
        using val_const_reference = const value_type &;
        using val_pointer = value_type *;
        using val_const_pointer = const value_type *;
        using vec_pointer = MyVector *;
        using vec_const_pointer = const MyVector *;
        using vec_reference = MyVector &;
        using vec_const_reference = const MyVector &;

        val_pointer data_;
        std::size_t size_;
        std::size_t capacity_;

    public:
        // Constructors
        MyVector();
        MyVector(std::size_t size);
        MyVector(std::size_t size, val_const_reference value);
        MyVector(val_const_pointer first, val_const_pointer last);
        MyVector(const MyVector &other);
        MyVector(MyVector &&other) noexcept;

        // Destructor
        ~MyVector();

        // Operators
        vec_reference operator=(const MyVector &other);
        vec_reference operator=(MyVector &&other);
        val_reference operator[](std::size_t index);
        val_const_reference operator[](std::size_t index) const;

        // Capacity
        std::size_t size() const;
        std::size_t capacity() const;

        // Modifiers
        void assign(std::size_t size, val_const_reference value);
        void assign(val_const_pointer first, val_const_pointer last);
        template <typename... Args>
        void emplace_back(Args... args);
        void push_back(val_const_reference value);
        void pop_back();
        void clear();
        void resize(std::size_t size);
        void resize(std::size_t size, val_const_reference value);
        void reserve(std::size_t capacity);

        // Element access
        val_reference at(std::size_t index);
        val_const_reference at(std::size_t index) const;
        val_reference front();
        val_const_reference front() const;
        val_reference back();
        val_const_reference back() const;
        val_const_pointer data() const;
    };
}

// ==== Constructors Begin Here ====
// default constructor
template <typename value_type>
MySTD::MyVector<value_type>::MyVector()
    : data_(nullptr), size_(0), capacity_(0)
{
}

// constructor with size
template <typename value_type>
MySTD::MyVector<value_type>::MyVector(std::size_t size)
    : size_(size), capacity_(size)
{
    if (size == 0)
    {
        data_ = nullptr;
        return;
    }

    try
    {
        data_ = new value_type[size];
    }
    catch (std::bad_alloc &e)
    {
        throw e;
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        new (&data_[i]) value_type();
    }
}

// constructor with size and value
// initialize all elements with value given
template <typename value_type>
MySTD::MyVector<value_type>::MyVector(std::size_t size, val_const_reference value)
    : size_(size), capacity_(size)
{
    try
    {
        data_ = new value_type[size];
    }
    catch (std::bad_alloc &e)
    {
        throw e;
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        new (&data_[i]) value_type(value);
    }
}

// constructor with first and last pointer
// initialize all elements with value from first to last
template <typename value_type>
MySTD::MyVector<value_type>::MyVector(val_const_pointer first, val_const_pointer last)
    : size_(last - first), capacity_(last - first)
{
    try
    {
        data_ = new value_type[capacity_];
    }
    catch (std::bad_alloc &e)
    {
        throw e;
    }

    for (std::size_t i = 0; i < size_; ++i)
    {
        new (&data_[i]) value_type(first[i]);
    }
}

// copy constructor
template <typename value_type>
MySTD::MyVector<value_type>::MyVector(const MyVector &other)
    : size_(other.size_), capacity_(other.capacity_)
{
    try
    {
        data_ = new value_type[capacity_];
    }
    catch (std::bad_alloc &e)
    {
        throw e;
    }

    for (std::size_t i = 0; i < size_; ++i)
    {
        new (&data_[i]) value_type(other.data_[i]);
    }
}

// move constructor
template <typename value_type>
MySTD::MyVector<value_type>::MyVector(MyVector &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}
// ==== Constructors End Here ====

// ==== Destructor Begin Here ====
template <typename value_type>
MySTD::MyVector<value_type>::~MyVector()
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i].~value_type();
    }
    delete[] data_;
}
// ==== Destructor End Here ====

// ==== Operators Begin Here ====
// copy assignment operator
template <typename value_type>
typename MySTD::MyVector<value_type>::vec_reference
MySTD::MyVector<value_type>::operator=(const MyVector &other)
{
    return *this = MyVector(other);
}

// move assignment operator
template <typename value_type>
typename MySTD::MyVector<value_type>::vec_reference
MySTD::MyVector<value_type>::operator=(MyVector &&other)
{
    return *this = std::move(other);
}

// get element at index
template <typename value_type>
typename MySTD::MyVector<value_type>::val_reference
MySTD::MyVector<value_type>::operator[](std::size_t index)
{
    return data_[index];
}

// get element at index
template <typename value_type>
typename MySTD::MyVector<value_type>::val_const_reference
MySTD::MyVector<value_type>::operator[](std::size_t index) const
{
    return data_[index];
}
// ==== Operators End Here ====

// ==== Capacity Begin Here ====
// get size
template <typename value_type>
std::size_t MySTD::MyVector<value_type>::size() const
{
    return size_;
}

// get capacity
template <typename value_type>
std::size_t MySTD::MyVector<value_type>::capacity() const
{
    return capacity_;
}
// ==== Capacity End Here ====

// ==== Modifiers Begin Here ====
// assign size and value
template <typename value_type>
void MySTD::MyVector<value_type>::assign(std::size_t size, val_const_reference value)
{
    *this = MyVector(size, value);
}

// assign first and last pointer
template <typename value_type>
void MySTD::MyVector<value_type>::assign(val_const_pointer first, val_const_pointer last)
{
    *this = MyVector(first, last);
}

// emplace_back
template <typename value_type>
template <typename... Args>
void MySTD::MyVector<value_type>::emplace_back(Args... args)
{
    if (size_ == capacity_)
    {
        reserve(capacity_ * 2 + 1);
    }
    new (&data_[size_++]) value_type(std::forward<Args>(args)...);
}

// push_back
template <typename value_type>
void MySTD::MyVector<value_type>::push_back(val_const_reference value)
{
    emplace_back(value);
}

// pop_back
template <typename value_type>
void MySTD::MyVector<value_type>::pop_back()
{
    data_[--size_].~value_type();
}

// clear
template <typename value_type>
void MySTD::MyVector<value_type>::clear()
{
    if (data_ == nullptr)
    {
        return;
    }

    // release memory
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i].~value_type();
    }

    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

// resize
template <typename value_type>
void MySTD::MyVector<value_type>::resize(std::size_t size)
{
    if (size < size_)
    {
        // if size is less than current size, destruct elements
        for (std::size_t i = size; i < size_; ++i)
        {
            data_[i].~value_type();
        }
    }
    else if (size > size_)
    {
        // if size is greater than current size, construct elements
        if (size > capacity_)
        {
            reserve(size);
        }
        for (std::size_t i = size_; i < size; ++i)
        {
            new (&data_[i]) value_type();
        }
    }
    size_ = size;
}

// resize with value
template <typename value_type>
void MySTD::MyVector<value_type>::resize(std::size_t size, val_const_reference value)
{
    if (size < size_)
    {
        // if size is less than current size, destruct elements
        for (std::size_t i = size; i < size_; ++i)
        {
            data_[i].~value_type();
        }
    }
    else if (size > size_)
    {
        // if size is greater than current size, construct elements
        if (size > capacity_)
        {
            reserve(size);
        }
        for (std::size_t i = size_; i < size; ++i)
        {
            new (&data_[i]) value_type(value);
        }
    }
    size_ = size;
}

// reserve capacity
template <typename value_type>
void MySTD::MyVector<value_type>::reserve(std::size_t capacity)
{
    // if capacity is less than or equal to current capacity, return
    if (capacity <= capacity_)
    {
        return;
    }
    // create new data with new capacity
    try
    {
        val_pointer new_data = new value_type[capacity];

        for (std::size_t i = 0; i < size_; ++i)
        {
            new (&new_data[i]) value_type(std::move(data_[i]));
            data_[i].~value_type();
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = capacity;
    }
    catch (std::bad_alloc &e)
    {
        throw e; // throw exception if memory allocation fails
    }
}
// ==== Modifiers End Here ====

// ==== Element Access Begin Here ====
// at with index
// if index is out of range, throw exception
template <typename value_type>
typename MySTD::MyVector<value_type>::val_reference
MySTD::MyVector<value_type>::at(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

// at with index
template <typename value_type>
typename MySTD::MyVector<value_type>::val_const_reference
MySTD::MyVector<value_type>::at(std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

// get first element
template <typename value_type>
typename MySTD::MyVector<value_type>::val_reference
MySTD::MyVector<value_type>::front()
{
    return data_[0];
}

// get first element
template <typename value_type>
typename MySTD::MyVector<value_type>::val_const_reference
MySTD::MyVector<value_type>::front() const
{
    return data_[0];
}

// get last element
template <typename value_type>
typename MySTD::MyVector<value_type>::val_reference
MySTD::MyVector<value_type>::back()
{
    return data_[size_ - 1];
}

// get last element
template <typename value_type>
typename MySTD::MyVector<value_type>::val_const_reference
MySTD::MyVector<value_type>::back() const
{
    return data_[size_ - 1];
}

// get data pointer
template <typename value_type>
typename MySTD::MyVector<value_type>::val_const_pointer
MySTD::MyVector<value_type>::data() const
{
    return data_;
}
// ==== Element Access End Here ====

#endif // MY_VECTOR_HPP