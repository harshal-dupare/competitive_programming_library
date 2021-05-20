#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename I, typename V>
class wgraph
{
public:
    I N = 1000007;
    V inf = 1e16;

    I n;
    vector<vector<I>> adjl;
    vector<I> deg;
    unordered_map<I, V> edge_weight;

    wgraph()
    {
        this->n = 0;
    }

    wgraph(I _n)
    {
        this->n = _n;
        this->adjl = vector<vector<I>>(_n, vector<I>(0));
        this->deg = vector<I>(_n, 0);
    }

    void add_edge(I x, I y, V w)
    {
        this->adjl[x].push_back(y);
        this->adjl[y].push_back(x);
        this->deg[x]++;
        this->deg[y]++;
        this->edge_weight[x * N + y] = w;
        this->edge_weight[y * N + x] = w;
    }

    void add_vertex(vector<I> &adj, vector<V> &wg)
    {
        this->adjl.push_back(vector<I>(0));
        for (I i = 0; i < this->n; i++)
        {
            this->add_edge(this->n, adj[i], wg[i]);
        }
        this->n++;
    }

    void input()
    {
        I m;
        I v1, v2;
        V w;
        cin >> this->n >> m;
        this->adjl = vector<vector<I>>(this->n, vector<I>(0));
        this->deg = vector<I>(this->n, 0);
        for (I i = 0; i < m; i++)
        {
            cin >> v1 >> v2 >> w;
            this->add_edge(v1, v2, w);
        }
    }
};

template <typename I, typename V>
void bfs(I x, wgraph<I, V> &G, vector<I> &level, vector<bool> &visted)
{
    queue<I> snow;
    level.resize(G.n, -1);
    visted.resize(G.n, false);

    snow.push(x);
    level[x] = 0;

    while (!snow.empty())
    {
        auto t = snow.front();
        visted[t] = true;
        snow.pop();
        for (auto y : G.adjl[t])
        {
            if (!visted[y])
            {
                level[y] = level[t] + 1;
                visted[y] = true;
                snow.push(y);
            }
        }
    }
}

template <typename I, typename V>
void dfs(I x, wgraph<I, V> &G, vector<I> &order, vector<I> &parent, vector<bool> &visited)
{
    stack<I> snow;
    order.resize(G.n, -1);
    parent.resize(G.n, -1);
    visited.resize(G.n, false);

    snow.push(x);
    I ct = 0;
    parent[x] = x;

    while (!snow.empty())
    {
        auto t = snow.top();
        visited[t] = true;
        order[t] = ct;
        ct++;
        snow.pop();
        for (auto y : G.adjl[t])
        {
            if (!visited[y])
            {
                order[y] = ct;
                parent[y] = t;
                ct++;
                visited[y] = true;
                snow.push(y);
            }
        }
    }
}

template <typename I, typename V>
void dfs(I x, wgraph<I, V> &G, vector<I> &tin, vector<I> &tout, vector<I> &parent, vector<bool> &visited)
{

    tin.resize(G.n, -1);
    tout.resize(G.n, -1);
    parent.resize(G.n, -1);
    visited.resize(G.n, false);

    I itimer = 0;
    stack<I> snow;
    snow.push(x);
    tin[x] = itimer;
    itimer++;
    parent[x] = x;

    while (!snow.empty())
    {
        auto t = snow.top();
        snow.pop();

        if (visited[t])
        {
            tout[x] = itimer;
            itimer++;
            continue;
        }

        visited[t] = true;
        tout[x] = itimer;
        itimer++;

        for (auto y : G.adjl[t])
        {
            if (y != parent[t])
            {
                parent[y] = t;
                visited[y] = true;
                tin[y] = itimer;
                itimer++;

                snow.push(t);
                snow.push(y);
            }
        }
    }
}

template <typename I, typename V>
void dfs_rec(I x, wgraph<I, V> &G, vector<I> &intime, vector<I> &otime, vector<I> &parent, vector<bool> &visited, I &mytimer)
{
    intime[x] = mytimer;
    visited[x] = true;
    for (auto y : G.adjl[x])
    {
        if (!visited[y])
        {
            parent[y] = x;
            dfs_rec(y, G, intime, otime, parent, visited, mytimer);
        }
    }
    otime[x] = mytimer++;
}

template <typename I, typename V>
I connected_components(wgraph<I, V> &G, vector<I> &component)
{
    component.assign(G.n, -1);

    I c = 0;
    I at = 0;

    while (at < G.n)
    {
        // do bfs for each vertex and get the component indexed
        queue<I> snow;
        snow.push(at);

        while (!snow.empty())
        {
            auto t = snow.front();
            component[t] = c;
            snow.pop();
            for (auto y : G.adjl[t])
            {
                if (component[y] == -1)
                {
                    component[y] = c;
                    snow.push(y);
                }
            }
        }
        c++;
        while (component[at] != -1 && at < G.n)
            at++;
    }

    return c;
}

