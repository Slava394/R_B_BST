#pragma once
#include <stdexcept>


template <typename T>
class Stack
{
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(const size_t newCapacity)
    {
        T* newData = new T[newCapacity];
        for (size_t index{0}; index < size; ++index)
        {
            newData[index] = data[index];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
public:
    Stack() : data(nullptr), capacity(0), size(0) {}

    ~Stack()
    {
        delete[] data;
    }

    void push(const T& element)
    {
        if (size == capacity)
        {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = element;
    }

    T pop()
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty");
        }
        return data[--size];
    }

    T top()
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty");
        }
        return data[size - 1];
    }

    [[nodiscard]] bool empty() const
    {
        return size == 0;
    }
};
