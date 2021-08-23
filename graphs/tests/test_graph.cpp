#include <bits/stdc++.h>
#include <fstream>
#include "../../utils/timer.hpp"
#include "../../utils/debug_out.hpp"
#include "../graph.hpp"
#include "../dgraph.hpp"
#include "../wgraph.hpp"
// #include "../wdgraph.hpp"
// #include "../generator.hpp"

using namespace std;

typedef long long ll;
typedef double R;

void weighted_graph()
{
    wgraph<ll,R> wg;

    wg.input();
    vector<ll> parent;
    R tw = krushal(wg,parent);
}

void normal_graph()
{
    // generator<ll> GR;
    // ll n, m;
    // cin >> n >> m;
    // graph<ll> g(n);
    // while (m--)
    // {
    //     ll u, v;
    //     cin >> v >> u;
    //     g.add_edge(u, v);
    // }

    // graph<ll> g, cyc, pet;
    // ll k;
    // cin >> k;
    // // GR.octahedral(k, g);
    // GR.cycle(k, cyc);
    // GR.perterson(pet);
    // g = cyc + pet;
    // n = g.n;

    // vector<ll> ord(n, 0), lev(n, 0), par(n, 0);
    // vector<bool> vis(n, false);

    // g.print_deg();
    // g.print_adjl();

    // g.bfs(2, lev, vis);
    // oks(lev);
    // oks(vis);
    // vis.assign(n, false);
    // g.dfs(2, ord, par, vis);
    // oks(ord);
    // oks(par);
    // oks(vis);

    // g.dijkstra(3, ord, par);
    // for (ll i = 0; i < g.n; i++)
    // {
    //     cout << i << ":" << ord[i] << ", " << par[i] << "| ";
    // }
    // cout << endl;

    // vector<ll> order(n), coloring(n), coloring2(n), partision(n);

    // cout << "Is biparted : " << g.is_biparted(partision) << endl;

    // pair<ll, ll> pairvs;
    // cout << "Is eulerian : " << g.is_eulerian(pairvs) << endl;

    // for (ll i = 0; i < n; i++)
    // {
    //     order[i] = i;
    // }

    // g.ordering_to_coloring(order, coloring);
    // for (ll i = 0; i < g.n; i++)
    // {
    //     cout << i << ":" << coloring[i] << endl;
    // }

    // g.degree_order_coloring(coloring2);
    // for (ll i = 0; i < g.n; i++)
    // {
    //     cout << i << ":" << coloring2[i] << endl;
    // }

    // graph<ll> gc(n);

    // g.compliment_graph(gc);

    // gc.print_deg();
    // gc.print_adjl();
}

void test_dist()
{
    // generator<ll> GR;
    // ll n;
    // cin>>n;
    // graph<ll> g;
    // GR.perterson(g);
    // g.set_adjM();
    // g.floyd_warshall();
    // okvv(g.min_distance);

    // GR.hypercube(3,g);
    // g.set_adjM();
    // g.floyd_warshall();
    // okvv(g.min_distance);

    // GR.cycle(9,g);
    // g.set_adjM();
    // g.floyd_warshall();
}

int main()
{
    freopen("../../input.txt","r",stdin);
    weighted_graph();
    return 0;
}
/*

3
3 2
1 2 5
2 3 7
1 3
3 3
1 2 4
1 3 7
2 3 1
1 3
3 1
1 2 4
1 3

8 7
1 2
0 1
1 3
3 0
2 0
7 6
5 4

5 5
1 2
0 1
1 3
3 0
2 0

4 5
1 2
0 1
1 3
3 0
2 0


4 5
0 1 7
1 3 6
0 3 5
2 1 9
3 2 2


*/