template <typename I, typename V>
bool is_biparted(wgraph<I, V> &G, vector<I> &partition)
{
    // Braces and Rigidity inG.n x m grid if the graph with edges as braces at b[r][c] is biparted and connected
    queue<I> q;
    q.push(0);
    partition.assign(G.n, -1);
    partition[0] = 0;
    while (!q.empty())
    {
        I x = q.front();
        q.pop();
        for (auto y : G.adjl[x])
        {
            if (partition[y] == partition[x])
            {
                return false;
            }
            if (partition[y] == -1)
            {
                partition[y] = partition[x] ^ 1;
                q.push(y);
            }
        }
    }

    return true;
}

template <typename I, typename V>
bool is_eulerian(wgraph<I, V> &G, pair<I, I> &p)
{
    p.first = -1;
    p.second = -1;
    I ct = 0;
    for (I i = 0; i < G.n; i++)
    {
        if (G.deg[i] & 1)
        {
            if (ct & 1)
            {
                p.first = i;
            }
            else
            {
                p.second = i;
            }
            ct++;
            if (ct > 3)
            {
                return false;
            }
        }
    }

    if (ct & 1)
    {
        return false;
    }

    return true;
}

// O(Elog(E)+V)
template <typename I, typename V>
void dijkstra(I x, wgraph<I, V> &G, vector<V> &dist, vector<I> &prev)
{
    dist.assign(G.n, G.inf);
    prev.assign(G.n, -1);
    vector<bool> relaxed(G.n, false);
    dist[x] = 0;
    prev[x] = x;
    // value and index
    set<pair<V, I>> q;
    q.insert(make_pair((V)0, x));

    while (!q.empty())
    {
        auto vw = q.begin();
        I v = vw->second;
        V w = vw->first;
        q.erase(vw);
        relaxed[v] = true;

        for (auto nbr : G.adjl[v])
        {
            if (relaxed[nbr])
            {
                continue;
            }

            V egw = G.edge_weight[v * G.N + nbr];
            if (egw + w < dist[nbr])
            {
                auto itr = q.find({dist[nbr], nbr});
                if (itr != q.end())
                {
                    q.erase(itr);
                }
                dist[nbr] = egw + w;
                prev[nbr] = v;
                q.insert({dist[nbr], nbr});
            }
        }
    }
}

// O(E*log(V)+V)
template <typename I, typename V>
V prims(wgraph<I, V> &G, vector<I> &parent)
{
    parent.resize(G.n, -1);
    vector<bool> done(G.n);
    vector<V> lowedge(G.n, G.inf);
    set<pair<V, I>> pq;

    V tweight = 0;
    done[0] = true;
    parent[0] = 0;
    for (auto u : G.adjl[0])
    {
        V w = G.edge_weight[u];
        lowedge[u] = w;
        parent[u] = 0;
        pq.insert(make_pair(w, u));
    }

    while (!pq.empty())
    {
        pair<V, I> tp = *pq.begin();
        tweight += tp.first;
        I u = tp.second;
        done[u] = true;
        pq.erase(tp);

        for (auto v : G.adjl[u])
        {
            if (done[v])
            {
                continue;
            }

            V w = G.edge_weight[u * G.N + v];
            if (lowedge[v] > w)
            {
                auto itr = pq.find(make_pair(lowedge[v], v));
                if (itr != pq.end())
                {
                    pq.erase(itr);
                }
                pq.insert(make_pair(w, v));
                lowedge[v] = w;
                parent[v] = u;
            }
        }
    }

    return tweight;
}

// O(V^3)
template <typename I, typename V>
void floyd_warshall(wgraph<I, V> &G, vector<vector<V>> &min_distance)
{
    assign_adj_matrix(G, min_distance);
    vector<vector<V>> tmin_distance = min_distance;
    for (I k = 0; k < G.n; k++)
    {
        for (I i = 0; i < G.n; i++)
        {
            if (min_distance[i][k] == wgraph<I, V>::inf)
            {
                continue;
            }

            for (I j = 0; j < G.n; j++)
            {
                tmin_distance[i][j] = min(min_distance[i][j], min_distance[i][k] + min_distance[k][j]);
            }
        }
        min_distance = tmin_distance;
    }
}

// O(E*log(E)+V)
template <typename I, typename V>
V krushal(wgraph<I, V> &G, vector<I> &parent)
{
    parent.resize(G.n, -1);
    priority_queue<pair<V, I>> epq;
    vector<I> dsu(G.n), sz(G.n);
    V tweight = 0;

    for (I i = 0; i < G.n; i++)
    {
        dsu[i] = i;
        sz[i] = 1;
        for (auto j : G.adjl[i])
        {
            epq.push({-G.edge_weight[i * G.N + j], i * G.N + j});
        }
    }

    while (!epq.empty())
    {
        pair<V, I> itr = epq.top();
        I a = itr.second / G.N;
        I b = itr.second % G.N;
        I ida = a, idb = b;
        while (ida != dsu[ida])
            ida = dsu[ida];
        while (idb != dsu[idb])
            idb = dsu[idb];

        if (ida != idb)
        {
            if (sz[ida] >= sz[idb])
            {
                sz[ida] += sz[idb];
                dsu[idb] = ida;
            }
            else
            {
                sz[idb] += sz[ida];
                dsu[ida] = idb;
            }

            tweight -= itr.first;
            parent[b] = a;
            if (parent[a] != -1)
            {
                parent[a] = a;
            }
        }
        epq.pop();
    }

    return tweight;
}

