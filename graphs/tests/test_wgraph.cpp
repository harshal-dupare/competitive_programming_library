#include <bits/stdc++.h>

using namespace std;

#include "../wgraph.h"
#include "../../utils/debug_out.h"

typedef double R;

template <typename I>
wgraph<I, R> rand_graph(I n, double p)
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    bernoulli_distribution ber(p);
    uniform_real_distribution<R> unf(1,10.0);
    wgraph<I, R> G(n);
    for (I i = 0; i < n; i++)
    {
        for (I j = i + 1; j < n; j++)
        {
            if (ber(rng))
            {
                G.add_edge(i, j, unf(rng));
            }
        }
    }
    return G;
}

void test_mst()
{
    int n = 10;
    double p=0.5;
    wgraph<int,R> G = rand_graph(n,p);
    vector<int> comps;
    while(G.connected_components(comps)!=1)
    {
        G = rand_graph(n,p);
    }
    vector<pair<int,int>> elist;
    R tw = G.krushal(elist);
    debug(G.deg);
    debug(tw);
}

void test_stiner()
{
    int n = 10;
    double p=0.5;
    wgraph<int,R> G = rand_graph(n,p);
    vector<int> comps;
    while(G.connected_components(comps)!=1)
    {
        G = rand_graph(n,p);
    }
    int sn;
    cin >> sn;
    vector<int> sv(sn);
    while (sn--)
    {
        cin >> sv[sn];
    }
    vector<pair<int, int>> se;

    G.approximate_stiner_tree(sv, se);

    debug(G.deg);
    debug(G.adjl);
    /*
8
13
0 1 1
0 2 1
0 3 1
0 4 1
0 5 1
0 6 1
0 7 1
1 2 2
2 3 2
3 4 2
4 5 2
5 6 2
6 7 2
7
1 2 3 4 5 6 7
*/
}

int main()
{
    test_stiner();
}