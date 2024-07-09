#pragma once
#include "IEnumerator.h"


class IEnumerable
{
public:
    virtual IEnumerator* begin() = 0;
    virtual IEnumerator* end() = 0;
    virtual ~IEnumerable() = default;
};
