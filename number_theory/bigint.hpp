#pragma once
// FIXME tests
#include <vector>
#include <ostream>
#include <math.h>
#include <iomanip>

// Uses 10^n as base
// @tparam `I` type of integer
// @tparam `n` 2*10^(2n) <= max_range(I)
template <typename I, int n>
class bigint
{
    static constexpr I B_max = std::pow((I)10, n);

public:
    typedef bigint<I, n> bint;
    std::vector<I> a;
    int sign;

    bigint() : a(1, (I)0), sign(1) {}
    bigint(const std::vector<I> &_a, int _sign) : a(_a), sign(_sign) {}
    void operator=(bint _n)
    {
        this->a.resize(_n.size());
        this->sign = _n.sign;
        for (I i = 0; i < _n.size(); i++)
        {
            this->a[i] = _n.a[i];
        }
    }

    template <class U, class = typename std::enable_if<std::is_integral<U>::value>::type> 
    bigint(const U &__n)
    {
        I _n = (I)__n;
        if (_n < 0)
        {
            this->sign = -1;
            _n = -_n;
        }
        else if (_n == 0)
        {
            this->sign = 1;
            this->a.push_back(0);
        }
        else
        {
            this->sign = 1;
        }

        while (_n > 0)
        {
            this->a.push_back(_n % B_max);
            _n /= B_max;
        }
    }
    template <class U, class = typename std::enable_if<std::is_integral<U>::value>::type> 
    void operator=(const U &__n)
    {
        I _n = (I)__n;
        this->a.clear();
        if (_n < 0)
        {
            this->sign = -1;
            _n = -_n;
        }
        else if (_n == 0)
        {
            this->sign = 1;
            this->a.push_back(0);
        }
        else
        {
            this->sign = 1;
        }

        while (_n > 0)
        {
            this->a.push_back(_n % B_max);
            _n /= B_max;
        }
    }

    bigint(const std::string &_n)
    {
        int low = 0;
        if (_n[0] == '-')
        {
            low = 1;
            this->sign = -1;
        }
        int i = (int)_n.size() - 1;
        I ai = 0;
        int tn = 0;
        while (i >= low)
        {
            ai *= (I)10;
            ai += (I)(_n[i] - '0');
            i--;
            tn++;
            if (tn == n)
            {
                this->a.push_back(ai);
                ai = 0;
                tn = 0;
            }
        }
    }
    void operator=(const std::string &_n)
    {
        this->a.clear();
        int low = 0;
        if (_n[0] == '-')
        {
            low = 1;
            this->sign = -1;
        }
        int i = (int)_n.size() - 1;
        I ai = 0;
        int tn = 0;
        while (i >= low)
        {
            ai *= (I)10;
            ai += (I)(_n[i] - '0');
            i--;
            tn++;
            if (tn == n)
            {
                this->a.push_back(ai);
                ai = 0;
                tn = 0;
            }
        }
    }

    I operator[](int i) const
    {
        if (i >= this->size() || i < 0)
            return 0;
        return this->a[i];
    }
    I get_int() const
    {
        I _n = 0;
        int i = this->a.size() - 1;
        while (i >= 0)
        {
            _n *= B_max;
            _n += this->a[i];
            i--;
        }
        return this->sign * _n;
    }
    int size() const { return (int)this->a.size(); }
    void shrink_to_fit()
    {
        int i = this->size() - 1;
        while (i > 0 && a[i] == 0)
        {
            this->a.pop_back();
            i--;
        }
    }

    friend bint abs(const bint &a) { return bint(a.a, 1); }