// O(E*W+V)
template <typename I, typename V>
V krushal_wrange(wgraph<I, V> &G, vector<I> &parent, V W_max)
{
    vector<vector<pair<I, I>>> weight_buckets(W_max + 1);
    parent.resize(G.n, -1);
    vector<I> dsu(G.n), sz(G.n);
    V tweight = 0;

    for (I i = 0; i < G.n; i++)
    {
        dsu[i] = i;
        sz[i] = 1;
        for (auto j : G.adjl[i])
        {
            if (j > i)
            {
                weight_buckets[G.edge_weight[i * G.N + j]].push_back(make_pair(i, j));
            }
        }
    }
    // weight_buckets.shrink_to_fit();

    I ct = 0;
    I W = 0, id = 0;
    I weight;
    pair<I, I> itr;
    while (ct < G.n - 1)
    {
        while (W <= W_max)
        {
            if (id >= weight_buckets[W].size())
            {
                W++;
                id = 0;
            }
            else
            {
                weight = W;
                itr = weight_buckets[W][id];
                id++;
                break;
            }
        }

        I a = itr.first;
        I b = itr.second;
        I ida = a, idb = b;
        while (ida != dsu[dsu[ida]])
            ida = dsu[dsu[ida]];
        while (idb != dsu[dsu[idb]])
            idb = dsu[dsu[idb]];

        if (ida != idb)
        {
            if (sz[ida] >= sz[idb])
            {
                sz[ida] += sz[idb];
                dsu[idb] = ida;
            }
            else
            {
                sz[idb] += sz[ida];
                dsu[ida] = idb;
            }

            tweight += weight;
            parent[b] = a;
            if (parent[a] != -1)
            {
                parent[a] = a;
            }
            ct++;
        }
    }

    return tweight;
}

// calcultes the coloring which will be given by the greedy method with the given ordering
template <typename I, typename V>
void ordering_to_coloring(wgraph<I, V> &G, vector<I> &ordering, vector<I> &coloring)
{
    vector<bool> cposs(G.n, true);
    stack<I> toremove;
    coloring.assign(G.n, -1);
    coloring[ordering[0]] = 0;

    for (I i = 1; i < G.n; i++)
    {
        for (auto nbr : G.adjl[ordering[i]])
        {
            if (coloring[nbr] != -1 && cposs[coloring[nbr]] == true)
            {
                cposs[coloring[nbr]] = false;
                toremove.push(coloring[nbr]);
            }
        }

        // most inefficient part might take linear time in n
        // find the MinEX
        I j = 0;
        while (!cposs[j])
            j++;

        coloring[i] = j;

        while (!toremove.empty())
        {
            cposs[toremove.top()] = true;
            toremove.pop();
        }
    }
}

template <typename I, typename V>
void degree_order_coloring(wgraph<I, V> &G, vector<I> &ordering)
{
    vector<pair<I, I>> plst;
    for (I i = 0; i < G.n; i++)
    {
        plst.push_back(make_pair(G.deg[i], i));
    }

    sort(plst.begin(), plst.end());
    for (I i = 0; i < G.n; i++)
    {
        ordering[i] = plst[G.n - 1 - i].second;
    }

    return ordering_to_coloring(ordering);
}

// need to complete
template <typename I, typename V>
void bridges(wgraph<I, V> &G, vector<pair<I, I>> &bridges)
{
    stack<I> st;
    stack<I> back_vertex;
    vector<I> processed(G.n, -1);
    st.push(0);

    while (!st.empty())
    {
        I x = st.top();
        st.pop();
        processed[x] = 1;
        for (auto y : G.adj[x])
        {
            if (processed[y] == 1)
            {
            }
            else if (processed[y] == 0)
            {
            }
            else
            {
                st.push(y);
                processed[y] = 0;
            }
        }
    }
}

// opt <= output <= 2*opt
template <typename I, typename V>
void approximate_stiner_tree(wgraph<I, V> &g, vector<I> &stiner_vertices, vector<pair<I, I>> &stiner_edges)
{
    I sn = stiner_vertices.size();
    wgraph<I, V> Hs(sn), G(g.n);

    vector<vector<V>> wg(sn);
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

    V tw = krushal(Hs, MSTh);
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

    V temp = krushal(G, MSTg);

    stiner_edges = MSTg;
}

template <typename I, typename V>
I dinics_algorithm(wgraph<I, V> &G)
{
    I max_flow;

    return max_flow;
}
