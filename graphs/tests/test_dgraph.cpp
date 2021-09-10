#include <bits/stdc++.h>
#include "../../utils/new_debug_out.hpp"
#include "../dgraph.hpp"

using namespace std;

typedef long long ll;
typedef double R;

void flow_input(dgraph<ll> &g,vector<unordered_map<ll,ll>> &rescap,vector<bool> &cut)
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

void test_edmonds_karp_max_flow()
{
    dgraph<ll> g;
    vector<unordered_map<ll,ll>> rescap;
    vector<bool> cut;
    flow_input(g,rescap,cut);
    ll s,t;
    cin>>s>>t;
    debug(rescap);
    
    ll flow_val = edmonds_karp_max_flow(s,t,g,rescap,cut);
    debug(flow_val);
    debug(rescap);
}

int main()
{
    freopen("input.txt","r",stdin);
    test_edmonds_karp_max_flow();
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