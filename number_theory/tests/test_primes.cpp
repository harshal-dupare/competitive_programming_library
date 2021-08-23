#include <bits/stdc++.h>
#include "../../utils/timer.h"

using namespace std;


#define ll long long

int main()
{
    primes<ll> ps(100005);
    ps.sieve();
    int t;
    cin >> t;
    while (t-- > 0)
    {
        // prime testing tests
        // float t1 = 0, t2 = 0, t3 = 0, t4 = 0;
        // timer tm;
        // prime_tests<long long> pt;
        // int tt = t;
        // while (tt--)
        // {
        //     int n;
        //     // cin>>n;
        //     n = tt;
        //     // cout << n << ": ";
        //     tm.set();
        //     int a = pt.check_till_root(n);
        //     t1 += tm.get();
        //     // cout << a;

        //     tm.set();
        //     int b = (pt.fermat_check(n));
        //     t2 += tm.get();
        //     // cout << b;

        //     tm.set();
        //     int c = (pt.prob_miller_check(n));
        //     t3 += tm.get();
        //     // cout << c;

        //     tm.set();
        //     int d = (pt.deter_miller_check(n));
        //     t4 += tm.get();
        //     // cout << d << endl;
        // }

        // cout << t1 << ", " << t2 << ", " << t3 << ", " << t4 << endl;
        // t /= 10;

        // primes factor test
        ll n;
        cin >> n;
        for (auto x : ps.factorize_id(n))
        {
            cout << x.first << ":" << x.second << endl;
        }
        cout << endl;
    }
    return 0;
}

/*

10000000
14.3397, 64.8257, 94.5135, 39.9679
1.04883, 6.87673, 9.54103, 3.86097
0.0948232, 0.682812, 0.934151, 0.369178
0.00895428, 0.0667426, 0.0904803, 0.0345295
0.000891205, 0.00625259, 0.00827469, 0.00313209
8.65999e-05, 0.0003559, 0.000421, 0.0002045
9.4e-06, 9.5e-06, 3.83e-05, 9.9e-06
1.1e-06, 9e-07, 9e-07, 9e-07

100000
0.0952627, 0.587831, 0.79096, 0.320024
0.00903027, 0.0573916, 0.0765467, 0.0301386
0.000877906, 0.00542827, 0.0070421, 0.00274819
8.78e-05, 0.0003005, 0.0003645, 0.0002365
8.7e-06, 8.6e-06, 8.8e-06, 8.6e-06
1e-06, 9e-07, 8e-07, 9e-07

*/