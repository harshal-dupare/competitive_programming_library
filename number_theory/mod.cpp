#include <bits/stdc++.h>
#include "../utils/timer.hpp"
#include "../utils/debugger.hpp"

using namespace std;

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

    return;
}

void test3()
{
    mint x(5), y(6);
    mint z = x - y;
    mint w = x + y;
    mint p = x * y;
    mint q = w * w.inverse();
    auto j = w.inverse();
}

int main()
{
    test3();
    return 0;
}