#include <bits/stdc++.h>
#include "../../lib/utils/timer.hpp"
#include "../../lib/pnc/combinations.hpp"

using namespace std;

#define ll long long
int main()
{

    ll n;
    cin >> n;
    timer tm;
    double tf = 0, tsf = 0, tct = 0, tcd = 0, tif = 0;
    double tf2 = 0, tsf2 = 0, tct2 = 0, tcd2 = 0, tif2 = 0;

    combinations_mod<ll> cb(100005, (1e9 + 7));
    tm.set();
    cb.computeFact();
    tf = tm.get();

    tm.set();
    cb.compute_subfact();
    tsf = tm.get();

    combinations_mod<ll> cb2(100005, (1e9 + 7));
    tm.set();
    cb2.computeFact();
    tf2 = tm.get();

    tm.set();
    cb2.compute_subfact();
    tsf2 = tm.get();

    ll ct = 0;
    for (ll i = 0; i < n; i++)
    {
        ll ans = cb.fact[i];
        ll ans2 = cb2.fact[i];
        if (ans == ans2)
        {
            ct++;
        }
        // cout << i << ":" << ans << endl;
    }
    cout << endl;
    cout << ct << "/ " << n << endl;

    ct = 0;
    for (ll i = 0; i < n; i++)
    {
        ll ans = cb.ifact[i];
        ll ans2 = cb2.ifact[i];
        if (ans == ans2)
        {
            ct++;
        }
        // cout << i << ":" << ans << endl;
    }
    cout << endl;
    cout << ct << "/ " << n << endl;

    ct = 0;
    ct = 0;
    for (ll i = 0; i < n; i++)
    {
        ll ans = cb.subfact[i];
        ll ans2 = cb2.subfact[i];
        if (ans == ans2)
        {
            ct++;
        }
        // cout << i << ":" << ans << endl;
    }
    cout << endl;
    cout << ct << "/ " << n << endl;

    ct = 0;
    for (ll i = 0; i < n; i++)
    {
        tm.set();
        ll ans = cb.catalan(i);
        tct += tm.get();
        // cout << i << ":" << ans << endl;

        tm.set();
        ll ans2 = cb2.catalan(i);
        tct2 += tm.get();

        if (ans == ans2)
        {
            ct++;
        }
    }
    cout << endl;
    cout << ct << "/ " << n << endl;

    ct = 0;

    tm.set();
    cb.delannoy_number(100);
    tcd = tm.get();

    tm.set();
    cb2.delannoy_number(100);
    tcd2 = tm.get();

    ct = 0;
    for (ll i = 0; i < 100; i++)
    {
        ll ans = cb.central_delannoy[i];
        ll ans2 = cb2.central_delannoy[i];

        if (ans == ans2)
        {
            ct++;
        }
        // cout << i << ":" << ans << endl;
    }
    cout << endl;
    cout << ct << "/ " << 100 << endl;

    cout << fixed << setprecision(6) << "fact: " << tf2 / tf << endl;
    // cout << fixed << setprecision(6) << "ifact: " << tif2 / tif << endl;
    cout << fixed << setprecision(6) << "subfact: " << tsf2 / tsf << endl;
    cout << fixed << setprecision(6) << "cat: " << tct2 / tct << endl;
    cout << fixed << setprecision(6) << "cd: " << tcd2 / tcd << endl;

    return 0;
}


/*

1000

1000/ 1000

1000/ 1000

1000/ 1000

1000/ 1000

100/ 100
fact: 1.899322
subfact: 1.484769
cat: 1.352475
cd: 1.708066


*/