    // a[0] + a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n - 2^Nn
    // a[0] + a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n - 2^(N-1)n*(2^n-1+1)
    // - [(2^n-a[0]) + (2^n-1-a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n
    friend bint operator+(const bint &a, const bint &b)
    {
        bint ans;
        I carry = 0;
        if (a.sign != b.sign)
        {
            if (a.sign == 1)
            {
                ans.a = a.a;
                ans.a.resize(std::max(a.a.size(), b.a.size()), (I)0);
                for (int i = 0; i < b.a.size(); i++)
                {
                    ans.a[i] -= b.a[i];
                }
            }
            else
            {
                ans.a = b.a;
                ans.a.resize(std::max(a.a.size(), b.a.size()), (I)0);
                for (int i = 0; i < a.a.size(); i++)
                {
                    ans.a[i] -= a.a[i];
                }
            }

            for (int i = 0; i < ans.a.size() - 1; i++)
            {
                if (ans.a[i] < 0)
                {
                    ans.a[i + 1]--;
                    ans.a[i] += B_max;
                }
            }

            if (ans.a[ans.a.size() - 1] < 0)
            {
                ans.a[ans.a.size() - 1] += B_max;
                ans.sign = -1;
                for (int i = 0; i < ans.a.size(); i++)
                {
                    ans.a[i] = B_max - 1 - ans.a[i];
                }
                ans.a[0]++;
            }
            else
            {
                ans.sign = 1;
            }
        }
        else
        {
            ans.sign = a.sign;
            ans.a = a.a;
            ans.a.resize(std::max(a.a.size(), b.a.size()), (I)0);
            for (int i = 0; i < b.a.size(); i++)
            {
                ans.a[i] += b.a[i] + carry;
                if (ans.a[i] >= B_max)
                {
                    carry = 1;
                    ans.a[i] -= B_max;
                }
                else
                {
                    carry = 0;
                }
            }
            for (int i = b.a.size(); (i < ans.a.size()) && (carry > 0); i++)
            {
                ans.a[i]++;
                if (ans.a[i] >= B_max)
                {
                    carry = 1;
                    ans.a[i] -= B_max;
                }
                else
                {
                    carry = 0;
                }
            }
            if (carry > 0)
            {
                ans.a.push_back(1);
            }
        }
        return ans;
    }
    template <typename U>
    friend bint operator+(const bint &a, const U &b) { return a + bint(b); }
    template <typename U>
    friend bint operator+(const U &b, const bint &a) { return a + bint(b); }

    friend bint operator-(const bint &a, const bint &b)
    {
        bint ans;
        I carry = 0;
        if (a.sign == b.sign)
        {
            if (a.sign == 1)
            {
                ans.a = a.a;
                ans.a.resize(std::max(a.a.size(), b.a.size()), (I)0);
                for (int i = 0; i < b.a.size(); i++)
                {
                    ans.a[i] -= b.a[i];
                }
            }
            else
            {
                ans.a = b.a;
                ans.a.resize(std::max(a.a.size(), b.a.size()), (I)0);
                for (int i = 0; i < a.a.size(); i++)
                {
                    ans.a[i] -= a.a[i];
                }
            }

            for (int i = 0; i < ans.a.size() - 1; i++)
            {
                if (ans.a[i] < 0)
                {
                    ans.a[i + 1]--;
                    ans.a[i] += B_max;
                }
            }

            if (ans.a[ans.a.size() - 1] < 0)
            {
                ans.a[ans.a.size() - 1] += B_max;
                ans.sign = -1;
                for (int i = 0; i < ans.a.size(); i++)
                {
                    ans.a[i] = B_max - 1 - ans.a[i];
                }
                ans.a[0]++;
            }
            else
            {
                ans.sign = 1;
            }
        }
        else
        {
            ans.sign = a.sign;
            ans.a = a.a;
            ans.a.resize(std::max(a.a.size(), b.a.size()), (I)0);
            for (int i = 0; i < b.a.size(); i++)
            {
                ans.a[i] += b.a[i] + carry;
                if (ans.a[i] >= B_max)
                {
                    carry = 1;
                    ans.a[i] -= B_max;
                }
                else
                {
                    carry = 0;
                }
            }
            for (int i = b.a.size(); (i < ans.a.size()) && (carry > 0); i++)
            {
                ans.a[i]++;
                if (ans.a[i] >= B_max)
                {
                    carry = 1;
                    ans.a[i] -= B_max;
                }
                else
                {
                    carry = 0;
                }
            }
            if (carry > 0)
            {
                ans.a.push_back(1);
            }
        }
        return ans;
    }
    template <typename U>
    friend bint operator-(const bint &a, const U &b) { return a - bint(b); }
    template <typename U>
    friend bint operator-(const U &b, const bint &a) { return bint(b) - a; }

    bool operator==(const bint &a)
    {
        if (a.sign != this->sign)
        {
            return false;
        }
        bool eq = true;
        if (this->size() > a.size())
        {
            for (int i = 0; i < a.size(); i++)
            {
                if (this->a[i] != a.a[i])
                    return false;
            }

            for (int i = a.size(); i < this->size(); i++)
            {
                if (this->a[i] != (I)0)
                    return false;
            }
        }
        else
        {
            for (int i = 0; i < this->size(); i++)
            {
                if (this->a[i] != a.a[i])
                    return false;
            }

            for (int i = this->size(); i < a.size(); i++)
            {
                if (a.a[i] != (I)0)
                    return false;
            }
        }
        return true;
    }
    template <typename U>
    friend bool operator==(const bint &a, const U &b) { return a == bint(b); }
    template <typename U>
    friend bool operator==(const U &b, const bint &a) { return bint(b) == a; }

