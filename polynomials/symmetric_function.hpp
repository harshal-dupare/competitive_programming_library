
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
    bool usemod;

    newtons_formula(I n)
    {
        this->n = n;
        this->p = std::vector<I>(this->n + 1, 0);
        this->e = std::vector<I>(this->n + 1, 0);
        this->usemod=false;
    }

    newtons_formula(std::vector<I> a)
    {
        this->a = a;
        this->n = a.size();
        this->p = std::vector<I>(this->n + 1, 0);
        this->e = std::vector<I>(this->n + 1, 0);
        this->usemod=false;
    }

    /*
    formula
    p[k] = a[0]^k+a[1]^k+...
    e[i]=a[0]*..*a[i]+a[1]*...*a[i+1] (sum of product of i numbers taken at a time)
    e[0]=1
    i*e[i] = e[i-1]p[1]-e[i-1]p[2]+...
    */
    // O( k*(n+k) ) time | O(n) space
    void normalize(I &a, I mod)
    {
        if(a>=0&&a<mod) return;
        a%=mod;
        if(a<0) a+=mod;
    }

    void compute(I k, I MOD = 10000007)
    {
        assert(k <= n);

        std::vector<I> temp(n, 1);
        for (I j = 0; j <= k; j++)
        {
            for (I i = 0; i < this->n; i++)
            {
                this->p[j] = (this->p[j] + temp[i]);
                if(this->usemod) this->normalize(this->p[j],MOD);
                temp[i] = (temp[i] * this->a[i]);
                if(this->usemod) this->normalize(temp[j],MOD);
            }
        }

        for (I j = 0; j <= k; j++)
        {
            for (I i = j - 1; i >= 0; i--)
            {
                I t = (this->e[i] * this->p[j - i]);
                if(this->usemod) this->normalize(t,MOD);
                this->e[j] = (this->e[j] + ((j - i) % 2 == 1 ? 1 : -1) * t) ;
                if(this->usemod) this->normalize(this->e[j],MOD);
            }
            if (j == 0)
            {
                this->e[j] = 1;
            }
            else
            {
                if(this->usemod)
                {
                    I pj = 1;
                    I tn = MOD - 2;
                    I tj = j;
                    while (tn > 0)
                    {
                        if (tn & 1)
                        {
                            tj = (tj * pj);
                            this->normalize(tj,MOD);
                        }
                        pj = (pj * pj);
                        this->normalize(pj,MOD);
                        tn >>= 1;
                    }
                    this->e[j] = (this->e[j] * tj);
                    this->normalize(this->e[j],MOD);
                }
                else
                {
                    this->e[j]/=j;
                }
            }
        }
    }
};
