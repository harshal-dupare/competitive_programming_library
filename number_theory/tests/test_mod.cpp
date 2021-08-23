#include <bits/stdc++.h>
#include "../../utils/timer.hpp"
#include "../modular_int.hpp"

using namespace std;

const long long MOD = 1000007ll;
typedef long long ll;
typedef unsigned long long ull;
typedef Zmod::modular<ll, (MOD)> mint;

void test2()
{
    ull delta = 10;
    ull start = 1000000000;
    ull ct = 0, ct1 = 0, ct2 = 0;
    for (ull i = start; i < start + delta; ++i)
    {
        // ok(mint(i));
        for (ull j = 0; j < MOD; ++j)
        {
            ct1++;
            if (mint(i * j) == mint(i) * mint(j))
            {
                ct2++;
                if ((((i * j) % MOD) + MOD) % MOD == mint(i * j).n)
                    ct++;
            }
        }
    }
    cout<<ct1<<","<<ct2<<","<<ct<<endl;

    return;
}

void test3()
{
    mint x(5), y(6);
    mint z = x - y;
    mint w = x + y;
    mint p = x * y;
    mint q = w * mint(Zmod::inverse<ll,MOD>(w.n));
    auto j = mint(Zmod::inverse<ll,MOD>(w.n));
}

int main()
{
    test2();
    return 0;
}