    friend bool operator<(const bint &b, const bint &a)
    {
        int i = a.size() - 1;
        if (a.size() > b.size())
        {
            for (i = a.size() - 1; i >= b.size(); i--)
            {
                if (a.a[i] > 0)
                {
                    return a.sign == 1;
                }
            }
        }
        else
        {
            for (i = b.size() - 1; i >= a.size(); i--)
            {
                if (b.a[i] > 0)
                {
                    return b.sign == -1;
                }
            }
        }

        for (; i >= 0; i--)
        {
            if (b.a[i] < a.a[i])
            {
                return a.sign == 1;
            }
            else if (b.a[i] > a.a[i])
            {
                return b.sign == -1;
            }
        }

        return false;
    }
    template <typename U>
    friend bool operator<(const bint &a, const U &b) { return a < bint(b); }
    template <typename U>
    friend bool operator<(const U &b, const bint &a) { return bint(b) < a; }

    friend bool operator<=(const bint &b, const bint &a)
    {
        if (a == b)
        {
            return true;
        }

        int i = a.size() - 1;
        if (a.a.size() > b.size())
        {
            for (i = a.size() - 1; i >= b.size(); i--)
            {
                if (a.a[i] > 0)
                {
                    return a.sign == 1;
                }
            }
        }
        else
        {
            for (i = b.size() - 1; i >= a.size(); i--)
            {
                if (b.a[i] > 0)
                {
                    return b.sign == -1;
                }
            }
        }

        for (; i >= 0; i--)
        {
            if (b.a[i] < a.a[i])
            {
                return a.sign == 1;
            }
            else if (b.a[i] > a.a[i])
            {
                return b.sign == -1;
            }
        }

        return false;
    }
    template <typename U>
    friend bool operator<=(const bint &a, const U &b) { return a <= bint(b); }
    template <typename U>
    friend bool operator<=(const U &b, const bint &a) { return bint(b) <= a; }

    friend bool operator>(const bint &b, const bint &a)
    {
        int i;
        if (b.size() > a.size())
        {
            for (i = b.size() - 1; i >= a.size(); i--)
            {
                if (b.a[i] > 0)
                {
                    return b.sign == 1;
                }
            }
        }
        else
        {
            for (i = a.size() - 1; i >= b.size(); i--)
            {
                if (a.a[i] > 0)
                {
                    return a.sign == -1;
                }
            }
        }

        for (; i >= 0; i--)
        {
            if (a.a[i] < b.a[i])
            {
                return b.sign == 1;
            }
            else if (a.a[i] > b.a[i])
            {
                return a.sign == -1;
            }
        }

        return false;
    }
    template <typename U>
    friend bool operator>(const bint &a, const U &b) { return a > bint(b); }
    template <typename U>
    friend bool operator>(const U &b, const bint &a) { return bint(b) > a; }

    friend bool operator>=(const bint &b, const bint &a)
    {
        if (a == b)
        {
            return true;
        }
        int i;
        if (b.size() > a.size())
        {
            for (i = b.size() - 1; i >= a.size(); i--)
            {
                if (b.a[i] > 0)
                {
                    return b.sign == 1;
                }
            }
        }
        else
        {
            for (i = a.size() - 1; i >= b.size(); i--)
            {
                if (a.a[i] > 0)
                {
                    return a.sign == -1;
                }
            }
        }

        for (; i >= 0; i--)
        {
            if (a.a[i] < b.a[i])
            {
                return b.sign == 1;
            }
            else if (a.a[i] > b.a[i])
            {
                return a.sign == -1;
            }
        }

        return false;
    }
    template <typename U>
    friend bool operator>=(const bint &a, const U &b) { return a >= bint(b); }
    template <typename U>
    friend bool operator>=(const U &b, const bint &a) { return bint(b) >= a; }

    void operator+=(const bint &a) { *this = *this + a; }
    template <typename U>
    void operator+=(const U &b) { *this = (*this) + bint(b); }

    void operator-=(const bint &a) { *this = *this - a; }
    template <typename U>
    void operator-=(const U &b) { *this = (*this) - bint(b); }

    void operator++() { *this = *this + bint({(I)1}, 1); }
    void operator++(int) { *this = *this + bint({(I)1}, 1); }
    void operator--() { *this = *this - bint({(I)1}, 1); }
    void operator--(int) { *this = *this - bint({(I)1}, 1); }

