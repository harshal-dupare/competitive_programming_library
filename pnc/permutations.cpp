#include <bits/stdc++.h>
#include "../utils/timer.h"
#include "../utils/debugger.h"

using namespace std;

typedef long long ll;

int main()
{
    ll n;
    cin >> n;
    permutation<ll> a(n), b, c(n), d, e;
    a.print();
    a <<= 1;
    a.print();
    a >>= 100;
    a.print();
    b = a ^ 10;
    b.print();
    b.swap(0, n - 1);
    b.print();
    c = ~b;
    c.print();
    b.randomize();
    b.print();

    vector<vector<ll>> cycle_dec;
    ll transposition_count = b.cyclic_decompose(cycle_dec);
    ok(transposition_count);
    okvv(cycle_dec);

    return 0;
}
