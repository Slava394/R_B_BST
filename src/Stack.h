#pragma once
#include <stdexcept>


template <typename T>
class Stack
{
private:
    //inner struct
    struct StackItem
    {
        StackItem *next;
        T data;
        StackItem(StackItem *next, const T &data) : next(next), data(data) {}
    };
    //head of the stack
    StackItem *head;
public:
    Stack() : head(nullptr) {}

    ~Stack()
    {
        StackItem *deletingNode = head;
        while (head != nullptr)
        {
            deletingNode = head;
            head = head->next;
            delete deletingNode;
        }
    }

    void push(const T &element)
    {
        head = new StackItem(head, element);
    }

    T pop()
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty");
        }
        T data = head->data;
        StackItem *deletingNode = head;
        head = head->next;
        delete deletingNode;
        return data;
    }

    T top()
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty");
        }
        return head->data;
    }

    bool empty()
    {
        return (head == nullptr);
    }
};
