#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/graphs/generator.hpp"
// #define DEACTIVATE_DEBUG

using namespace std;

typedef long long ll;
typedef double R;

void test_petersion()
{
    special_graph::perterson<ll> pg;

    debug(pg.adjl);
    debug(pg.deg);
}
int main()
{
    freopen("input.txt","r",stdin);
    test_petersion();
    return 0;
}