#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../roots.hpp"

using namespace std;
typedef long long int ll;

void test_inroot()
{
    
    ll lim = 10000;
    for (ll i = -lim; i < lim + 1; i++)
    {
        ll r=4;
        if (roots::inroot<ll>(i, r) != 0)
            cout << i <<"^(1/"<<r<< "): " << roots::inroot<ll>(i, r) << endl;
    }
}

int main()
{
    test_inroot();
    return 0;
}