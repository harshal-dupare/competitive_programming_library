#pragma once
#include <ostream>

namespace Zmod
{
    template <typename I, I mod>
    inline I normalize(I a)
    {
        if (!(a >= 0 && a < mod))
            a %= mod;
        if (a < 0)
            a += mod;
        return a;
    }

    // @tparam `inrange` if true then ensures that `0 <= output < mod`
    template <typename I, I mod, bool inrange = true>
    I inverse(I a)
    {
        I u = 0, v = 1;
        I m = mod;
        while (a != 0)
        {
            I t = m / a;
            m -= t * a;
            std::swap(a, m);
            u -= t * v;
            std::swap(u, v);
        }
        assert(m == 1);
        if (inrange)
        {
            u %= mod;
            if (u < 0)
                u += mod;
        }
        return u;
    }

    template <typename I>
    I pow(I a, I n)
    {
        I ta = 1;
        while (n > 0)
        {
            if (n & 1)
            {
                ta *= a;
            }
            n >>= 1;
            a *= a;
        }
        return ta;
    }

    // @tparam `I` the type of integer to use
    // @tparam `mod` 2*mod < max_range(I) necessary, mod^2 < max_range(I) for no overflow
    // @tparam `AVOID_OVERFLOW` if true avoids overflow but gives `log(mod)` extra factor for * & /
    template <typename I, I mod, bool AVOID_OVERFLOW = false>
    class modular
    {
    public:
        typedef modular<I, mod, AVOID_OVERFLOW> mint;
        I n;
        modular() { this->n = 0; }
        template <typename U>
        modular(const U &x) { this->n = Zmod::normalize<I, mod>((I)x); }
        template <typename U>
        explicit operator U() const { return static_cast<U>(this->n); }

        void operator=(const mint &o) { this->n = o.n; }
        template <typename U>
        void operator=(const U _n) { this->n = Zmod::normalize<I, mod>((I)_n); }

        bool operator>(const mint &o) { return this->n > o.n; }
        template <typename U>
        friend bool operator>(const mint &a, const U &i) { return a.n > Zmod::normalize<I, mod>((I)i); }
        template <typename U>
        friend bool operator>(const U &i, const mint &a) { return Zmod::normalize<I, mod>((I)i) > a.n; }

        bool operator<(const mint &o) { return this->n < o.n; }
        template <typename U>
        friend bool operator<(const mint &a, const U &i) { return a.n < Zmod::normalize<I, mod>((I)i); }
        template <typename U>
        friend bool operator<(const U &i, const mint &a) { return Zmod::normalize<I, mod>((I)i) < a.n; }

        bool operator>=(const mint &o) { return this->n >= o.n; }
        template <typename U>
        friend bool operator>=(const mint &a, const U &i) { return a.n >= Zmod::normalize<I, mod>((I)i); }
        template <typename U>
        friend bool operator>=(const U &i, const mint &a) { return Zmod::normalize<I, mod>((I)i) >= a.n; }

        bool operator<=(const mint &o) { return this->n <= o.n; }
        template <typename U>
        friend bool operator<=(const mint &a, const U &i) { return a.n <= Zmod::normalize<I, mod>((I)i); }
        template <typename U>
        friend bool operator<=(const U &i, const mint &a) { return Zmod::normalize<I, mod>((I)i) <= a.n; }

        bool operator==(const mint &o) { return this->n == o.n; }
        template <typename U>
        friend bool operator==(const mint &a, const U &i) { return a.n == Zmod::normalize<I, mod>((I)i); }
        template <typename U>
        friend bool operator==(const U &i, const mint &a) { return Zmod::normalize<I, mod>((I)i) == a.n; }

        mint operator&(const mint &o)
        {
            mint ans = o;
            ans.n &= this->n;
            return ans;
        }
        template <typename U>
        friend mint operator&(const mint &a, const U &i) { return a & mint(i); }
        template <typename U>
        friend mint operator&(const U &i, const mint &a) { return mint(i)&a; }

        void operator&=(const mint &o) { this->n &= o.n; }
        template <typename U>
        void operator&=(const U &i) { this->n &= Zmod::normalize<I, mod>((I)i); }

        mint operator^(const mint &o)
        {
            mint ans = o;
            ans.n ^= this->n;
            return ans;
        }
        template <typename U>
        friend mint operator^(const mint &a, const U &i) { return a ^ mint(i); }
        template <typename U>
        friend mint operator^(const U &i, const mint &a) { return mint(i)^a; }

        void operator^=(const mint &o) { this->n ^= o.n; }
        template <typename U>
        void operator^=(const U &i) { this->n ^= Zmod::normalize<I, mod>((I)i); }

        mint operator|(const mint &o)
        {
            mint ans = o;
            ans.n |= this->n;
            return ans;
        }
        template <typename U>
        friend mint operator|(const mint &a, const U &i) { return a | mint(i); }
        template <typename U>
        friend mint operator|(const U &i, const mint &a) { return mint(i)|a; }

        void operator|=(const mint &o) { this->n |= o.n; }
        template <typename U>
        void operator|=(const U &i) { this->n |= Zmod::normalize<I, mod>((I)i); }

