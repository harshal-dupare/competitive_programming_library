#pragma once

#include <vector>
#include <iostream>

// 10^n as base and N base-bit long storing ints as I type
template <typename I, int n>
class bigint
{
    const static I B_max = pow((I)10, n);

public:
    std::vector<I> a;

    int sign;
    bigint()
    {
        this->a.assign(1, (I)0);
        this->sign = 1;
    }
    bigint(std::vector<I> _a, int _sign)
    {
        this->a.resize(_a.size());
        this->sign = _sign;
        for (int i = 0; i < _a.size(); i++)
        {
            this->a[i] = _a[i];
        }
    }
    bigint(I _n)
    {
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
    bigint(string &_n)
    {
        int low = 0;
        if (_n[0] == '-')
        {
            low = 1;
            this->sign = -1;
        }
        int i = _n.size() - 1;
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

    void operator=(I _n)
    {
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

    void operator=(string &_n)
    {
        this->a.clear();
        int low = 0;
        if (_n[0] == '-')
        {
            low = 1;
            this->sign = -1;
        }
        int i = _n.size() - 1;
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

    // a[0] + a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n - 2^Nn
    // a[0] + a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n - 2^(N-1)n*(2^n-1+1)
    // - [(2^n-a[0]) + (2^n-1-a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n

    void shrink_to_fit()
    {
        int i = this->a.size() - 1;
        while (i > 0 && a[i] == 0)
        {
            this->a.pop_back();
            i--;
        }
    }

    I get_int()
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

    int size()
    {
        return this->a.size();
    }

    friend bigint<I, n> abs(bigint<I, n> &a)
    {
        return bigint<I, n>(a.a, 1);
    }

    friend bigint<I, n> operator+(const bigint<I, n> &a, const bigint<I, n> &b)
    {
        bigint<I, n> ans;
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

    friend bigint<I, n> operator-(const bigint<I, n> &a, const bigint<I, n> &b)
    {
        bigint<I, n> ans;
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

    friend bigint<I, n> operator*(const bigint<I, n> &a, const bigint<I, n> &b)
    {
        if (a.a.size() <= 10 || b.a.size() <= 10)
        {
            bigint<I, n> ans;
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

        bigint<I, n> a0, a1, b0, b1;
        int m = (std::max(a.a.size(), b.a.size())) / 2;
        int i;
        for (i = 0; i < std::min((int)a.a.size(), m); i++)
        {
            a0.a.push_back(a.a[i]);
        }
        for (; i < a.a.size(); i++)
        {
            a1.a.push_back(a.a[i]);
        }
        a0.sign = a.sign;
        a1.sign = a.sign;

        for (i = 0; i < std::min((int)b.a.size(), m); i++)
        {
            b0.a.push_back(b.a[i]);
        }
        for (; i < b.a.size(); i++)
        {
            b1.a.push_back(b.a[i]);
        }
        b0.sign = b.sign;
        b1.sign = b.sign;

        bigint<I, n> z0 = a0 * b0;
        bigint<I, n> z1 = a1 * b1;
        bigint<I, n> z2 = (a0 + a1) * (b0 + b1) - z0 - z1;
        int nz2 = z2.a.size() - 1;
        int nz1 = z1.a.size() - 1;
        z2.a.resize(z2.a.size() + m * 2, 0);
        while (nz2--)
        {
            z2.a[nz2 + 2 * m] = z2.a[nz2];
        }
        z1.a.resize(z1.a.size() + m, 0);
        while (nz1--)
        {
            z1.a[nz1 + m] = z1.a[nz1];
        }

        bigint<I, n> ans = z2 + z1 + z0;
        ans.shrink_to_fit();
        return ans;
    }

    friend bigint<I, n> operator/(bigint<I, n> a, bigint<I, n> b)
    {

        int asign = a.sign;
        a.sign = 1;
        int bsign = b.sign;
        b.sign = 1;
        if (a < b)
        {
            return bigint<I, n>((I)0);
        }
        a.shrink_to_fit();
        b.shrink_to_fit();
        bigint<I, n> q, r;
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
                bigint<I, n> bmid(mid);
                bigint<I, n> prod = bmid * b;
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
            bigint<I, n> qi(low);
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
        q = bigint<I, n>(Q, 1);

        q.sign = asign * bsign;
        r.shrink_to_fit();
        if (r.a.size() == 1 && r.a[0] == 0)
        {
            r.sign = 1;
        }
        {
            r.sign = asign;
        }

        return q;
    }

    friend bigint<I, n> operator%(bigint<I, n> a, bigint<I, n> b)
    {

        int asign = a.sign;
        a.sign = 1;
        int bsign = b.sign;
        b.sign = 1;
        if (a < b)
        {
            return bigint<I, n>((I)0);
        }
        a.shrink_to_fit();
        b.shrink_to_fit();
        bigint<I, n> q, r;
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
                bigint<I, n> bmid(mid);
                bigint<I, n> prod = bmid * b;
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
            bigint<I, n> qi(low);
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
        q = bigint<I, n>(Q, 1);

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

    I operator[](int i)
    {
        if (i >= this->a.size() || i < 0)
        {
            return 0;
        }

        return this->a[i];
    }

    std::pair<bigint<I, n>, bigint<I, n>> div(bigint<I, n> a, bigint<I, n> b)
    {
        int asign = a.sign;
        a.sign = 1;
        int bsign = b.sign;
        b.sign = 1;
        if (a < b)
        {
            return bigint<I, n>((I)0);
        }
        a.shrink_to_fit();
        b.shrink_to_fit();
        bigint<I, n> q, r;
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
                bigint<I, n> bmid(mid);
                bigint<I, n> prod = bmid * b;
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
            bigint<I, n> qi(low);
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
        q = bigint<I, n>(Q, 1);

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

    bool operator==(bigint<I, n> &a)
    {
        if (a.sign != this->sign)
        {
            return false;
        }
        this->shrink_to_fit();
        a.shrink_to_fit();
        return a.a == this->a;
    }

    friend bool operator<(const bigint<I, n> &b, const bigint<I, n> &a)
    {
        int i = a.a.size() - 1;
        if (a.a.size() > b.a.size())
        {
            for (i = a.a.size() - 1; i >= b.a.size(); i--)
            {
                if (a.a[i] > 0)
                {
                    return a.sign == 1;
                }
            }
        }
        else
        {
            for (i = b.a.size() - 1; i >= a.a.size(); i--)
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

    friend bool operator<=(const bigint<I, n> &b, const bigint<I, n> &a)
    {
        if (a == b)
        {
            return true;
        }

        int i = a.a.size() - 1;
        if (a.a.size() > b.a.size())
        {
            for (i = a.a.size() - 1; i >= b.a.size(); i--)
            {
                if (a.a[i] > 0)
                {
                    return a.sign == 1;
                }
            }
        }
        else
        {
            for (i = b.a.size() - 1; i >= a.a.size(); i--)
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

    friend bool operator>(const bigint<I, n> &b, const bigint<I, n> &a)
    {
        int i;
        if (b.a.size() > a.a.size())
        {
            for (i = b.a.size() - 1; i >= a.a.size(); i--)
            {
                if (b.a[i] > 0)
                {
                    return b.sign == 1;
                }
            }
        }
        else
        {
            for (i = a.a.size() - 1; i >= b.a.size(); i--)
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

    friend bool operator>=(const bigint<I, n> &b, const bigint<I, n> &a)
    {
        if (a == b)
        {
            return true;
        }
        int i;
        if (b.a.size() > a.a.size())
        {
            for (i = b.a.size() - 1; i >= a.a.size(); i--)
            {
                if (b.a[i] > 0)
                {
                    return b.sign == 1;
                }
            }
        }
        else
        {
            for (i = a.a.size() - 1; i >= b.a.size(); i--)
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

    void operator+=(const bigint<I, n> &a)
    {
        *this = *this + a;
    }

    void operator-=(const bigint<I, n> &a)
    {
        *this = *this - a;
    }

    void operator+=(I a)
    {
        *this = *this + bigint<I, n>(a);
    }

    void operator-=(I a)
    {
        *this = *this - bigint<I, n>(a);
    }

    void operator++()
    {
        bigint<I, n> one({(I)1}, 1);
        *this = *this + one;
    }

    void operator++(int)
    {
        bigint<I, n> one({(I)1}, 1);
        *this = *this + one;
    }

    void operator--()
    {
        bigint<I, n> one({(I)1}, 1);
        *this = *this - one;
    }

    void operator--(int)
    {
        bigint<I, n> one({(I)1}, 1);
        *this = *this - one;
    }

    friend ostream &operator<<(ostream &os, const bigint<I, n> &a)
    {
        if (a.sign == -1)
        {
            os << "-";
        }
        bool first = false;
        for (int i = a.a.size() - 1; i >= 0; i--)
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
