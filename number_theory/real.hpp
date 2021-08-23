#pragma once
#include <cmath>

namespace real
{
    // fp >=0,fp+ip=x
    template <typename R>
    std::pair<R, R> decompose(R x, R _EPSILON = 1e-6)
    {
        R ni = std::round(x);
        if (std::abs(x - ni) <= _EPSILON)
            return {0.0, ni};
        R ip, fp;
        if (x >= ni)
            fp = x - ni, ip = ni;
        else
            fp = x - ni + 1, ip = ni - 1;
        return {fp, ip};
    }

}