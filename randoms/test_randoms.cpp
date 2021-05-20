#include <bits/stdc++.h>
#include "../utils/debug_out.h"
#include "../utils/timer.h"
#include "random_gen.hpp"

using namespace std;

typedef long long ll;

void test()
{
    random_gens<ll, double, std::mt19937> rd;
    ll n = 10, mxitr = 10;
    vector<ll> a(n);
    auto gen = rd.uniform_int(0,10);
    while (mxitr--)
    {
        rand_fill(a,gen);
        debug(a);
    }
}

int main()
{
    test();
    return 0;
}