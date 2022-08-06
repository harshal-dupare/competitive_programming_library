// FIXME add poly triangulations
// FIXME other simple algorithms
// FIXME convex hull

#pragma once
#include <vector>
#include "point.hpp"
#include "../utils/debug_out.hpp"

using namespace std;

template <typename R, int N>
vector<point<R, N>> get_subset_of_points(const vector<point<R, N>> &p, const vector<int> &subset)
{
    vector<point<R, N>> sp;
    for (auto pi : subset)
    {
        sp.push_back(p[pi]);
    }
    return sp;
}

template <typename R>
void reduce_dim(vector<general_point<R>> &p)
{
    return;
}