    friend bint operator*(const bint &a, const bint &b)
    {
        if (a.a.size() <= 10 || b.a.size() <= 10)
        {
            bint ans;
            ans.a.assign(a.a.size() + b.a.size(), 0);
            for (int i = 0; i < a.a.size(); i++)
            {
                for (int j = 0; j < b.a.size(); j++)
                {
                    ans.a[i + j] += b.a[j] * a.a[i];
                    if (ans.a[i + j] >= B_max)
                    {
                        ans.a[i + j + 1] += ans.a[i + j] / B_max;
                        ans.a[i + j] %= B_max;
                    }
                }
            }

            ans.shrink_to_fit();
            if (ans.a.size() == 1 && ans.a[0] == 0)
            {
                ans.sign = 1;
            }
            else
            {
                ans.sign = a.sign * b.sign;
            }

            return ans;
        }

        bint a0, a1, b0, b1;
        int m = (std::max(a.size(), b.size())) / 2;
        int i;
        for (i = 0; i < std::min(a.size(), m); i++)
        {
            a0.a.push_back(a.a[i]);
        }
        for (; i < a.a.size(); i++)
        {
            a1.a.push_back(a.a[i]);
        }
        a0.sign = a.sign;
        a1.sign = a.sign;

        for (i = 0; i < std::min(b.size(), m); i++)
        {
            b0.a.push_back(b.a[i]);
        }
        for (; i < b.a.size(); i++)
        {
            b1.a.push_back(b.a[i]);
        }
        b0.sign = b.sign;
        b1.sign = b.sign;

        bint z0 = a0 * b0;
        bint z1 = a1 * b1;
        bint z2 = (a0 + a1) * (b0 + b1) - z0 - z1;
        int nz2 = z2.size() - 1;
        int nz1 = z1.size() - 1;
        z2.a.resize(z2.size() + m * 2, 0);
        while (nz2--)
        {
            z2.a[nz2 + 2 * m] = z2.a[nz2];
        }
        z1.a.resize(z1.size() + m, 0);
        while (nz1--)
        {
            z1.a[nz1 + m] = z1.a[nz1];
        }

        bint ans = z2 + z1 + z0;
        ans.shrink_to_fit();
        return ans;
    }
    template <typename U>
    friend bint operator*(const bint &a, const U &b) { return a * bint(b); }
    template <typename U>
    friend bint operator*(const U &b, const bint &a) { return bint(b) * a; }

    friend bint operator/(bint a, bint b)
    {
        int asign = a.sign;
        a.sign = 1;
        int bsign = b.sign;
        b.sign = 1;
        if (a < b)
        {
            return bint((I)0);
        }
        a.shrink_to_fit();
        b.shrink_to_fit();
        bint q, r;
        r.a[0] = a.a[a.size() - 1];
        r.sign = 1;
        int i = a.size() - 2;
        while (r < b)
        {
            r.a.push_back(0);
            for (int j = r.size() - 1; j > 0; j--)
            {
                r.a[j] = r.a[j - 1];
            }
            r.a[0] = a.a[i];
            i--;
        }

        std::vector<I> Q;
        while (!(r < b))
        {
            I low = 0, high = B_max;
            while (high - low > 1)
            {
                I mid = (high + low) / 2;
                bint bmid(mid);
                bint prod = bmid * b;
                if (prod < r)
                {
                    low = bmid.get_int();
                }
                else if (prod == r)
                {
                    low = bmid.get_int();
                    high = low;
                    break;
                }
                else
                {
                    high = bmid.get_int();
                }
            }
            bint qi(low);
            Q.push_back(low);
            r = r - b * qi;
            r.shrink_to_fit();
            while (i >= 0)
            {
                r.a.push_back(0);
                for (int j = r.size() - 1; j > 0; j--)
                {
                    r.a[j] = r.a[j - 1];
                }
                r.a[0] = a.a[i];
                i--;
                if (r < b)
                {
                    Q.push_back((I)0);
                }
                else
                {
                    break;
                }
            }
        }

        reverse(Q.begin(), Q.end());
        q = bint(Q, 1);
        q.sign = asign * bsign;
        r.shrink_to_fit();
        if (r.size() == 1 && r.a[0] == 0)
        {
            r.sign = 1;
        }
        {
            r.sign = asign;
        }
        return q;
    }
    template <typename U>
    friend bint operator/(const bint &a, const U &b) { return a / bint(b); }
    template <typename U>
    friend bint operator/(const U &b, const bint &a) { return bint(b) / a; }

