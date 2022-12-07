#pragma once
#include <bits/stdc++.h>
#include <limits>
#include "../utils/debug_out.hpp"

using namespace std;

template <typename I>
class graph
{
public:
    const I inf = std::numeric_limits<I>::max();
    I n = 0;
    I edge_count = 0;
    vector<vector<I>> adjl;
    vector<I> deg;

    graph() {}
    graph(I n)
    {
        this->n = n;
        this->edge_count = 0;
        this->adjl = vector<vector<I>>(n, vector<I>(0));
        this->deg = vector<I>(n, 0);
    }

    void resize(I n)
    {
        this->n = n;
        this->adjl = vector<vector<I>>(n, vector<I>(0));
        this->deg = vector<I>(n, 0);
    }

    virtual void input()
    {
        I m;
        I v1, v2;
        cin >> n >> m;
        for (I i = 0; i < m; i++)
        {
            cin >> v1 >> v2;
            this->add_edge(v1, v2);
        }
    }

    // O(1) amortized :: vector push_back
    void add_edge(I x, I y)
    {
        this->adjl[x].push_back(y);
        this->adjl[y].push_back(x);
        this->deg[x]++;
        this->deg[y]++;
        this->edge_count++;
    }

    // O(degree) amortized :: vector push_back
    void add_vertex(vector<I> &adj)
    {
        this->adjl.push_back(adj);
        this->deg.push_back(adj.size());
        for (auto x : adj)
        {
            this->adjl[x].push_back(this->n);
            this->deg[x]++;
        }
        this->n++;
    }

    // assumes that adjl has no special order
    void swap_vertex(I u, I v)
    {
        if (u == v)
            return;
        I szu = 0, szv = 0;
        for (auto w : adjl[u])
        {
            szu += (I)adjl[w].size();
        }
        for (auto w : adjl[v])
        {
            szv += (I)adjl[w].size();
        }
        if (szu > szv)
        {
            swap(u, v);
        }
        // assumes that szu <= szv

        for (auto w : adjl[u])
        {
            for (I i = 0; i < (I)adjl[w].size(); i++)
            {
                if (adjl[w][i] == u)
                {
                    // mark it as last node
                    adjl[w][i] = n;
                }
            }
        }
        for (auto w : adjl[v])
        {
            if (w == n)
            {
                // i.e. u and v are adj
                for (I i = 0; i < (I)adjl[u].size(); i++)
                {
                    if (adjl[u][i] == v)
                    {
                        // mark it as u i.e. new id
                        adjl[u][i] = u;
                    }
                }
                continue;
            }
            for (I i = 0; i < (I)adjl[w].size(); i++)
            {
                if (adjl[w][i] == v)
                {
                    // mark it as u i.e. new id
                    adjl[w][i] = u;
                }
            }
        }
        for (auto w : adjl[u])
        {
            if (w == u)
            {
                // assuming no self loop
                for (I i = 0; i < (I)adjl[v].size(); i++)
                {
                    if (adjl[v][i] == n)
                    {
                        // mark it as last node
                        adjl[v][i] = v;
                    }
                }
                continue;
            }
            for (I i = 0; i < (I)adjl[w].size(); i++)
            {
                if (adjl[w][i] == n)
                {
                    // mark it as last node
                    adjl[w][i] = v;
                }
            }
        }
        swap(adjl[u], adjl[v]);
    }

    void remove_vertex(I u)
    {
        this->swap_vertex(u, n - (I)1);
        I nm = n - (I)1;
        for (I v : this->adjl[nm])
        {
            I nz = (I)adjl[v].size() - (I)1;
            for (I i = 0; i < nz; i++)
            {
                if (this->adjl[v][i] == nm)
                {
                    swap(adjl[v][i], adjl[v][nz]);
                    // assuming simple graph, hence breaking
                    break;
                }
            }
            this->adjl[v].pop_back();
        }
        adjl.pop_back();
        this->n--;
    }

    graph<I> operator+(const graph<I> &O)
    {
        graph<I> GO(O.n + this->n);

        for (I i = 0; i < this->n; i++)
        {
            for (auto j : this->adjl[i])
            {
                if (j > i)
                    GO.add_edge(i, j);
            }
        }

        for (I i = 0; i < O.n; i++)
        {
            for (auto j : O.adjl[i])
            {
                if (j > i)
                    GO.add_edge(this->n + i, this->n + j);
            }
        }

        for (I i = 0; i < this->n; i++)
        {
            for (I j = 0; j < O.n; j++)
            {
                GO.add_edge(i, this->n + j);
            }
        }
        return GO;
    }

