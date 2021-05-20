#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename I, typename V>
class wdgraph
{
public:
    I N = 1000007;
    V inf = 1e16;
    I n;
    vector<vector<I>> iadjl;
    vector<vector<I>> oadjl;
    vector<I> odeg;
    vector<I> ideg;
    unordered_map<I, V> edge_weight;

    wdgraph(I n)
    {
        this->n = n;
        this->oadjl = vector<vector<I>>(n, vector<I>(0));
        this->iadjl = vector<vector<I>>(n, vector<I>(0));
        this->odeg = vector<I>(n, 0);
        this->ideg = vector<I>(n, 0);
    }

    void add_edge(I x, I y, V w)
    {
        this->oadjl[x].push_back(y);
        this->iadjl[y].push_back(x);
        this->odeg[x]++;
        this->ideg[y]++;
        this->edge_weight[x * N + y] = w;
    }

    void add_vertex(vector<I> &id, vector<I> &iw, vector<I> &od, vector<I> &ow)
    {
        this->iadjl.push_back(vector<I>(0));
        this->oadjl.push_back(vector<I>(0));
        this->odeg.push_back(od.size());
        this->ideg.push_back(id.size());

        for (I i = 0; i < id.size(); i++)
        {
            this->iadjl[this->n].push_back(id[i]);
            this->oadjl[id[i]].push_back(this->n);
            this->odeg[id[i]]++;

            this->edge_weight[N * id[i] + this->n] = iw[i];
        }

        for (I i = 0; i < od.size(); i++)
        {
            this->oadjl[this->n].push_back(od[i]);
            this->iadjl[od[i]].push_back(this->n);
            this->ideg[od[i]]++;

            this->edge_weight[N * this->n + od[i]] = ow[i];
        }

        this->n++;
    }

    void invert_edges()
    {
        swap(this->oadjl, this->iadjl);
        swap(this->odeg, this->ideg);
        unordered_map<I, V> tedw;
        for (auto x : this->edge_weight)
        {
            tedw[((x.first) % N) * N + ((x.first) / N)] = x.second;
        }
        this->edge_weight = tedw;
    }

    void input()
    {
        I m;
        I v1, v2;
        V w;
        cin >> n > m;
        for (I i = 0; i < m; i++)
        {
            cin >> v1 >> v2 >> w;
            this->add_edge(v1, v2, w);
        }
    }
};

template <typename I, typename V>
void bfs(I x, wdgraph<I, V> &G, vector<I> &level, vector<bool> &visted)
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
        for (auto y : G.oadjl[t])
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
void dfs(I x, wdgraph<I, V> &G, vector<I> &order, vector<I> &parent, vector<bool> &visited)
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
        for (auto y : G.oadjl[t])
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
void dfs(I x, wdgraph<I, V> &G, vector<I> &tin, vector<I> &tout, vector<I> &parent, vector<bool> &visited)
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

        for (auto y : G.oadjl[t])
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
I underlining_connected_components(wdgraph<I, V> &G, vector<I> &component)
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
            for (auto y : G.oadjl[t])
            {
                if (component[y] == -1)
                {
                    component[y] = c;
                    snow.push(y);
                }
            }

            for (auto y : G.iadjl[t])
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
bool topological_sort(wdgraph<I, V> &G, vector<I> &sorted_vertices)
{
    vector<I> dct = G.ideg;
    sorted_vertices.resize(G.n, -1);

    queue<I> nextv;
    for (I i = 0; i < G.n; i++)
    {
        if (dct[i] == 0)
        {
            nextv.push(i);
        }
    }
    I id = 0;
    while (!nextv.empty())
    {
        I v = *nextv.front();
        nextv.pop();
        sorted_vertices[id] = v;
        id++;
        for (I u : G.oadjl[v])
        {
            dct[u]--;
            if (dct[u] == 0)
            {
                nextv.push(u);
            }
        }
    }
    if (id < G.n)
    {
        return false;
    }
    return true;
}

// O(Elog(E)+V)
template <typename I, typename V>
void dijkstra(I x, wdgraph<I, V> &G, vector<V> &dist, vector<I> &prev)
{
    vector<bool> relaxed(G.n, false);
    dist.resize(G.n, G.inf);
    prev.resize(G.n, -1);
    dist[x] = 0;
    prev[x] = x;

    set<pair<V, I>> q;
    q.insert(make_pair((V)0, x));

    while (!q.empty())
    {
        auto vw = q.begin();
        I v = vw->second;
        V w = vw->first;
        auto titr = q.erase(vw);
        relaxed[v] = true;

        for (auto nbr : G.oadjl[v])
        {
            if (relaxed[nbr])
            {
                continue;
            }

            V egw = G.edge_weight[v * G.N + nbr];
            if (egw + w < dist[nbr])
            {
                auto itr = q.find(make_pair(dist[nbr], nbr));
                if (itr != q.end())
                {
                    titr = q.erase(itr);
                }
                dist[nbr] = egw + w;
                prev[nbr] = v;
                q.insert(make_pair(dist[nbr], nbr));
            }
        }
    }
}

// O(E*log(V)+V)
template <typename I, typename V>
V prims(wdgraph<I, V> &G, vector<I> &parent)
{
    parent.resize(G.n, -1);
    vector<bool> done(G.n);
    vector<V> lowedge(G.n, G.inf);
    set<pair<V, I>> pq;

    V tweight = 0;
    done[0] = true;
    parent[0] = 0;
    for (auto u : G.oadjl[0])
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

        for (auto v : G.oadjl[u])
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

template <typename I, typename V>
void assign_adj_matrix(wdgraph<I, V> &G, vector<vector<V>> &adjm)
{
    adjm.assign(G.n, vector<V>(G.n, G.inf));
    for (auto edg : G.edge_weight)
    {
        adjm[(edg.first / G.N)][(edg.second % G.N)] = edg.second;
    }
}

// O(V^3)
template <typename I, typename V>
void floyd_warshall(wdgraph<I, V> &G, vector<vector<V>> &min_distance)
{
    assign_adj_matrix(G, min_distance);
    vector<vector<V>> tmin_distance = min_distance;
    for (I k = 0; k < G.n; k++)
    {
        for (I i = 0; i < G.n; i++)
        {
            if (min_distance[i][k] == G.inf)
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

template <typename I, typename V>
void elist_to_parent(vector<pair<I, I>> &elist, vector<I> &parent)
{
}

// O(E*log(E)+V)
template <typename I, typename V>
V krushal(wdgraph<I, V> &G, vector<I> &parent)
{
    parent.resize(G.n, -1);
    priority_queue<pair<V, I>> epq;
    vector<I> dsu(G.n), sz(G.n);
    V tweight = 0;

    for (I i = 0; i < G.n; i++)
    {
        dsu[i] = i;
        sz[i] = 1;
        for (auto j : G.oadjl[i])
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
