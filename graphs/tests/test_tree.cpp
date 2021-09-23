#include <bits/stdc++.h>
#include "../tree.hpp"
#include "../../utils/debug_out.hpp"
using namespace std;

typedef long long ll;

void test()
{
    ll n, m;
    cin >> n >> m;
    tree<ll, ll> tr(n);

    for (ll i = 0; i < m; i++)
    {
        ll x, y, w;
        cin >> x >> y >> w;
        tr.add_edge(x, y, w);
    }

    // tr.print();
    tr.root_at(1);
    tr.print();

    vector<ll> ct(n, 0);

    for (ll i = 0; i < n; i++)
    {
        if (tr.nodes[i].deg == 1)
        {
            tr.climb_search(i, ct);
        }
    }
    vector<ll> level(n), intime(n), outtime(n), pruf(n - 2);

    tr.bfs(1, level);
    tr.dfs(1, intime, outtime);
    tr.prufer_seq(pruf);

    debug(level);
    debug(intime);
    debug(outtime);
    debug(pruf);
}

void testes()
{
    ll n, m;
    cin >> n >> m;
    tree<ll, ll> tr(n);

    for (ll i = 0; i < m; i++)
    {
        ll x, y;
        cin >> x >> y;
        tr.add_edge(x, y);
    }
    vector<ll> es, esr;
    vector<bool> vis(n, false);
    tr.euler_seq(0, es);
    debug(es);
    tr.rec_euler_seq(0, vis, esr);
    debug(esr);
}

int main()
{
    testes();
    return 0;
}

/*

6 5
0 1 1
0 2 2
1 3 5
2 4 -1
2 5 8
adj list:
[0, 2] : 1, 2,
[1, 2] : 0, 3,
[2, 3] : 0, 4, 5,
[3, 1] : 1,
[4, 1] : 2,
[5, 1] : 2,
parent:
[0 : 1], [1 : 1], [2 : 0], [3 : 1], [4 : 2], [5 : 2],
edge weight:
[5, 2: 8], [2, 5: 8], [4, 2: -1], [2, 4: -1], [3, 1: 5], [1, 3: 5], [2, 0: 2], [0, 2: 2], [1, 0: 1], [0, 1: 1],
3
4
5
2
0
S :
3:1, 4:2, 5:2,
S :
1:0, 4:2, 5:2,
S :
0:2, 4:2, 5:2,
S :
4:2, 5:2,
level :
{ 1 0 2 1 3 3 }
intime :
{ 2 0 6 3 8 9 }
outtime :
{ 5 1 7 4 11 10 }
pruf :
{ 1 0 2 2 }

*/