    void operator+=(const graph<I> &O)
    {
        graph<I> GO;
        for (I i = 0; i < this->n; i++)
        {
            for (auto j : this->adjl[i])
            {
                GO.add_edge(i, j);
            }
        }

        for (I i = 0; i < O.n; i++)
        {
            for (auto j : O.adjl[i])
            {
                GO.add_edge(this->n + i, this->n + j);
            }
        }

        for (I i = 0; i < this->n; i++)
        {
            for (I j = 0; j < O.n; j++)
            {
                GO.add_edge(i, this->n + j);
            }
        }
    }
};

template <typename I, typename V>
class wgraph : public graph<I>
{
public:
    I N = 1000007;
    const V inf_v = std::numeric_limits<V>::max();
    unordered_map<I, V> edge_weight;

    wgraph() : graph<I>() {}
    wgraph(I n) : graph<I>(n) {}

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

template <typename I>
void get_edge_list_of_graph(const graph<I> &G, vector<pair<I,I>> &edge_list)
{
    edge_list.clear();
    for(I u=0;u<G.n;u++)
    {
        for(I v: G.adjl[u])
        {
            if(u<=v) edge_list.push_back(make_pair(u,v));
        }
    }
}

template <typename I, typename R>
void get_edge_list_of_wgraph(const wgraph<I,R> &G, vector<pair<pair<I,I>,R>> &edge_list)
{
    edge_list.clear();
    for(I u=0;u<G.n;u++)
    {
        for(I v: G.adjl[u])
        {
            if(u<=v) edge_list.push_back(make_pair(make_pair(u,v),G.edge_weight[G.N*u+v]));
        }
    }
}

template <typename I>
void assign_adj_matrix(const graph<I> &G, vector<vector<I>> &adjm)
{
    adjm.assign(G.n, vector<I>(G.n, 0));
    for (I i = 0; i < G.n; i++)
    {
        for (auto j : G.adjl[i])
        {
            adjm[i][j] = 1;
        }
    }
}

template <typename I, typename V>
void assign_wadj_matrix(wgraph<I, V> &G, vector<vector<V>> &adjm)
{
    adjm.assign(G.n, vector<V>(G.n, 0));
    for (I i = 0; i < G.n; i++)
    {
        for (auto j : G.adjl[i])
        {
            adjm[i][j] = G.edge_weight[i * G.N + j];
        }
    }
}

template <typename I>
void bfs(I x, graph<I> &G, vector<I> &level, vector<bool> &visted)
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

template <typename I>
void dfs(I x, graph<I> &G, vector<I> &order, vector<I> &parent, vector<bool> &visited)
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

template <typename I>
void dfs(I x, graph<I> &G, vector<I> &tin, vector<I> &tout, vector<I> &parent, vector<bool> &visited)
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

template <typename I>
void dfs_rec(I x, graph<I> &G, vector<I> &intime, vector<I> &otime, vector<I> &parent, vector<bool> &visited, I &mytimer)
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

template <typename I>
I connected_components(graph<I> &G, vector<I> &component)
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

template <typename I>
bool is_biparted(graph<I> &G, vector<I> &partition)
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

template <typename I>
bool is_eulerian(graph<I> &G, pair<I, I> &p)
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
            if (ct > 2)
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

template <typename I>
void compliment_graph(graph<I> &G, graph<I> &Gc)
{
    vector<bool> allset(G.n);
    for (I i = 0; i < G.n; i++)
    {
        allset[i] = true;
    }

    for (I i = 0; i < G.n; i++)
    {
        for (auto j : G.adjl[i])
        {
            allset[j] = false;
        }

        for (I j = 0; j < G.n; j++)
        {
            if (allset[j] & i != j)
            {
                Gc.add_edge(i, j);
                allset[j] = true;
            }
        }
    }
}

template <typename I>
bool degree_isomorphic(const graph<I> &G, const graph<I> &O)
{
    if (O.n != G.n)
    {
        return false;
    }

    vector<I> dct(G.n, 0);
    for (I i = 0; i < G.n; i++)
    {
        dct[O.deg[i]]++;
        dct[G.deg[i]]--;
    }

    for (I i = 0; i < G.n; i++)
    {
        if (dct[i] != 0)
        {
            return false;
        }
    }

    return true;
}

// calcultes the coloring which will be given by the greedy method with the given ordering
template <typename I>
void ordering_to_coloring(graph<I> &G, vector<I> &ordering, vector<I> &coloring)
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

