// FIXME add operators
// FIXME tests
// FIXME add string inputs

#pragma once
#include <vector>
#include <ostream>
#include <math.h>
#include <iomanip>

#include "../utils/new_debug_out.hpp"

namespace baseint
{
    const char __BASE_CHAR[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                        'U', 'V', 'W', 'X', 'Y', 'Z'};
    const int __MAX_BASE = 36;

    template<typename I,bool __CHECK_INRANGE = true>
    bool _CHAR_IS_IN_BASE_CHAR(const char &c,I _B=(I)__MAX_BASE)
    {
        if(__CHECK_INRANGE)
        {
            assert(_B>(I)0&&_B<=(I)__MAX_BASE);
        }
        return (c<='9'&&c>='0')||(c>=__BASE_CHAR[10]&&c<(__BASE_CHAR[10]+_B-10));
    }

    template<typename I,I B,bool __CHECK = true>
    std::string digit_to_base_str(I d)
    {
        if(__CHECK)
        {
            assert(d<B||d>=(I)0);
        }

        std::string s;
        if(B>(I)__MAX_BASE)
        {
            while(d>(I)0)
            {
                s.push_back(__BASE_CHAR[d%((I)__MAX_BASE)]);
                d/=(I)__MAX_BASE;
            }
            std::reverse(s.begin(),s.end());
        }
        else
        {
            s.push_back(__BASE_CHAR[d]);
        }
        return s;
    }

    //TODO optimize check statement
    template<typename I,I B,bool __CHECK = true>
    I str_to_base_digit(const std::string &s)
    {
        I d=-1;
        if(B>(I)__MAX_BASE)
        {
            d=0;
            for(auto c: s)
            {
                if(__CHECK)
                {
                    assert(_CHAR_IS_IN_BASE_CHAR<I>(c));
                }

                d*=B;
                if(c-'0'<10 && c-'0'>=0)
                {
                    d += c-'0';
                }
                else
                {
                    d += (c - __BASE_CHAR[10]) + (I)10;
                }
            }
        }
        else
        {
            if(__CHECK)
            {
                assert((int)s.size()==1);
                if(B>(I)10)
                {
                    assert(_CHAR_IS_IN_BASE_CHAR<I>(s[0]));
                }
                else
                {
                    assert(s[0]<('0'+B)&&s[0]>='0');
                }
            }

            if(s[0]-'0'<10&&s[0]-'0'>=0)
            {
                d = s[0]-'0';
            }
            else
            {
                d = (s[0] -  __BASE_CHAR[10]) + (I)10;
            }
        }
        return d;
    }

    template<typename I>
    constexpr I get_base_representation_length(I B)
    {
        I len = 0;
        B--;
        while(B>0)
        {
            B/=(I)__MAX_BASE;
            len++;
        }
        return len;
    }

    // @tparam `I` type of integer
    // @tparam `B` 2*B^(2) <= max_range(I)
    template <typename I, I B>
    class int_base
    {
    public:
        typedef int_base<I,B> intb;
        std::vector<I> a;
        int sign;

        int_base() : a(1, (I)0), sign(1) {}
        int_base(const std::vector<I> &_a, int _sign) : a(_a), sign(_sign) {}
        void operator=(intb _n)
        {
            this->a.resize(_n.size());
            this->sign = _n.sign;
            for (I i = 0; i < _n.size(); i++)
            {
                this->a[i] = _n.a[i];
            }
        }

