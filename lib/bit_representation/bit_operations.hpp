#pragma once

namespace bit_operations
{
    // O(log(x)) time
    template <typename I>
    I most_significant_bit(I n)
    {
        I m = 0;
        while (n > 0)
        {
            m++;
            n >>= 1;
        }

        return m;
    }

    // O(log(x)) time
    template <typename I>
    I least_significant_bit(I n)
    {
        I l = 0;
        while (n > 0)
        {
            l++;
            if (n & 1)
                break;
            n >>= 1;
        }
        return l;
    }
};

namespace bit_encodings
{
    template <typename I>
    I gray(I n)
    {
        return n ^ (n >> 1);
    }

    template <typename I>
    I inverse_gray(I g)
    {
        I n = 0;
        while (g)
        {
            n ^= g;
            g >>= 1;
        }
        return n;
    }
};