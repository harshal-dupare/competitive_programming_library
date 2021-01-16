#include <bits/stdc++.h>
#include "../utils/debug_out.h"
#include "point.h"
#include "line.h"
#include "polygon.h"
#include "algos.h"

mt19937 rng(198);

using namespace std;
typedef point3<double> pt;

int main()
{
    pt a, b, c;
    vector<pt> ps;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ps.push_back(pt(rng() % 100, rng() % 100, rng() % 100));
    }

    debug(ps);

    for (int i = 0; i < n - 2; i++)
    {
        pt opt = ps[i].projection_on_line(ps[i + 1], ps[i + 2]);
        // debug(ps[i]>ps[i+1]);
        debug(ps[i]);
        debug(ps[i + 1]);
        // pt xx = ps[i]*0.02;
        // debug(xx);
        debug((opt - ps[i + 1]).length());
        debug((ps[i + 2] - ps[i + 1]).length());
        debug((ps[i + 2] - opt).length());
        debug(opt);
        debug(opt.on_line(ps[i + 1], ps[i + 2]));
        debug(opt.on_plain(ps[i], ps[i + 1], ps[i + 2]));
        debug(opt.in_segment(ps[i + 1], ps[i + 2]));
        debug(opt.in_triangle(ps[i], ps[i + 1], ps[i + 2]));

        debug_out();
    }

    return 0;
}