        template <class U, class = typename std::enable_if<std::is_integral<U>::value>::type> 
        int_base(const U &__n)
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
                this->a.push_back(_n % B);
                _n /= B;
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
                this->a.push_back(_n % B);
                _n /= B;
            }
        }

        int_base(const std::string &_n)
        {
            I start=0;
            this->sign=1;
            if(_n[0]=='-')
            {
                this->sign = -1;
                start=1;
            }
            else if(_n[0]=='+')
            {
                start=1;
            }

            // FIXME can this be just computed to once per class
            static I len = baseint::get_base_representation_length<I>(B);

            I i = (I)_n.size();
            assert((i-start)%len==0); // string must be multiple of the len of req to represent 1 digit
            i--;
            for(;i>=start;i-=len)
            {
                a.push_back(str_to_base_digit<I,B,true>(_n.substr(i,len)));
            }
        }
        void operator=(const std::string &_n)
        {
            I start=0;
            this->sign=1;
            if(_n[0]=='-')
            {
                this->sign = -1;
                start=1;
            }
            else if(_n[0]=='+')
            {
                start=1;
            }

            // FIXME can this be just computed to once per class
            static I len = baseint::get_base_representation_length<I>(B);

            I i = (I)_n.size();
            assert((i-start)%len==0); // string must be multiple of the len of req to represent 1 digit
            i--;
            for(;i>=start;i-=len)
            {
                a.push_back(str_to_base_digit<I,B,true>(_n.substr(i,len)));
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
                _n *= B;
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

        friend intb abs(const intb &a) { return intb(a.a, 1); }

        // a[0] + a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n - 2^Nn
        // a[0] + a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n - 2^(N-1)n*(2^n-1+1)
        // - [(2^n-a[0]) + (2^n-1-a[1]2^n + a[2]2^2n +....+a[N-1]2^(N-1)n
        friend intb operator+(const intb &a, const intb &b)
        {
            intb ans;
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
                        ans.a[i] += B;
                    }
                }

                if (ans.a[ans.a.size() - 1] < 0)
                {
                    ans.a[ans.a.size() - 1] += B;
                    ans.sign = -1;
                    for (int i = 0; i < ans.a.size(); i++)
                    {
                        ans.a[i] = B - 1 - ans.a[i];
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
                    if (ans.a[i] >= B)
                    {
                        carry = 1;
                        ans.a[i] -= B;
                    }
                    else
                    {
                        carry = 0;
                    }
                }
                for (int i = b.a.size(); (i < ans.a.size()) && (carry > 0); i++)
                {
                    ans.a[i]++;
                    if (ans.a[i] >= B)
                    {
                        carry = 1;
                        ans.a[i] -= B;
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
        friend intb operator+(const intb &a, const U &b) { return a + intb(b); }
        template <typename U>
        friend intb operator+(const U &b, const intb &a) { return a + intb(b); }

        friend intb operator-(const intb &a, const intb &b)
        {
            intb ans;
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
                        ans.a[i] += B;
                    }
                }

                if (ans.a[ans.a.size() - 1] < 0)
                {
                    ans.a[ans.a.size() - 1] += B;
                    ans.sign = -1;
                    for (int i = 0; i < ans.a.size(); i++)
                    {
                        ans.a[i] = B - 1 - ans.a[i];
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
                    if (ans.a[i] >= B)
                    {
                        carry = 1;
                        ans.a[i] -= B;
                    }
                    else
                    {
                        carry = 0;
                    }
                }
                for (int i = b.a.size(); (i < ans.a.size()) && (carry > 0); i++)
                {
                    ans.a[i]++;
                    if (ans.a[i] >= B)
                    {
                        carry = 1;
                        ans.a[i] -= B;
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
        friend intb operator-(const intb &a, const U &b) { return a - intb(b); }
        template <typename U>
        friend intb operator-(const U &b, const intb &a) { return intb(b) - a; }

        bool operator==(const intb &a)
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
        friend bool operator==(const intb &a, const U &b) { return a == intb(b); }
        template <typename U>
        friend bool operator==(const U &b, const intb &a) { return intb(b) == a; }

        friend bool operator<(const intb &b, const intb &a)
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
        friend bool operator<(const intb &a, const U &b) { return a < intb(b); }
        template <typename U>
        friend bool operator<(const U &b, const intb &a) { return intb(b) < a; }

        friend bool operator<=(const intb &b, const intb &a)
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
        friend bool operator<=(const intb &a, const U &b) { return a <= intb(b); }
        template <typename U>
        friend bool operator<=(const U &b, const intb &a) { return intb(b) <= a; }

        friend bool operator>(const intb &b, const intb &a)
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
        friend bool operator>(const intb &a, const U &b) { return a > intb(b); }
        template <typename U>
        friend bool operator>(const U &b, const intb &a) { return intb(b) > a; }

        friend bool operator>=(const intb &b, const intb &a)
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
        friend bool operator>=(const intb &a, const U &b) { return a >= intb(b); }
        template <typename U>
        friend bool operator>=(const U &b, const intb &a) { return intb(b) >= a; }

        void operator+=(const intb &a) { *this = *this + a; }
        template <typename U>
        void operator+=(const U &b) { *this = (*this) + intb(b); }

        void operator-=(const intb &a) { *this = *this - a; }
        template <typename U>
        void operator-=(const U &b) { *this = (*this) - intb(b); }

        void operator++() { *this = *this + intb({(I)1}, 1); }
        void operator++(int) { *this = *this + intb({(I)1}, 1); }
        void operator--() { *this = *this - intb({(I)1}, 1); }
        void operator--(int) { *this = *this - intb({(I)1}, 1); }

        friend intb operator*(const intb &a, const intb &b)
        {
            if (a.a.size() <= 10 || b.a.size() <= 10)
            {
                intb ans;
                ans.a.assign(a.a.size() + b.a.size(), 0);
                for (int i = 0; i < a.a.size(); i++)
                {
                    for (int j = 0; j < b.a.size(); j++)
                    {
                        ans.a[i + j] += b.a[j] * a.a[i];
                        if (ans.a[i + j] >= B)
                        {
                            ans.a[i + j + 1] += ans.a[i + j] / B;
                            ans.a[i + j] %= B;
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

            intb a0, a1, b0, b1;
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

            intb z0 = a0 * b0;
            intb z1 = a1 * b1;
            intb z2 = (a0 + a1) * (b0 + b1) - z0 - z1;
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

            intb ans = z2 + z1 + z0;
            ans.shrink_to_fit();
            return ans;
        }
        template <typename U>
        friend intb operator*(const intb &a, const U &b) { return a * intb(b); }
        template <typename U>
        friend intb operator*(const U &b, const intb &a) { return intb(b) * a; }

        friend intb operator/(intb a, intb b)
        {
            int asign = a.sign;
            a.sign = 1;
            int bsign = b.sign;
            b.sign = 1;
            if (a < b)
            {
                return intb((I)0);
            }
            a.shrink_to_fit();
            b.shrink_to_fit();
            intb q, r;
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
                I low = 0, high = B;
                while (high - low > 1)
                {
                    I mid = (high + low) / 2;
                    intb bmid(mid);
                    intb prod = bmid * b;
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
                intb qi(low);
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
            q = intb(Q, 1);
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
        friend intb operator/(const intb &a, const U &b) { return a / intb(b); }
        template <typename U>
        friend intb operator/(const U &b, const intb &a) { return intb(b) / a; }

        friend intb operator%(intb a, intb b)
        {

            int asign = a.sign;
            a.sign = 1;
            int bsign = b.sign;
            b.sign = 1;
            if (a < b)
            {
                return intb((I)0);
            }
            a.shrink_to_fit();
            b.shrink_to_fit();
            intb q, r;
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
                I low = 0, high = B;

                while (high - low > 1)
                {
                    I mid = (high + low) / 2;
                    intb bmid(mid);
                    intb prod = bmid * b;
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
                intb qi(low);
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
            q = intb(Q, 1);

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
        friend intb operator%(const intb &a, const U &b) { return a % intb(b); }
        template <typename U>
        friend intb operator%(const U &b, const intb &a) { return intb(b) % a; }

        std::pair<intb, intb> div(intb a, intb b)
        {
            int asign = a.sign;
            a.sign = 1;
            int bsign = b.sign;
            b.sign = 1;
            if (a < b)
            {
                return intb((I)0);
            }
            a.shrink_to_fit();
            b.shrink_to_fit();
            intb q, r;
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
                I low = 0, high = B;

                while (high - low > 1)
                {
                    I mid = (high + low) / 2;
                    intb bmid(mid);
                    intb prod = bmid * b;
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
                intb qi(low);
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
            q = intb(Q, 1);

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

        friend std::ostream &operator<<(std::ostream &os, const intb &a)
        {
            if (a.sign == -1)
            {
                os << "-";
            }
            bool first = false;
            for (int i = a.size() - 1; i >= 0; i--)
            {
                os << digit_to_base_str<I,B,false>(a.a[i]);
            }
            return os;
        }
    };

}