    friend bint operator%(bint a, bint b)
    {

        int asign = a.sign;
        a.sign = 1;
        int bsign = b.sign;
        b.sign = 1;
        if (a < b)
        {
            return bint((I)0);
        }
        a.shrink_to_fit();
        b.shrink_to_fit();
        bint q, r;
        r.a[0] = a.a[a.a.size() - 1];
        r.sign = 1;
        int i = a.a.size() - 2;
        while (r < b)
        {
            r.a.push_back(0);
            for (int j = r.a.size() - 1; j > 0; j--)
            {
                r.a[j] = r.a[j - 1];
            }
            r.a[0] = a.a[i];
            i--;
        }

        std::vector<I> Q;
        while (!(r < b))
        {
            I low = 0, high = B_max;

            while (high - low > 1)
            {
                I mid = (high + low) / 2;
                bint bmid(mid);
                bint prod = bmid * b;
                if (prod < r)
                {
                    low = bmid.get_int();
                }
                else if (prod == r)
                {
                    low = bmid.get_int();
                    high = low;
                    break;
                }
                else
                {
                    high = bmid.get_int();
                }
            }
            bint qi(low);
            Q.push_back(low);

            r = r - b * qi;
            r.shrink_to_fit();

            while (i >= 0)
            {
                r.a.push_back(0);
                for (int j = r.a.size() - 1; j > 0; j--)
                {
                    r.a[j] = r.a[j - 1];
                }
                r.a[0] = a.a[i];
                i--;

                if (r < b)
                {
                    Q.push_back((I)0);
                }
                else
                {
                    break;
                }
            }
        }

        reverse(Q.begin(), Q.end());
        q = bint(Q, 1);

        q.sign = asign * bsign;
        r.shrink_to_fit();
        if (r.a.size() == 1 && r.a[0] == 0)
        {
            r.sign = 1;
        }
        {
            r.sign = asign;
        }

        return r;
    }
    template <typename U>
    friend bint operator%(const bint &a, const U &b) { return a % bint(b); }
    template <typename U>
    friend bint operator%(const U &b, const bint &a) { return bint(b) % a; }

    std::pair<bint, bint> div(bint a, bint b)
    {
        int asign = a.sign;
        a.sign = 1;
        int bsign = b.sign;
        b.sign = 1;
        if (a < b)
        {
            return bint((I)0);
        }
        a.shrink_to_fit();
        b.shrink_to_fit();
        bint q, r;
        r.a[0] = a.a[a.a.size() - 1];
        r.sign = 1;
        int i = a.a.size() - 2;
        while (r < b)
        {
            r.a.push_back(0);
            for (int j = r.a.size() - 1; j > 0; j--)
            {
                r.a[j] = r.a[j - 1];
            }
            r.a[0] = a.a[i];
            i--;
        }

        std::vector<I> Q;
        while (!(r < b))
        {
            I low = 0, high = B_max;

            while (high - low > 1)
            {
                I mid = (high + low) / 2;
                bint bmid(mid);
                bint prod = bmid * b;
                if (prod < r)
                {
                    low = bmid.get_int();
                }
                else if (prod == r)
                {
                    low = bmid.get_int();
                    high = low;
                    break;
                }
                else
                {
                    high = bmid.get_int();
                }
            }
            bint qi(low);
            Q.push_back(low);

            r = r - b * qi;
            r.shrink_to_fit();

            while (i >= 0)
            {
                r.a.push_back(0);
                for (int j = r.a.size() - 1; j > 0; j--)
                {
                    r.a[j] = r.a[j - 1];
                }
                r.a[0] = a.a[i];
                i--;

                if (r < b)
                {
                    Q.push_back((I)0);
                }
                else
                {
                    break;
                }
            }
        }

        reverse(Q.begin(), Q.end());
        q = bint(Q, 1);

        q.sign = asign * bsign;
        r.shrink_to_fit();
        if (r.a.size() == 1 && r.a[0] == 0)
        {
            r.sign = 1;
        }
        {
            r.sign = asign;
        }

        return std::make_pair(q, r);
    }

    friend std::ostream &operator<<(std::ostream &os, const bint &a)
    {
        if (a.sign == -1)
        {
            os << "-";
        }
        bool first = false;
        for (int i = a.size() - 1; i >= 0; i--)
        {
            if (first)
            {
                os << std::setfill('0') << std::setw(n) << a.a[i];
            }
            else if (a.a[i] > 0)
            {
                os << a.a[i];
                first = true;
            }
        }
        if (!first)
        {
            os << '0';
        }
        return os;
    }
};