        // most inefficient part might take linear time inG.n
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

template <typename I>
void degree_order_coloring(graph<I> &G, vector<I> &coloring)
{
    vector<pair<I, I>> plst;
    vector<I> ordering(G.n);
    for (I i = 0; i < G.n; i++)
    {
        plst.push_back(make_pair(G.deg[i], i));
    }

    sort(plst.begin(), plst.end());
    for (I i = 0; i < G.n; i++)
    {
        ordering[i] = plst[G.n - 1 - i].second;
    }

    G.ordering_to_coloring(ordering, coloring);
}

// need to test section
template <typename I>
void A_star(graph<I> &G, I (*heuristic)(I), I source, I target, vector<I> &dist, vector<I> &parent)
{
    priority_queue<pair<I, I>> pq;
    vector<bool> vis(G.n, false);
    dist.assign(G.n, G.inf);
    parent.assign(G.n);
    dist[source] = 0;
    parent[source] = source;
    pq.push({(I)0, source});

    while (!pq.empty())
    {
        auto min_state = pq.top();
        pq.pop();
        if (vis[min_state.second])
            continue;

        vis[min_state.second] = true;

        for (auto u : G.adjl[min_state.second])
        {
            if (vis[u])
                continue;
            I h_val = heuristic(u);
            if (dist[u] > dist[min_state.second] + h_val + 1)
            {
                parent[u] = min_state.second;
                dist[u] = dist[min_state.second] + h_val + 1;
                pq.push({(-1) * dist[u], u});
            }
        }
    }
}

template <typename I>
bool perfect_biparted_matching(graph<I> &G, vector<I> &matching)
{
    vector<I> partion;
    if (!is_biparted(G, partion))
    {
        return false;
    }
    I ct = 0;
    for (auto t : partion)
    {
        if (t == 1)
            ct++;
    }

    if (2 * ct != G.n)
    {
        return false;
    }

    // O(E), compute initial matching
    I matching_size = 0;
    matching.assign(G.n, -1);
    for (I u = 0; u < G.n; u++)
    {
        if (matching[u] != -1)
        {
            continue;
        }
        for (auto v : G.adjl[u])
        {
            if (matching[v] == -1)
            {
                matching[u] = v;
                matching[v] = u;
                matching_size++;
                break;
            }
        }
    }

    // max O(V)
    while (true)
    {
        I new_matching_size = matching_size;
        I x = -1;
        for (I i = 0; i < G.n; i++)
        {
            if (matching[i] == -1)
            {
                x = i;
                break;
            }
        }
        if (x == -1)
        {
            break;
        }
    }

    return true;
}

template <typename I>
void dfs_bridges(graph<I> &G, vector<I> &tin, vector<I> &min_reachable_node, vector<bool> &visited)
{
    visited.assign(G.n, false);
    tin.assign(G.n, -1);
    min_reachable_node.assign(G.n, -1);
    vector<I> parent(G.n, -1);
    I itimer = 0;
    stack<I> S;
    S.push(0);
    tin[0] = itimer;
    min_reachable_node[0] = itimer;
    itimer++;

    while (!S.empty())
    {
        I u = S.top();
        S.pop();
        if (visited[u])
        {
            // we are not maintianing tout so no need to update it
            // when the entire botto tree is assigned with min_reachable_node we update this node
            min_reachable_node[parent[u]] = min(min_reachable_node[parent[u]], tin[u]);
            itimer++;
            // this line maybe called many times so we cant process bridges till all loops are over
            continue;
        }
        visited[u] = true;
        tin[u] = itimer;
        min_reachable_node[u] = itimer;
        itimer++;

        for (auto v : G.adjl[u])
        {
            if (v == parent[u])
            {
                continue;
            }
            if (visited[v])
            {
                // back edge detected u -> v
                // min of the time which it can reach by taking the back edge is tin of that node or min already in min_reach_node
                min_reachable_node[u] = min(min_reachable_node[u], tin[v]);
            }
            else
            {
                // tree edge u->v
                S.push(u);
                S.push(v);
                parent[v] = u;
            }
        }
    }
}

template <typename I>
void dfs_bridges_rec(I v, I p, I rtimer, graph<I> &G, vector<I> &tin, vector<I> &min_reachable_node, vector<bool> &visited, vector<pair<I, I>> &bridges)
{
    // property : all the bridges will appear in any DFS at any node and any order
    visited[v] = true;
    tin[v] = rtimer;
    min_reachable_node[v] = rtimer;
    rtimer++;

    for (auto u : G.adjl[v])
    {
        if (u == p)
        {
            continue;
        }
        if (visited[u])
        {
            // back edge
            min_reachable_node[v] = min(min_reachable_node[v], tin[u]);
        }
        else
        {
            // calcualte the min_reachable node for all bottom nodes
            dfs_bridges_rec(u, v, rtimer, G, tin, min_reachable_node, visited, bridges);
            // update its min_reachable using that value as it can also reach it
            min_reachable_node[v] = min(min_reachable_node[v], min_reachable_node[u]);

            // after this we can check if edge v--u is a bridge or not as all the nodes below
            // u have been assigned a low so if its less or equal to tin[v] then it can reach v or its ancestors
            // so its not a  bridge else its a bridge
            if (tin[v] > min_reachable_node[u])
            {
                bridges.push_back(make_pair(u, v));
            }
        }
    }
}

template <typename I>
void dfs_cut_vertices(I v, I p,graph<I> &G, vector<bool> &visited, vector<I> &tin, vector<I> &low, I &timer, vector<I> &is_cut_vertex)
{
    visited[v] = true;
    tin[v] = low[v] = timer++;
    I children = 0;
    for (I to : G.adj[v])
    {
        if (to == p)
            continue;
        if (visited[to])
        {
            low[v] = min(low[v], tin[to]);
        }
        else
        {
            dfs_cut_vertices(to, v,G, visited, tin, low, timer);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p != -(I)1)
            {
                is_cut_vertex[v] = 1;
            }
            ++children;
        }
    }
    if (p == -(I)1 && children > (I)1)
    {
        is_cut_vertex[v] = 1;
    }
}

