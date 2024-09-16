namespace MySTD
{
    template <typename T, std::size_t N>
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