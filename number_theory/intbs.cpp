#include <bits/stdc++.h>
#include "../utils/debug_out.h"
#include "int_base.h"

mt19937 rng(198);

using namespace std;

typedef int_base<int, 13> intb;

int main()
{
    intb x(120), y(13);
    debug(x);
    debug(y);
    debug(x + y);
    debug(x >> 1);
    debug(y >> 1);
    debug(x << 1);
    debug(y << 1);
    debug(y - x);
    debug(y * x);

    return 0;
}