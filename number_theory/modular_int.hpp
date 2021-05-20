#pragma once

template <typename I, I mod>
class modular
{
public:
    I n;

    modular()
    {
        this->n = 0;
    }

    modular(I _n)
    {
        this->n = (_n % mod + mod) % mod;
    }

    void operator=(const modular<I, mod> &o)
    {
        this->n = o.n;
    }

    void operator=(I _n)
    {
        this->n = (_n % mod + mod) % mod;
    }

    bool operator>(const modular<I, mod> &o)
    {
        return this->n > o.n;
    }

    bool operator<(const modular<I, mod> &o)
    {
        return this->n < o.n;
    }

    bool operator>=(const modular<I, mod> &o)
    {
        return this->n >= o.n;
    }

    bool operator<=(const modular<I, mod> &o)
    {
        return this->n <= o.n;
    }

    bool operator==(const modular<I, mod> &o)
    {
        return this->n == o.n;
    }

    void operator++()
    {
        if (this->n < mod - 1)
        {
            this->n = ((I)1 + this->n);
            return;
        }

        this->n = 0;
    }

    void operator--()
    {
        if (this->n > 0)
        {
            this->n = (this->n - (I)1);
            return;
        }

        this->n = mod - 1;
    }

    void operator++(int)
    {
        if (this->n < mod - 1)
        {
            this->n = ((I)1 + this->n);
            return;
        }

        this->n = 0;
    }

    void operator--(int)
    {
        if (this->n > 0)
        {
            this->n = (this->n - (I)1);
            return;
        }

        this->n = mod - 1;
    }

    modular<I, mod> operator*(const modular<I, mod> &o)
    {
        modular<I, mod> ans;
        ans.n = (this->n * o.n) % mod;
        return ans;
    }

    void operator*=(const modular<I, mod> &o)
    {
        this->n = (this->n * o.n) % mod;
    }

    modular<I, mod> operator/(const modular<I, mod> &o)
    {
        modular<I, mod> ans;
        ans.n = (this->n * o.inverse()) % mod;
        return ans;
    }

    void operator/=(const modular<I, mod> &o)
    {
        this->n = (this->n * o.inverse()) % mod;
    }

    modular<I, mod> operator+(const modular<I, mod> &o)
    {
        modular<I, mod> ans;
        ans.n = (this->n + o.n) % mod;
        return ans;
    }

    void operator+=(const modular<I, mod> &o)
    {
        this->n = (this->n + o.n) % mod;
    }

    modular<I, mod> operator-(const modular<I, mod> &o)
    {
        modular<I, mod> ans;
        ans.n = (this->n + (mod - o.n)) % mod;
        return ans;
    }

    void operator-=(const modular<I, mod> &o)
    {
        this->n = (this->n + (mod - o.n)) % mod;
    }

    void operator>>=(I k)
    {
        this->n >>= k;
    }

    void operator<<=(I k)
    {
        this->n = (this->n << k) % mod;
    }

    modular<I, mod> power(I m)
    {
        modular<I, mod> pr(1), bpr(this->n);
        while (m > 0)
        {
            if (m & 1)
            {
                pr *= bpr;
            }
            m >>= 1;
            bpr *= bpr;
        }

        return pr;
    }

    modular<I, mod> inverse()
    {
        I m = mod - 2;
        modular<I, mod> pr(1), bpr(this->n);
        while (m > 0)
        {
            if (m & 1)
            {
                pr *= bpr;
            }
            m >>= 1;
            bpr *= bpr;
        }

        return pr;
    }

    modular<I, mod> nooverflow(I a, I b)
    {
        I res = 0;
        a = a % mod;
        while (b > 0)
        {
            if (b & 1)
                res = (res + a) % mod;

            a = (a << 1) % mod;

            b >>= 1;
        }

        return res % mod;
    }

    friend ostream &operator<<(ostream &os, const modular<I, mod> &r)
    {
        os << r.n;
        return os;
    }
};
