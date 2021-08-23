#pragma once
// FIXME add operators
#include <bits/stdc++.h>

#include "../utils/debug_out.hpp"

using namespace std;

char __BASE_CHAR[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

template <typename I, int B>
class int_base
{
public:
    string n;
    int_base()
    {
    }

    int_base(string &s)
    {
        n = s;
    }

    int_base(I _n)
    {
        n.clear();
        while (_n > 0)
        {
            n += __BASE_CHAR[_n % B];
            _n /= B;
        }
        reverse(n.begin(), n.end());
    }

    int_base<I, B> operator+(const int_base<I, B> &o)
    {
        int_base<I, B> op;
        I i = this->n.size() - 1, j = o.n.size() - 1;
        I tp, c = 0;
        while (i >= 0 && j >= 0)
        {
            tp = (this->n[i] - '0') + (o.n[j] - '0') + c;
            c = tp / B;
            tp %= B;
            op.n += __BASE_CHAR[tp];
            i--;
            j--;
        }
        if (i >= 0)
        {
            while (i >= 0)
            {
                tp = (this->n[i] - '0') + c;
                c = tp / B;
                tp %= B;
                op.n += __BASE_CHAR[tp];
                i--;
            }
        }
        if (j >= 0)
        {
            while (j >= 0)
            {
                tp = (o.n[j] - '0') + c;
                c = tp / B;
                tp %= B;
                op.n += __BASE_CHAR[tp];
                j--;
            }
        }
        if (c > 0)
        {
            op.n += '0' + c;
        }
        reverse(op.n.begin(), op.n.end());
        return op;
    }

    void operator+=(const int_base<I, B> &o)
    {
        string _n;
        I i = this->n.size() - 1, j = o.n.size() - 1;
        I tp, c = 0;
        while (i >= 0 && j >= 0)
        {
            tp = (this->n[i] - '0') + (o.n[j] - '0') + c;
            c = tp / B;
            tp %= B;
            _n += __BASE_CHAR[tp];
            i--;
            j--;
        }
        if (i >= 0)
        {
            while (i >= 0)
            {
                tp = (this->n[i] - '0') + c;
                c = tp / B;
                tp %= B;
                _n += __BASE_CHAR[tp];
                i--;
            }
        }
        if (j >= 0)
        {
            while (j >= 0)
            {
                tp = (o.n[j] - '0') + c;
                c = tp / B;
                tp %= B;
                _n += __BASE_CHAR[tp];
                j--;
            }
        }
        if (c > 0)
        {
            _n += '0' + c;
        }
        reverse(_n.begin(), _n.end());
        this->n = _n;
    }

    int_base<I, B> operator-(const int_base<I, B> &o)
    {
        int_base<I, B> op;
        I i = this->n.size() - 1, j = o.n.size() - 1;
        I tp, c = 0;
        while (i >= 0 && j >= 0)
        {
            tp = (this->n[i] - '0') - (o.n[j] - '0') + c;
            c = tp / B;
            tp = (B + tp) % B;
            op.n += __BASE_CHAR[tp];
            i--;
            j--;
        }
        if (i >= 0)
        {
            while (i >= 0)
            {
                tp = (this->n[i] - '0') + c;
                c = tp / B;
                tp = (B + tp) % B;
                op.n += __BASE_CHAR[tp];
                i--;
            }
        }
        if (j >= 0)
        {
            while (j >= 0)
            {
                tp = (o.n[j] - '0') + c;
                c = tp / B;
                tp = (B + tp) % B;
                op.n += __BASE_CHAR[tp];
                j--;
            }
        }
        if (c > 0)
        {
            op.n += '0' + c;
        }
        reverse(op.n.begin(), op.n.end());
        return op;
    }

    void operator-=(const int_base<I, B> &o)
    {
        string _n;
        I i = this->n.size() - 1, j = o.n.size() - 1;
        I tp, c = 0;
        while (i >= 0 && j >= 0)
        {
            tp = (this->n[i] - '0') - (o.n[j] - '0') + c;
            c = tp / B;
            tp = (B + tp) % B;
            _n += __BASE_CHAR[tp];
            i--;
            j--;
        }
        if (i >= 0)
        {
            while (i >= 0)
            {
                tp = (this->n[i] - '0') + c;
                c = tp / B;
                tp = (B + tp) % B;
                _n += __BASE_CHAR[tp];
                i--;
            }
        }
        if (j >= 0)
        {
            while (j >= 0)
            {
                tp = (o.n[j] - '0') + c;
                c = tp / B;
                tp = (B + tp) % B;
                _n += __BASE_CHAR[tp];
                j--;
            }
        }
        if (c > 0)
        {
            _n += '0' + c;
        }
        reverse(_n.begin(), _n.end());
        this->n = _n;
    }

    void operator--()
    {
        string _n;
        c = -1;
        while (i >= 0)
        {
            tp = (this->n[i] - '0') + c;
            c = tp / B;
            tp = (B + tp) % B;
            _n += __BASE_CHAR[tp];
            i--;
        }
        if (c > 0)
        {
            _n += '0' + c;
        }
        reverse(_n.begin(), _n.end());
        this->n = _n;
    }

    void operator++()
    {
        string _n;
        c = 1;
        while (i >= 0)
        {
            tp = (this->n[i] - '0') + c;
            c = tp / B;
            tp = (tp) % B;
            _n += __BASE_CHAR[tp];
            i--;
        }

        if (c > 0)
        {
            _n += '0' + c;
        }
        reverse(_n.begin(), _n.end());
        this->n = _n;
    }

    int_base<I, B> operator<<(I h)
    {
        int_base<I, B> op = (*this);
        while ((h--) > 0)
        {
            op.n.push_back('0');
        }
        return op;
    }

    int_base<I, B> operator>>(I h)
    {
        int_base<I, B> op = (*this);
        if (h > this->n.size())
            h = this->n.size();
        while ((h--) > 0)
        {
            op.n.pop_back();
        }
        if (op.n.size() == 0)
        {
            op.n += '0';
        }
        return op;
    }

    void operator<<=(I h)
    {
        while ((h--) > 0)
        {
            this->n.push_back('0');
        }
    }

    void operator>>=(I h)
    {
        if (h > this->n.size())
            h = this->n.size();

        while ((h--) > 0)
        {
            this->n.pop_back();
        }
        if (this->n.size() == 0)
        {
            this->n += '0';
        }
    }

    pair<int_base<I, B>, int_base<I, B>> split(I i)
    {
        pair<int_base<I, B>, int_base<I, B>> op;
        int_base<I, B> tp = (*this);
        op.first = tp >> i;
        op.second = (tp - (op.first << i)) >> i;

        return op;
    }

    int_base<I, B> operator*(int_base<I, B> &o)
    {
        int_base<I, B> op;
        if (o.n.size() == 0 || this->n.size() == 0)
        {
            op.n = "0";
            return op;
        }
        if (o.n.size() == 1)
        {
            I i = this->n.size() - 1;
            I tp, c = 0;
            while (i >= 0)
            {
                tp = (this->n[i] - '0') * (o.n[0] - '0') + c;
                c = tp / B;
                tp %= B;
                op.n += __BASE_CHAR[tp];
            }
            if (c > 0)
            {
                op.n += '0' + c;
            }
            reverse(op.n.begin(), op.n.end());
            return op;
        }
        if (this->n.size() == 1)
        {
            I i = o.n.size() - 1;
            I tp, c = 0;
            while (i >= 0)
            {
                tp = (o.n[i] - '0') * (this->n[0] - '0') + c;
                c = tp / B;
                tp %= B;
                op.n += __BASE_CHAR[tp];
            }
            if (c > 0)
            {
                op.n += '0' + c;
            }
            reverse(op.n.begin(), op.n.end());
            return op;
        }
        I ns = max(this->n.size(), o.n.size());

        pair<int_base<I, B>, int_base<I, B>> xp;
        xp.first = (*this) >> (ns / 2);
        xp.second = ((*this) - (xp.first << (ns / 2))) >> (ns / 2);
        debug(xp);
        pair<int_base<I, B>, int_base<I, B>> yp;
        yp.first = (o >> (ns / 2));
        yp.second = ((o) - (yp.first << (ns / 2))) >> (ns / 2);
        debug(yp);
        int_base<I,B> xp12 = (xp.first + xp.second);
        int_base<I,B> yp12 = (yp.first + yp.second);
        debug("ok");
        debug(xp12);
        debug(yp12);
        int_base<I, B> z0 = xp.first * yp.first;
        int_base<I, B> z2 = xp.second * yp.second;
        int_base<I, B> z1 = xp12 * yp12 - z0 - z2;
        debug(z0);
        debug(z1);
        debug(z2);
        op = (z2 << (2 * (ns / 2))) + (z1 << (ns / 2)) + z0;

        return op;
    }

    friend ostream &operator<<(ostream &os, const int_base<I, B> &x)
    {
        os << x.n;
        return os;
    }
};
