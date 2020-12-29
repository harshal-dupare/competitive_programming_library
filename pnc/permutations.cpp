#include <bits/stdc++.h>
#include "../utils/timer.h"
#include "../utils/debugger.h"

using namespace std;

typedef long long ll;

template <typename I>
class permutation
{
public:
    I n;
    vector<I> p;

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

    permutation(vector<I> &a)
    {
        this->n = a.size();
        this->p = a;
    }

    permutation<I> operator*(const permutation<I> &o)
    {
        permutation<I> po(this->n);
        for (I i = 0; i < n; i++)
        {
            po.p[i] = this->p[o.p[i]];
        }
        return po;
    }

    void operator*=(const permutation<I> &o)
    {
        vector<I> po;
        po.assign(n, 0);
        for (I i = 0; i < n; i++)
        {
            po[i] = this->p[o.p[i]];
        }
        this->p = po;
    }

    permutation<I> operator<<(I k)
    {
        permutation<I> po(this->n);
        for (I i = 0; i < this->n; i++)
        {
            po.p[i] = this->p[(this->n + (i - k) % this->n) % this->n];
        }
        return po;
    }

    permutation<I> operator>>(I k)
    {
        permutation<I> po(this->n);
        for (I i = 0; i < this->n; i++)
        {
            po.p[i] = this->p[(this->n + (i + k) % this->n) % this->n];
        }
        return po;
    }

    void operator>>=(I k)
    {
        vector<I> po(n);
        po.assign(this->n, 0);
        for (I i = 0; i < this->n; i++)
        {
            po[i] = this->p[(this->n + (i + k) % this->n) % this->n];
        }
        this->p = po;
    }

    void operator<<=(I k)
    {
        vector<I> po(n);
        for (I i = 0; i < this->n; i++)
        {
            po[i] = this->p[(this->n + (i - k) % this->n) % this->n];
        }
        this->p = po;
    }

    permutation<I> operator~()
    {
        permutation<I> po(n);
        for (I i = 0; i < this->n; i++)
        {
            po.p[this->p[i]] = i;
        }
        return po;
    }

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

    I cyclic_decompose(vector<vector<I>> &cycle)
    {
        vector<bool> done(n, false);
        I id = 0;
        I transposition_ct = n;
        for (I i = 0; i < n; i++)
        {
            if (!done[i])
            {
                I start = i;
                cycle.push_back(vector<I>(1, this->p[start]));
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
        for (I i = n; i > 1; i--)
        {
            I j = abs(rand()) % i;
            this->swap(i - 1, j);
        }
    }

    void print()
    {
        cerr << "[ ";
        for (I i = 0; i < n; i++)
        {
            cerr << this->p[i] << ", ";
        }
        cerr << "]\n";
    }
};

int main()
{
    ll n;
    cin >> n;
    permutation<ll> a(n), b, c(n), d, e;
    a.print();
    a <<= 1;
    a.print();
    a >>= 100;
    a.print();
    b = a ^ 10;
    b.print();
    b.swap(0, n - 1);
    b.print();
    c = ~b;
    c.print();
    b.randomize();
    b.print();

    vector<vector<ll>> cycle_dec;
    ll transposition_count = b.cyclic_decompose(cycle_dec);
    ok(transposition_count);
    okvv(cycle_dec);

    return 0;
}
