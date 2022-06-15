// FIXME add poly triangulations
// FIXME other simple algorithms
// FIXME convex hull

#pragma once
#include <vector>
#include "point.hpp"
#include "../utils/debug_out.hpp"

using namespace std;

template <typename R, int N>
void convex_hull_nd(const vector<general_point<R>> &p, vector<int> &chp)
{
}

template <typename R>
void convex_hull_1d(const vector<point<R, 1>> &p, vector<int> &chp)
{
    chp.clear();
    int mid = 0;
    int mxid = 0;
    for (int i = 1; i < p.size(); i++)
    {
        if (p[mid].x[0] > p[i].x[0])
        {
            mid = i;
        }
        else if (p[mxid].x[0] < p[i].x[0])
        {
            mxid = i;
        }
    }
    chp.push_back(mid);
    chp.push_back(mxid);
}

template <typename R>
void convex_hull_2d(const vector<point<R, 2>> &p, vector<int> &chp)
{
    int org = 0;
    R orgx = p[0].x[0];
    for (int i = 1; i < p.size(); i++)
    {
        if (p[i].x[0] < orgx)
        {
            org = i;
            orgx = p[i].x[0];
        }
    }
    vector<int> order(p.size(), 0);
    vector<R> angle(p.size());
    for (int i = 0; i < order.size(); i++)
    {
        order[i] = i;
        if (i == org)
        {
            angle[i] = (R)-5.0;
            continue;
        }
        int sg = sign_of(p[i].x[0] - p[org].x[0]);
        if (sg != 0)
            angle[i] = std::atan((p[i].x[1] - p[org].x[1]) / (p[i].x[0] - p[org].x[0]));
        else
            angle[i] = (sg == 1 ? (R)2.0 * std::atan(1) : (R)2.0 * std::atan(-1));
    }

    //true if p1 < p2 i.e. sg1 = (y2*x1-y1*x2), sg2 = (x1*x2+y1*y2), if (sg1*sg2>0)
    auto angle_comperator = [&](const int &p1, const int &p2)
    {
        if (p1 == org)
            return true;
        if (p2 == org)
            return false;
        return angle[p1] < angle[p2];
    };

    auto right_turn = [&](const int &p1, const int &p2, const int &p3)
    {
        return sign_of((p[p2].x[0] - p[p1].x[0]) * (p[p3].x[1] - p[p2].x[1]) - (p[p2].x[1] - p[p1].x[1]) * (p[p3].x[0] - p[p2].x[0])) >= 0;
    };

    sort(order.begin(), order.end(), angle_comperator);
    // remove prll vectors-org
    int j = 0;
    for (int i = 1; i < order.size(); i++)
    {
        if (!is_equal(angle[order[i]], angle[order[j]]))
        {
            j++;
            order[j] = order[i];
        }
        else
        {
            if (p[order[i]].dist_square(p[org]) > p[order[j]].dist_square(p[org]))
            {
                order[j] = order[i];
            }
        }
    }
    j++;
    order.resize(j);
    order.push_back(order[0]);

    std::stack<std::pair<int, int>> hull;
    hull.push({order[1], order[0]});
    for (int i = 2; i < order.size(); i++)
    {
        int cp1 = hull.top().second;
        int cp2 = hull.top().first;
        int cp3 = order[i];
        while (!right_turn(cp1, cp2, cp3))
        {
            if (hull.empty())
            {
                cp2 = cp1;
                break;
            }
            hull.pop();
            cp2 = cp1;
            cp1 = hull.top().second;
        }
        hull.push({cp3, cp2});
    }
    while (!hull.empty())
    {
        chp.push_back(hull.top().first);
        hull.pop();
    }
}
