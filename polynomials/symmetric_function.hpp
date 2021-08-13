
#pragma once
#include <iostream>
#include <vector>

template <typename I>
class newtons_formula
{
public:
    std::vector<I> a;
    std::vector<I> p;
    std::vector<I> e;
    I n;

    newtons_formula(I n)
    {
        this->n = n;
        this->p = std::vector<I>(this->n + 1, 0);
        this->e = std::vector<I>(this->n + 1, 0);
    }

    newtons_formula(std::vector<I> a)
    {
        this->a = a;
        this->n = a.size();
        this->p = std::vector<I>(this->n + 1, 0);
        this->e = std::vector<I>(this->n + 1, 0);
    }

    /*
    formula
    p[k] = a[0]^k+a[1]^k+...
    e[i]=a[0]*..*a[i]+a[1]*...*a[i+1] (sum of product of i numbers taken at a time)
    e[0]=1
    i*e[i] = e[i-1]p[1]-e[i-1]p[2]+...
    */
    // O( k*(n+k) ) time | O(n) space
    void compute(I k, I inMOD = 10000007)
    {
        assert(k <= n);

        std::vector<I> temp(n, 1);
        for (I j = 0; j <= k; j++)
        {
            for (I i = 0; i < this->n; i++)
            {
                this->p[j] = (this->p[j] + temp[i]) % inMOD;
                temp[i] = (temp[i] * this->a[i]) % inMOD;
            }
        }

        for (I j = 0; j <= k; j++)
        {
            for (I i = j - 1; i >= 0; i--)
            {
                this->e[j] = (this->e[j] + inMOD + ((j - i) % 2 == 1 ? 1 : -1) * ((this->e[i] * this->p[j - i]) % inMOD)) % inMOD;
            }
            if (j == 0)
            {
                this->e[j] = 1;
            }
            else
            {
                I pj = 1;
                I tn = inMOD - 2;
                I tj = j;
                while (tn > 0)
                {
                    if (tn & 1)
                    {
                        tj = (tj * pj) % inMOD;
                    }
                    pj = (pj * pj) % inMOD;
                    tn >>= 1;
                }
                this->e[j] = (this->e[j] * tj) % inMOD;
            }
        }
    }
};
