#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../generator.hpp"
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