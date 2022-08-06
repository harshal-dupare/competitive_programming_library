#pragma once
#include <cmath>
#include <ostream>

namespace real
{
    // fp >=0,fp+ip=x
    template <typename R, R const &eps>
    std::pair<R, R> decompose(R x)
    {
        R ni = std::round(x);
        if (x - ni <= eps&&x - ni >= eps)
            return {0.0, ni};
        R ip, fp;
        if (x >= ni)
            fp = x - ni, ip = ni;
        else
            fp = x - ni + 1, ip = ni - 1;
        return {fp, ip};
    }

    template <typename R, R const &eps>
    inline R normalize(R a)
    {
        if(a<=eps&&a>=-eps)
        {
            return R();
        }
        return a;
    }

    template <typename R,typename I=int>
    R pow(R a, I n)
    {
        R ta = 1;
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

    // @tparam `R` the type of floating point to use
    // @tparam `eps` precision level
    template <typename R, R const &eps>
    class precision_real
    {
    public:
        typedef precision_real<R,eps> prl;
        R n;
        precision_real() {this->n = R(); }
        template <typename U>
        precision_real(const U &x) {this->n = real::normalize<R,eps>((R)x); }
        template <typename U>
        explicit operator U() const { return static_cast<U>(this->n); }

        void operator=(const prl &o) { this->n = o.n; }
        template <typename U>
        void operator=(const U _n) {this->n = real::normalize<R, eps>((R)_n); }

        bool operator>(const prl &o) { return this->n > o.n; }
        template <typename U>
        friend bool operator>(const prl &a, const U &i) { return a.n > real::normalize<R, eps>((R)i); }
        template <typename U>
        friend bool operator>(const U &i, const prl &a) { return real::normalize<R, eps>((R)i) > a.n; }

        bool operator<(const prl &o) { return this->n < o.n; }
        template <typename U>
        friend bool operator<(const prl &a, const U &i) { return a.n < real::normalize<R, eps>((R)i); }
        template <typename U>
        friend bool operator<(const U &i, const prl &a) { return real::normalize<R, eps>((R)i) < a.n; }

        bool operator>=(const prl &o) { return this->n >= o.n; }
        template <typename U>
        friend bool operator>=(const prl &a, const U &i) { return a.n >= real::normalize<R, eps>((R)i); }
        template <typename U>
        friend bool operator>=(const U &i, const prl &a) { return real::normalize<R, eps>((R)i) >= a.n; }

        bool operator<=(const prl &o) { return this->n <= o.n; }
        template <typename U>
        friend bool operator<=(const prl &a, const U &i) { return a.n <= real::normalize<R, eps>((R)i); }
        template <typename U>
        friend bool operator<=(const U &i, const prl &a) { return real::normalize<R, eps>((R)i) <= a.n; }

        bool operator==(const prl &o) { return this->n == o.n; }
        template <typename U>
        friend bool operator==(const prl &a, const U &i) { return a.n == real::normalize<R, eps>((R)i); }
        template <typename U>
        friend bool operator==(const U &i, const prl &a) { return real::normalize<R, eps>((R)i) == a.n; }

        prl operator&(const prl &o)
        {
            prl ans = o;
            ans.n &= this->n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator&(const prl &a, const U &i) { return a & prl(i); }
        template <typename U>
        friend prl operator&(const U &i, const prl &a) { return prl(i)&a; }

        void operator&=(const prl &o) { this->n &= o.n; this->n = real::normalize<R, eps>(this->n); }
        template <typename U>
        void operator&=(const U &i) { this->n &= real::normalize<R, eps>((R)i); this->n = real::normalize<R, eps>(this->n); }

        prl operator^(const prl &o)
        {
            prl ans = o;
            ans.n ^= this->n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator^(const prl &a, const U &i) { return a ^ prl(i); }
        template <typename U>
        friend prl operator^(const U &i, const prl &a) { return prl(i)^a; }

        void operator^=(const prl &o) { this->n ^= o.n; this->n = real::normalize<R, eps>(this->n); }
        template <typename U>
        void operator^=(const U &i) { this->n ^= real::normalize<R, eps>((R)i); this->n = real::normalize<R, eps>(this->n); }

        prl operator|(const prl &o)
        {
            prl ans = *this;
            ans.n |= o.n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator|(const prl &a, const U &i) { return a | prl(i); }
        template <typename U>
        friend prl operator|(const U &i, const prl &a) { return prl(i)|a; }

        void operator|=(const prl &o) { this->n |= o.n; this->n = real::normalize<R, eps>(this->n); }
        template <typename U>
        void operator|=(const U &i) { this->n |= real::normalize<R, eps>((R)i); this->n = real::normalize<R, eps>(this->n); }

        template <typename U>
        void operator>>=(U k) { this->n >>= k; this->n = real::normalize<R, eps>(this->n); }
        template <typename U>
        void operator<<=(U k) { this->n = this->n << k; this->n = real::normalize<R, eps>(this->n); }

        void operator++()
        {
            this->n++;
        }
        void operator--()
        {
            this->n--;
        }
        void operator++(int)
        {
            this->n++;
        }
        void operator--(int)
        {
            this->n--;
        }

        prl operator+(const prl &o)
        {
            prl ans = *this;
            ans.n += o.n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator+(const prl &a, const U &i)
        {
            prl ans = a;
            ans.n += real::normalize<R, eps>((R)i);
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator+(const U &i, const prl &a)
        {
            prl ans;
            ans.n = real::normalize<R, eps>((R)i)+a.n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }

        void operator+=(const prl &o)
        {
            this->n += o.n;
            this->n = real::normalize<R, eps>(this->n);
        }
        template <typename U>
        void operator+=(const U &i)
        {
            this->n += real::normalize<R, eps>((R)i);
            this->n = real::normalize<R, eps>(this->n);
        }

        prl operator-(const prl &o)
        {
            prl ans = (*this);
            ans.n -= o.n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator-(const prl &a, const U &i)
        {
            prl ans = a;
            ans.n -= real::normalize<R, eps>((R)i);
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator-(const U &i, const prl &a)
        {
            prl ans;
            ans.n = real::normalize<R, eps>((R)i);
            ans.n -= a.n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }

        void operator-=(const prl &o)
        {
            this->n -= o.n;
            this->n = real::normalize<R, eps>(this->n);
        }
        template <typename U>
        void operator-=(const U &i)
        {
            this->n -= real::normalize<R, eps>((R)i);
            this->n = real::normalize<R, eps>(this->n);
        }

        prl operator-() const { return prl(-this->n); }

        prl operator*(const prl &o)
        {
            prl ans = *this;
            ans.n*=o.n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator*(const prl &o, const U &i) { return o * prl(i); }
        template <typename U>
        friend prl operator*(const U &i, const prl &o) { return prl(i)*o; }

        void operator*=(const prl &o)
        {
            this->n*=o.n;
            this->n = real::normalize<R, eps>(this->n);
        }
        template <typename U>
        void operator*=(const U &i) { *this *= prl(i); }

        prl operator/(const prl &o)
        {
            prl ans=*this;
            ans.n/=o.n;
            ans.n = real::normalize<R, eps>(ans.n);
            return ans;
        }
        template <typename U>
        friend prl operator/(const U &i, const prl &o) { return prl(i)/o; }

        void operator/=(const prl &o)
        {
            this->n /= o.n;
            this->n = real::normalize<R, eps>(this->n);
        }
        template <typename U>
        void operator/=(const U &i) { *this /= prl(i); }

        friend std::ostream &operator<<(std::ostream &os, const prl &r)
        {
            os << r.n;
            return os;
        }

        std::pair<prl, prl> decompose()
        {
            prl ni(std::round(this->n));
            if (this->n - ni.n <= eps&&this->n - ni.n >= eps)
                return {prl(), prl(ni)};
            prl ip, fp;
            if (this->n >= ni.n)
                fp = *this - ni, ip = ni;
            else
                fp = *this - ni + 1, ip = ni - 1;
            return {fp, ip};
        }
    };

}