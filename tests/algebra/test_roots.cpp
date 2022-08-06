#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/algebra/roots.hpp"

using namespace std;

typedef long long int ll;
typedef double R;
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

void test_polynomial_roots_companion_matrix()
{
    vector<R> p = {6,-5,-2,1,5,7};
    auto proots = roots::polynomial_roots_companion_matrix<R,int>(p);
    debug(proots);
}

int main()
{
    test_polynomial_roots_companion_matrix();
    return 0;
}