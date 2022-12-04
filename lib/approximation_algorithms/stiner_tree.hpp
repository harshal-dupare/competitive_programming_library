#pragma once
// FIXME tests
#include <vector>
#include <numeric>
#include <set>
#include "../graphs/graph.hpp"
using namespace std;

// opt <= output <= 2*opt
template <typename I, typename R>
R metric_reduction_2_approximate_stiner_tree(const wgraph<I, R> &g, vector<I> &stiner_vertices, vector<pair<I, I>> &stiner_edges)
{
    I sn = stiner_vertices.size();
    wgraph<I, R> Hs(sn), G(g.n);

    vector<vector<R>> wg(sn);
    vector<vector<I>> prev(sn);
    for (I i = 0; i < sn; i++)
    {
        dijkstra(g, stiner_vertices[i], wg[i], prev[i]);
    }

    for (I i = 0; i < sn; i++)
    {
        for (I j = i + 1; j < sn; j++)
        {
            Hs.add_edge(i, j, wg[i][j]);
        }
    }

    vector<pair<I, I>> MSTh, MSTg;

    R tw = krushal(Hs, MSTh);
    unordered_map<I, bool> added;
    for (auto ep : MSTh)
    {
        I i = stiner_vertices[ep.first];
        I j = stiner_vertices[ep.second];

        while (j != i)
        {
            if (i < j)
            {
                if (!added[i * g.N + j])
                {
                    G.add_edge(i, j, g.edge_weight[i * g.N + j]);
                    added[i * g.N + j] = true;
                }
            }
            else
            {
                if (!added[j * g.N + i])
                {
                    G.add_edge(i, j, g.edge_weight[j * g.N + i]);
                    added[j * G.N + i] = true;
                }
            }

            j = prev[ep.first][j];
        }
    }

    R temp = krushal(G, MSTg);

    stiner_edges = MSTg;

    return temp;
}