template <typename I>
void cut_vertices(graph<I> &G, vector<I> &is_cut_vertex)
{
    I timer = (I)0;
    is_cut_vertex.assign(G.n, 0);
    vector<bool> visited(G.n, false);
    vector<I> tin(G.n, -(I)1), low(G.n, -(I)1);

    for (int i = 0; i < G.n; ++i)
    {
        if (!visited[i])
        {
            dfs_cut_vertices(i,-(I)1,G,visited,tin,low,is_cut_vertex);
        }
    }
}

template <typename I>
I eccentricity(graph<I> &G, I v)
{
    vector<I> level(G.n, -1);
    queue<pair<I, I>> q;
    q.push({v, (I)0});
    while (!q.empty())
    {
        I u = q.top();
        I ul = q.top().second;
        q.pop();
        if (level[u] == -1)
        {
            level[u] = ul;
            for (auto nu : G.adjl[u])
            {
                if (level[nu] == -1)
                {
                    q.push({nu, level[u] + (I)1});
                }
            }
        }
    }
    I ec = 0;
    for (I i = 0; i < G.n; i++)
    {
        if (level[i] == -1)
            return level[i];
        else
            ec = max(ec, level[i]);
    }
    return ec;
}

template <typename I>
I radius(graph<I> &G)
{
    I r = std::numeric_limits<I>::max();
    for (I i = 0; i < G.n; i++)
    {
        r = min(r, eccentricity(G, i));
        if (r == -1)
            return r;
    }
    return r;
}

template <typename I>
I diameter(graph<I> &G)
{
    I r = -1;
    for (I i = 0; i < G.n; i++)
    {
        r = max(r, eccentricity(G, i));
        if (r == -1)
            return r;
    }
    return r;
}

template <typename I>
I center_vertex(graph<I> &G)
{
    I r = std::numeric_limits<I>::max();
    I c = -1;
    for (I i = 0; i < G.n; i++)
    {
        I ec = eccentricity(G, i);
        if (ec == -1)
            return ec;
        if (ec < r)
        {
            r = ec;
            c = i;
        }
    }
    return c;
}

template <typename I>
I peripheral_vertex(graph<I> &G)
{
    I r = -1;
    I c = -1;
    for (I i = 0; i < G.n; i++)
    {
        I ec = eccentricity(G, i);
        if (ec == -1)
            return ec;
        if (ec > r)
        {
            r = ec;
            c = i;
        }
    }
    return c;
}

template <typename I>
graph<I> line_graph(graph<I> &G)
{
    graph<I> lg(G.edge_count);
    vector<unordered_map<I, I>> e2n(G.n, unordered_map<I, I>());
    I ectid = 0;
    for (I u = 0; u < G.n; u++)
    {
        for (auto v : G.adjl[u])
        {
            if (u < v)
            {
                e2n[u][v] = ectid;
                ectid++;
            }
            else
            {
                e2n[u][v] = e2n[v][u];
            }
        }
    }
    assert(ectid == G.edge_count);

    for (I u = 0; u < G.n; u++)
    {
        for (I i = 0; i < G.adjl[u].size(); i++)
        {
            lg.add_edge(G.adjl[u][i], u);
            for (I j = i + 1; j < G.adjl[u].size(); j++)
            {
                lg.add_edge(G.adjl[u][i], G.adjl[u][j]);
            }
        }
    }
    return lg;
}

