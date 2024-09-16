#ifndef MY_ARRAY_HPP
#define MY_ARRAY_HPP
namespace MySTD
{
    template <typename T, std::size_t N> requires (N > 0)
    class MyArray
    {
    private:
        T m_data[N];
    public:
        MyArray() = default;
        MyArray(const MyArray &other) = default;
        MyArray(MyArray &&other) = default;
        MyArray &operator=(const MyArray &other) = default;
        MyArray &operator=(MyArray &&other) = default;
        ~MyArray() = default;

        T &operator[](std::size_t index);
        const T &operator[](std::size_t index) const;

        T *data();
        const T *data() const;

        std::size_t size() const;

        void fill(const T &value);

        T front() const;
        T back() const;

        T &at(std::size_t index);
        const T &at(std::size_t index) const;
    };
}

template <typename T, std::size_t N>
T &MySTD::MyArray<T, N>::operator[](std::size_t index)
{
    return m_data[index];
}

template <typename T, std::size_t N>
const T &MySTD::MyArray<T, N>::operator[](std::size_t index) const
{
    return m_data[index];
}

template <typename T, std::size_t N>
T *MySTD::MyArray<T, N>::data()
{
    return m_data;
}

template <typename T, std::size_t N>
const T *MySTD::MyArray<T, N>::data() const
{
    return m_data;
}

template <typename T, std::size_t N>
std::size_t MySTD::MyArray<T, N>::size() const
{
    return N;
}

template <typename T, std::size_t N>
void MySTD::MyArray<T, N>::fill(const T &value)
{
    for (std::size_t i = 0; i < N; i++)
    {
        m_data[i] = value;
    }
}

template <typename T, std::size_t N>
T MySTD::MyArray<T, N>::front() const
{
    return m_data[0];
}

template <typename T, std::size_t N>
T MySTD::MyArray<T, N>::back() const
{
    return m_data[N - 1];
}

template <typename T, std::size_t N>
T &MySTD::MyArray<T, N>::at(std::size_t index)
{
    if (index >= N)
    {
        throw std::out_of_range("MyArray::at");
    }

    return m_data[index];
}

template <typename T, std::size_t N>
const T &MySTD::MyArray<T, N>::at(std::size_t index) const
{
    if (index >= N)
    {
        throw std::out_of_range("MyArray::at");
    }

    return m_data[index];
}

#endif // MY_ARRAY_HPP