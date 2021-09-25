#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../graph.hpp"
// #define DEACTIVATE_DEBUG

using namespace std;

typedef long long ll;
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

void flow_input(graph<ll> &g,vector<unordered_map<ll,ll>> &rescap,vector<bool> &cut)
{
    ll n,m;
    cin>>n>>m;
    g.resize(n);
    rescap.assign(n,unordered_map<ll,ll>());
    cut.assign(n,false);
    for(ll i=0;i<m;i++)
    {
        ll u,v,cap;
        cin>>u>>v>>cap;
        g.add_edge(u,v);
        rescap[u][v] = cap;
    }
}

void normal_graph(graph<ll>& g)
{
    ll n,m;
    cin>>n>>m;
    g.resize(n);
    for(ll i=0;i<m;i++)
    {
        ll u,v;
        cin>>u>>v;
        g.add_edge(u,v);
    }
}

void test_edmonds_karp_max_flow()
{
    graph<ll> g;
    vector<unordered_map<ll,ll>> rescap;
    vector<bool> cut;
    flow_input(g,rescap,cut);
    ll s,t;
    cin>>s>>t;
    debug(rescap);

    ll flow_val = edmonds_karp_max_flow(s,t,g,rescap,cut);
    debug("ran");
    debug(flow_val);
    debug(rescap);
}

void test_tuckers_algorithm()
{
    graph<ll> g;
    normal_graph(g);
    debug(g.deg);
    vector<unordered_map<ll,ll>> eorder;
    bool there = tuckers_algorithm(g,eorder);
    debug(there);
    debug(eorder);
}

void test_assign_adj_matrix()
{
    graph<ll> g;
    normal_graph(g);
    vector<vector<ll>> adjm;
    assign_adj_matrix(g,adjm);
    debug(adjm);

    wgraph<ll,R> wg;
    wg.input();
    vector<vector<R>> wadjm;
    assign_adj_matrix(wg,wadjm);
    debug(wadjm);
}

int main()
{
    freopen("input.txt","r",stdin);
    test_assign_adj_matrix();
    return 0;
}