template <typename I>
bool tuckers_algorithm(graph<I> &G, vector<unordered_map<I, I>> &edge_order)
{
    pair<I, I> p;
    if (!is_eulerian(G, p))
    {
        return false;
    }
    edge_order.assign(G.n, unordered_map<I, I>());
    vector<I> net_dir(G.n, 0);
    net_dir[p.first]--;
    net_dir[p.second]++;

    for (I u = 0; u < G.n; u++)
    {
        I i = 0;
        while (net_dir[u] != 0 && i < G.adjl[u].size())
        {
            I v = G.adjl[u][i];
            if (edge_order[u][v] == 0)
            {
                if (net_dir[u] < 0)
                {
                    edge_order[u][v] = 1;
                    edge_order[v][u] = -1;
                    net_dir[u]++;
                    net_dir[v]--;
                }
                else
                {
                    edge_order[u][v] = -1;
                    edge_order[v][u] = 1;
                    net_dir[u]--;
                    net_dir[v]++;
                }
            }
            i++;
        }
        for (; i < G.adjl[u].size(); i++)
        {
            I v = G.adjl[u][i];
            if (edge_order[u][v] == 0)
            {
                if (i % 2 == 0)
                {
                    edge_order[u][v] = 1;
                    edge_order[v][u] = -1;
                    net_dir[u]++;
                    net_dir[v]--;
                }
                else
                {
                    edge_order[u][v] = -1;
                    edge_order[v][u] = 1;
                    net_dir[u]--;
                    net_dir[v]++;
                }
            }
        }
    }
    return true;
}

// FIXME complete
template <typename I>
void level_graph_dinitz(I s, I t, graph<I> &G, vector<vector<I>> &residual_capacity, vector<vector<I>> &flow, vector<I> &parents)
{
    return;
}

// FIXME complete
template <typename I>
I dinitz_algorithm(I s, I t, graph<I> &G, vector<vector<I>> &capacity, vector<vector<I>> &flow,vector<bool> &min_cut)
{
    I max_flow = 0;
    return max_flow;
}

template <typename I>
I augmenting_flow_bfs(I s, I t, graph<I> &G, vector<unordered_map<I, I>> &residual_capacity, vector<I> &parents, vector<bool> &visited)
{
    visited.assign(G.n, false);
    queue<pair<I, I>> Q;
    Q.push(make_pair(s, G.inf));
    visited[s] = true;
    while (!Q.empty())
    {
        I u = Q.front().first;
        I af = Q.front().second;
        Q.pop();

        for (auto v : G.adjl[u])
        {
            if (visited[v] || (residual_capacity[u][v] == 0))
            {
                continue;
            }
            parents[v] = u;
            visited[v] = true;
            if (v == t)
            {
                parents[v] = u;
                return min(residual_capacity[u][v], af);
            }
            Q.push(make_pair(v, min(residual_capacity[u][v], af)));
        }
    }
    return 0;
}

template <typename I>
I edmonds_karp_max_flow(I s, I t, graph<I> &G, vector<unordered_map<I, I>> &residual_capacity, vector<bool> &min_cut)
{
    min_cut.assign(G.n, false);
    I flow = 0;
    I augmenting_flow = 0;
    do
    {
        vector<I> parents(G.n, -1);
        augmenting_flow = augmenting_flow_bfs(s, t, G, residual_capacity, parents, min_cut);
        flow += augmenting_flow;
        I ut = t;
        while (parents[ut] != -1)
        {
            residual_capacity[parents[ut]][ut] -= augmenting_flow;
            residual_capacity[ut][parents[ut]] += augmenting_flow;
            ut = parents[ut];
        }

    } while (augmenting_flow != 0);
    return flow;
}

// O(E*log(E)+V)
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

// O(E*log(E)+E*log_star(V)+V)
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
            ida = dsu[ida] = dsu[dsu[ida]];
        while (idb != dsu[idb])
            idb = dsu[idb] = dsu[dsu[idb]];

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

// O(E*W+E*log_star(V)+V)
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
        while (ida != dsu[ida])
            ida = dsu[ida] = dsu[dsu[ida]];
        while (idb != dsu[idb])
            idb = dsu[idb] = dsu[dsu[idb]];

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
