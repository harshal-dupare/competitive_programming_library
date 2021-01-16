#include <bits/stdc++.h>
#include "../utils/timer.h"
#include "../utils/debugger.h"

using namespace std;

template <typename I>
class lmodop
{
public:
    I MOD;
    lmodop(I MOD)
    {
        this->MOD = MOD;
    }

    I add(I n, I m)
    {
        return (this->MOD + (n + m) % this->MOD) % this->MOD;
    }

    I sub(I n, I m)
    {
        return (this->MOD + (n - m) % this->MOD) % this->MOD;
    }

    I mult(I n, I m)
    {
        return (this->MOD + (n * m) % this->MOD) % this->MOD;
    }

    I powm(I n, I k)
    {
        I ans = 1;
        I po = n;
        while (k > 0)
        {
            if (k & 1)
            {
                ans = this->mult(ans, n);
            }
            po = this->mult(po, po);
            k >>= 1;
        }

        return ans;
    }

    I div(I n, I m)
    {
        return this->mult(n, this->powm(m, this->MOD - 2));
    }
};

template <typename I>
class modop
{
public:
    I MOD;
    modop(I MOD)
    {
        this->MOD = MOD;
    }

    I add(I n, I m)
    {
        I ans = (n + m) % this->MOD;
        if (ans < 0)
            ans += this->MOD;

        return ans;
    }

    I sub(I n, I m)
    {
        I ans = (n - m) % this->MOD;
        if (ans < 0)
            ans += this->MOD;
        return ans;
    }

    I mult(I n, I m)
    {
        I ans = (n * m) % this->MOD;
        if (ans < 0)
            ans += this->MOD;

        return ans;
    }

    I powm(I n, I k)
    {
        I ans = 1;
        I po = n;
        while (k > 0)
        {
            if (k & 1)
            {
                ans = this->mult(ans, n);
            }
            po = this->mult(po, po);
            k >>= 1;
        }

        return ans;
    }

    I div(I n, I m)
    {
        return this->mult(n, this->powm(m, this->MOD - 2));
    }
};

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

#define MOD 7
typedef long long ll;
typedef unsigned long long ull;
typedef modular<ll, (MOD)> mint;

void test1()
{
    ll prm = 1e9 + 7;
    modop<ll> mo(prm);
    lmodop<ll> lmo(prm);
    int t;
    cin >> t;
    timer tm;
    ll a1, a2;
    double pl = 0, mn = 0, ml = 0, dv = 0;
    double lpl = 0, lmn = 0, lml = 0, ldv = 0;
    while (t--)
    {
        ll n, m;
        n = abs(rand()) % mo.MOD;
        m = abs(rand()) % mo.MOD;

        tm.set();
        a1 = mo.add(n, m);
        pl += tm.get(1);
        a2 = lmo.add(n, m);
        lpl += tm.get(1);
        // cout << n << "+" << m << "=" << a1 << ", " << a2 << endl;

        tm.set();
        a1 = mo.sub(n, m);
        mn += tm.get(1);
        a2 = lmo.sub(n, m);
        lmn += tm.get(1);
        // cout << n << "-" << m << "=" << a1 << ", " << a2 << endl;

        tm.set();
        a1 = mo.mult(n, m);
        ml += tm.get(1);
        a2 = lmo.mult(n, m);
        lml += tm.get(1);
        // cout << n << "*" << m << "=" << a1 << ", " << a2 << endl;

        tm.set();
        a1 = mo.div(n, m);
        dv += tm.get(1);
        a2 = lmo.div(n, m);
        ldv += tm.get(1);
        cout << n << "/" << m << "=" << a1 << ", " << a2 << endl;

        // cout << endl;
    }

    cout << pl << endl;
    cout << mn << endl;
    cout << ml << endl;
    cout << dv << endl;

    cout << pl / lpl << endl;
    cout << mn / lmn << endl;
    cout << ml / lml << endl;
    cout << dv / ldv << endl;
}

void test2()
{
    ull delta = 1000000;
    ull start = 1000000000;
    ull ct = 0, ct1 = 0, ct2 = 0;
    for (ull i = start; i < start + delta; ++i)
    {
        // ok(mint(i));
        for (ull j = 0; j < inMOD; ++j)
        {
            ct1++;
            if (mint(i * j) == mint(i) * mint(j))
            {
                ct2++;
                if ((((i * j) % inMOD) + inMOD) % inMOD == mint(i * j).n)
                    ct++;
            }
        }
    }

    ok(delta * inMOD);
    ok(ct);
    ok(ct1);
    ok(ct2);
}

void test3()
{
    mint x(5), y(6);
    ok(x);
    ok(y);
    mint z = x - y;
    mint w = x + y;
    mint p = x * y;
    mint q = w * w.inverse();
    auto j = w.inverse();

    ok(z);
    ok(w);
    ok(p);
    ok(j);
    ok(q);
}

int main()
{
    test3();
    return 0;
}