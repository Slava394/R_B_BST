#pragma once
#include <stdexcept>

//custom stack aka vector
template <typename T>
class Stack
{
private:
    //private fields
    T* data;
    size_t capacity;
    size_t size;
    //resize if the size is equal to stock
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
    //constructror
    Stack() : data(nullptr), capacity(0), size(0) {}
    //copy constructor
    Stack(const Stack &otherStack)
    {
        data = new T[otherStack.capacity];
        capacity = otherStack.capacity;
        size = otherStack.size;
        for (size_t index{0}; index < size; ++index)
        {
            data[index] = otherStack.data[index];
        }
    }
    //destructor
    ~Stack()
    {
        delete[] data;
    }
    //push
    void push(const T& element)
    {
        if (size == capacity)
        {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = element;
    }
    //pop
    T pop()
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty");
        }
        return data[--size];
    }
    //pop without deleting
    T top()
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty");
        }
        return data[size - 1];
    }
    //is empty?
    [[nodiscard]] bool empty() const
    {
        return size == 0;
    }
};
