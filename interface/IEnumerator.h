#pragma once


class IEnumerator
{
public:
    virtual IEnumerator& operator++() = 0;
    virtual IEnumerator* operator++(int) = 0;
    virtual ~IEnumerator() = default;
};
