#include <bits/stdc++.h>
#include "../../utils/timer.hpp"
#include "../../utils/debug_out.hpp"
#include "../number_properties.hpp"

using namespace std;

typedef long long ll;

void test_cyc()
{
    number_properties<int> np;
    int n;
    cin >> n;
    // int mxv=-1,mxi;
    for (int i = 1; i <= n; i++)
    {
        // cout << i << ":" << np.reciprocal_period(i) << endl;
        // if(np.fract_period(1,i) >= mxv)
        // {
        //     mxv = np.fract_period(1,i);
        //     mxi=i;
        // }
        // cout << np.fract_period(1,i) << ", ";
        // cout << np.fract_period(1,i) << ", ";
        cout << np.reciprocal_period(i) << ", ";
    }
    // ok(mxi);
}

void test_forb()
{
    number_properties<ll> np;
    ll n;
    cin >> n;
    while(n--)
    {
        ll k;
        cin>>k;
        vector<ll> nl(k);
        while(k>0)
        {
            cin>>nl[k-1];
            k--;
        }

        ll ans = np.forbenius(nl);
        cout<<ans<<endl;
    }
}

void test_gcd()
{
    number_properties<int> np;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        int x, y;
        int g = np.extended_gcd(a, b, x, y);
        cout << a << "*(" << x << ") + (" << y << ")*" << b << " = " << g << endl;
    }
}

int main()
{
    // test_cyc();
    test_forb();
    return 0;
}
