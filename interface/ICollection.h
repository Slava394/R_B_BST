#pragma once
#include <cstddef>
#include "IEnumerable.h"


template <typename T>
class ICollection : public IEnumerable<T>
{
public:
    virtual T& Get(size_t) = 0;
    virtual size_t GetCount() = 0;
    virtual void CopyTo(T*, size_t) = 0;
    ~ICollection() override = default;
};
