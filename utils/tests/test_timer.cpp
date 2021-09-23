#include <bits/stdc++.h>
#include "../timer.hpp"
#include "../debug_out.hpp"

using namespace std;

typedef long long ll;

int main()
{
    timer tm(100);
    ll n;
    cin >> n;
    ll t = 100;

    // testing map and unorderd map
    // prefer unorderd map whenever possible
    // map<ll, ll> om;
    // unordered_map<ll, ll> uom;
    // double otm = 0, uotm = 0;
    // while (t--)
    // {
    //     tm.set();
    //     for (ll i = 0; i < n; i++)
    //     {
    //         om[i] = i;
    //     }
    //     otm += tm.get();

    //     tm.set();
    //     for (ll i = 0; i < n; i++)
    //     {
    //         uom[i] = i;
    //     }
    //     uotm += tm.get();

    //     uom.clear();
    //     om.clear();
    // }

    // cout << uotm / otm << endl;
    // /*
    // result
    // 200000
    // 0.290576

    // 1000000
    // 0.260175
    // */

    // vectors vs array
    // prefer array whenever possible
    // double vtm = 0, atm = 0, vsz = 0, asz = 0;
    // vector<ll> v;
    // ll a[n];
    // while (t--)
    // {
    //     tm.set();
    //     for (ll i = 0; i < n; i++)
    //     {
    //         a[i] = i;
    //     }
    //     atm += tm.get();

    //     tm.set();
    //     for (ll i = 0; i < n; i++)
    //     {
    //         v.push_back(i);
    //     }
    //     vtm += tm.get();

    //     asz += sizeof(a);
    //     vsz += sizeof(v);

    //     v.clear();
    // }

    // cout << vtm / atm << endl;

    /*
    results
    200000
    5.05552

    1000000
    4.70435
    */

    // sets vs priority queue

    set<ll> s;
    double stm = 0, pqtm = 0;

    while (t--)
    {
        priority_queue<ll> pq;
        tm.set();
        for (ll i = 0; i < n; i++)
        {
            s.insert(i);
        }
        stm += tm.get();

        tm.set();
        for (ll i = 0; i < n; i++)
        {
            pq.push(i);
        }
        pqtm += tm.get();

        s.clear();
    }

    cout << stm / pqtm << endl;

    /*
    results
    200000
    1.22524
    */

    return 0;
}