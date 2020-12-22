#include <bits/stdc++.h>
#include "../utils/timer.h"

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

#define ll long long

int main()
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

    return 0;
}