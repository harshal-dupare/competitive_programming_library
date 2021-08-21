#pragma once
#include <vector>
#include <iostream>

template <typename I>
class permutation
{
public:
    I n;
    std::vector<I> p;

    permutation() {}

    permutation(I n)
    {
        this->n = n;
        this->p.assign(n, 0);
        for (I i = 0; i < n; i++)
        {
            this->p[i] = i;
        }
    }

    permutation(const std::vector<I> &a)
    {
        this->n = a.size();
        this->p = a;
    }

    // O(n)
    permutation<I> operator*(const permutation<I> &o)
    {
        permutation<I> po(this->n);
        for (I i = 0; i < n; i++)
        {
            po.p[i] = this->p[o.p[i]];
        }
        return po;
    }

    // O(n)
    void operator*=(const permutation<I> &o)
    {
        std::vector<I> po;
        po.assign(n, 0);
        for (I i = 0; i < n; i++)
        {
            po[i] = this->p[o.p[i]];
        }
        this->p = po;
    }

    // O(n)
    permutation<I> operator<<(I k)
    {
        permutation<I> po(this->n);
        for (I i = 0; i < this->n; i++)
        {
            po.p[i] = this->p[(this->n + (i - k) % this->n) % this->n];
        }
        return po;
    }

    // O(n)
    permutation<I> operator>>(I k)
    {
        permutation<I> po(this->n);
        for (I i = 0; i < this->n; i++)
        {
            po.p[i] = this->p[(this->n + (i + k) % this->n) % this->n];
        }
        return po;
    }

    // O(n)
    void operator>>=(I k)
    {
        std::vector<I> po(n);
        po.assign(this->n, 0);
        for (I i = 0; i < this->n; i++)
        {
            po[i] = this->p[(this->n + (i + k) % this->n) % this->n];
        }
        this->p = po;
    }

    // O(n)
    void operator<<=(I k)
    {
        std::vector<I> po(n);
        for (I i = 0; i < this->n; i++)
        {
            po[i] = this->p[(this->n + (i - k) % this->n) % this->n];
        }
        this->p = po;
    }

    // O(n)
    permutation<I> operator~()
    {
        permutation<I> po(n);
        for (I i = 0; i < this->n; i++)
        {
            po.p[this->p[i]] = i;
        }
        return po;
    }

    // O(nlog(k))
    permutation<I> operator^(I k)
    {
        permutation<I> po(this->n);
        permutation<I> po1(this->n);
        for (I i = 0; i < this->n; i++)
        {
            po.p[i] = this->p[i];
            po1.p[i] = i;
        }

        while (k > 0)
        {
            if (k & 1)
            {
                po1 *= po;
            }
            k >>= 1;
            po *= po;
        }

        return po1;
    }

    I operator[](int i) const
    {
        return this->p[i];
    }

    void swap(I i, I j)
    {
        if (i == j)
        {
            return;
        }
        this->p[i] ^= this->p[j];
        this->p[j] ^= this->p[i];
        this->p[i] ^= this->p[j];
    }
    
    // cycle count
    // sign
    // order p^order = I

    // O(n)
    I cyclic_decompose(std::vector<std::vector<I>> &cycle)
    {
        std::vector<bool> done(n, false);
        I id = 0;
        I transposition_ct = n;
        for (I i = 0; i < n; i++)
        {
            if (!done[i])
            {
                I start = i;
                cycle.push_back(std::vector<I>(1, this->p[start]));
                done[start] = true;

                while (true)
                {
                    start = this->p[start];
                    if (start == i)
                    {
                        cycle[id].shrink_to_fit();
                        id++;
                        break;
                    }
                    cycle[id].push_back(this->p[start]);
                    done[start] = true;
                }
            }
        }
        cycle.shrink_to_fit();
        transposition_ct -= cycle.size();
        return transposition_ct;
    }

    void randomize()
    {
        std::random_shuffle(this->p.begin(),this->p.end());
    }

    friend std::ostream& operator<<(std::ostream &os, const permutation<I>& p)
    {
        os << "[ ";
        for (I i = 0; i < p.n; i++)
        {
            os << p.p[i] << ", ";
        }
        os << "]\n";
        return os;
    }
};