        template <typename U>
        void operator>>=(U k) { this->n >>= k; }
        template <typename U>
        void operator<<=(U k) { this->n = (this->n << k) % mod; }

        void operator++()
        {
            this->n++;
            if (this->n == mod)
                this->n = 0;
        }
        void operator--()
        {
            if (this->n == (I)0)
                this->n = mod;
            this->n--;
        }
        void operator++(int)
        {
            this->n++;
            if (this->n == mod)
                this->n = 0;
        }
        void operator--(int)
        {
            if (this->n == (I)0)
                this->n = mod;
            this->n--;
        }

        mint operator+(const mint &o)
        {
            mint ans = o;
            ans.n += this->n;
            if (ans.n >= mod)
                ans.n -= mod;
            return ans;
        }
        template <typename U>
        friend mint operator+(const mint &a, const U &i)
        {
            mint ans = a;
            ans.n += Zmod::normalize<I, mod>((I)i);
            if (ans.n >= mod)
                ans.n -= mod;
            return ans;
        }
        template <typename U>
        friend mint operator+(const U &i, const mint &a)
        {
            mint ans = a;
            ans.n += Zmod::normalize<I, mod>((I)i);
            if (ans.n >= mod)
                ans.n -= mod;
            return ans;
        }

        void operator+=(const mint &o)
        {
            this->n += o.n;
            if (this->n >= mod)
                this->n -= mod;
        }
        template <typename U>
        void operator+=(const U &i)
        {
            this->n += Zmod::normalize<I, mod>((I)i);
            if (this->n >= mod)
                this->n -= mod;
        }

        mint operator-(const mint &o)
        {
            mint ans = (*this);
            ans.n += (mod - o.n);
            if (ans.n >= mod)
                ans.n -= mod;
            return ans;
        }
        template <typename U>
        friend mint operator-(const mint &a, const U &i)
        {
            mint ans = a;
            ans.n -= Zmod::normalize<I, mod>((I)i);
            if (ans.n < (I)0)
                ans.n += mod;
            return ans;
        }
        template <typename U>
        friend mint operator-(const U &i, const mint &a)
        {
            mint ans = a;
            ans.n -= Zmod::normalize<I, mod>((I)i);
            if (ans.n < (I)0)
                ans.n += mod;
            return ans;
        }

        void operator-=(const mint &o)
        {
            this->n -= o.n;
            if (this->n < (I)0)
                this->n += mod;
        }
        template <typename U>
        void operator-=(const U &i)
        {
            this->n -= Zmod::normalize<I, mod>((I)i);
            if (this->n < (I)0)
                this->n += mod;
        }

        mint operator-() const { return mint(mod - this->n); }

        // may have incresed log(mod) factor if mod^2 > range(I)
        mint operator*(const mint &o)
        {
            mint ans;
            // O(log(mod)) extra factor for every multiply
            if (AVOID_OVERFLOW)
            {
                I an = 0;
                I on = o.n;
                I tn = this->n;
                while (on)
                {
                    if (on & (I)1)
                    {
                        an += tn;
                        if (an >= mod)
                            an -= mod;
                    }
                    tn += tn;
                    if (tn >= mod)
                        tn -= mod;
                    on >>= 1;
                }
                ans.n = an;
            }
            else
            {
                ans.n = (this->n * o.n) % mod;
                if (ans.n < 0)
                    ans.n += mod;
            }
            return ans;
        }
        template <typename U>
        friend mint operator*(const mint &o, const U &i) { return o * mint(i); }
        template <typename U>
        friend mint operator*(const U &i, const mint &o) { return mint(i)*o; }

        // may have incresed log(mod) factor if mod^2 > range(I)
        void operator*=(const mint &o)
        {
            if (AVOID_OVERFLOW)
            {
                // O(log(mod)) extra factor for every multiply
                I on = o.n;
                I tn = this->n;
                this->n = 0;
                while (on)
                {
                    if (on & (I)1)
                    {
                        this->n += tn;
                        if (this->n >= mod)
                            this->n -= mod;
                    }
                    tn += tn;
                    if (tn >= mod)
                        tn -= mod;
                    on >>= 1;
                }
            }
            else
            {
                this->n = (this->n * o.n) % mod;
                if (this->n < 0)
                    this->n += mod;
            }
        }
        template <typename U>
        void operator*=(const U &i) { *this = (*this) * mint(i); }

        // may have incresed log(mod) factor if mod^2 > range(I)
        mint operator/(const mint &o)
        {
            mint ans(Zmod::inverse<I, mod,false>(o.n));
            ans *= (*this);
            return ans;
        }
        template <typename U>
        friend mint operator/(const U &i, const mint &o) { return mint(i)/o; }

        // may have incresed log(mod) factor if mod^2 > range(I)
        void operator/=(const mint &o)
        {
            this->n *= mint(Zmod::inverse<I, mod>(o.n));
            if (this->n < 0)
                this->n += mod;
        }
        template <typename U>
        void operator/=(const U &i) { *this = (*this) / mint(i); }

        friend std::ostream &operator<<(std::ostream &os, const mint &r)
        {
            os << r.n;
            return os;
        }
    };

}