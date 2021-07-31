#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename I>
class graph
{
public:
    I inf = 1e16;
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

    void input()
    {
        I m;
        I v1, v2;
        cin >> n > m;
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

template <typename I>
void assign_adj_matrix(graph<I> &G, vector<vector<I>> &adjm)
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
            dfs_rec(y, G, intime, otime, parent, visited,mytimer);
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
    for (I i = 0; i <G.n; i++)
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

template <typename I>
void compliment_graph(graph<I> &G, graph<I> &Gc)
{
    vector<bool> allset(G.n);
    for (I i = 0; i <G.n; i++)
    {
        allset[i] = true;
    }

    for (I i = 0; i <G.n; i++)
    {
        for (auto j : G.adjl[i])
        {
            allset[j] = false;
        }

        for (I j = 0; j <G.n; j++)
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
    for (I i = 0; i <G.n; i++)
    {
        dct[O.deg[i]]++;
        dct[G.deg[i]]--;
    }

    for (I i = 0; i <G.n; i++)
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
    if (!is_biparted(G,partion))
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
void dfs_bridges(graph<I> &G, vector<I> &tin, vector<I> &min_reachable_node,vector<bool> &visited)
{
    visited.assign(G.n,false);
    tin.assign(G.n,-1);
    min_reachable_node.assign(G.n,-1);
    vector<I> parent(G.n,-1);
    I itimer =0;
    stack<I> S;
    S.push(0);
    tin[0]=itimer;
    min_reachable_node[0]=itimer;
    itimer++;

    while(!S.empty())
    {
        I u = S.top();
        S.pop();
        if(visited[u])
        {
            // we are not maintianing tout so no need to update it
            // when the entire botto tree is assigned with min_reachable_node we update this node
            min_reachable_node[parent[u]]=min(min_reachable_node[parent[u]],tin[u]);
            itimer++;
            // this line maybe called many times so we cant process bridges till all loops are over
            continue;
        }
        visted[u]=true;
        tin[u] = itimer;
        min_reachable_node[u] = itimer;
        itimer++;
        

        for(auto v: G.adjl[u])
        {
            if(v == parent[u])
            {
                continue;
            }
            if(visited[v])
            {
                // back edge detected u -> v
                // min of the time which it can reach by taking the back edge is tin of that node or min already in min_reach_node
                min_reachable_node[u] = min(min_reachable_node[u],tin[v]);
            }
            else
            {
                // tree edge u->v
                S.push(u);
                S.push(v);
                parent[v]=u;
            }
        }
    }
}

template <typename I>
void dfs_bridges_rec(I v, I p, I rtimer, graph<I> &G, vector<I> &tin, vector<I> &min_reachable_node,vector<bool> &visited, vector<pair<I,I>> &bridges)
{
    // property : all the bridges will appear in any DFS at any node and any order
    visited[v] = true;
    tin[v]=rtimer;
    min_reachable_node[v]=rtimer;
    rtimer++;

    for(auto u: G.adjl[v])
    {
        if(u==p)
        {
            continue;
        }
        if(visited[u])
        {
            // back edge
            min_reachable_node[v] = min(min_reachable_node[v],tin[u]);
        }
        else
        {
            // calcualte the min_reachable node for all bottom nodes
            dfs_bridges_rec(u,v,rtimer,G,tin,min_reachable_node,visited,bridges);
            // update its min_reachable using that value as it can also reach it
            min_reachable_node[v] = min(min_reachable_node[v],min_reachable_node[u]);

            // after this we can check if edge v--u is a bridge or not as all the nodes below
            // u have been assigned a low so if its less or equal to tin[v] then it can reach v or its ancestors 
            // so its not a  bridge else its a bridge
            if(tin[v]>min_reachable_node[u])
            {
                bridges.push_back(make_pair(u,v));
            }
        }
    }
}

template <typename I>
I radius(graph<I> &G)
{
    I mnmxlv = 0;

    vector<I> seq(G.n);
    iota(seq.begin(), seq.end(), 1);
}

template <typename I>
void diameter(graph<I> &G)
{
}

template <typename I>
void eccentricity(graph<I> &G, I v)
{
}

template <typename I>
void center(graph<I> &G)
{
}

template <typename I>
void line_graph(graph<I> &G)
{
}

template <typename I>
void characterstics_polynomial(graph<I> &G)
{
}

template <typename I>
void eignevalues(graph<I> &G)
{
    // adj matrix
    // all are real if symmetric matrix, AM = GM ,
    // sum of all eigenvalues is 0 as all diagonal is 0
    // if graph is connected then Multiplicity of largest eigenvalue is 1
    // graph is biparted iff r is largest eigenvalue and -r is also the eigenvalue
    // value of largest eigenvalue is between avg degree and largets degree
}

template <typename I>
I tuckers_algorithm(graph<I> &G)
{
    I x;
    // new idea is to pair all the edges on a vertex into (in, out) pair
    return x;
}

void level_graph_dinitz(I s, I t, graph<I> &G, vector<vector<I>> &residual_capacity, vector<vector<I>> &flow, vector<I> &parents)
{
    return;
}

template <typename I>
I dinitz_algorithm(I s, I t, graph<I> &G, vector<vector<I>> &capacity, vector<vector<I>> &flow)
{
    I max_flow=0;
    flow = capacity;
    for(int i=0;i<flow.size();i++)
    {
        for(int j=0;j<flow[i].size();j++)
        {
            flow[j]=0;
        }
    }
    return max_flow;
}

template <typename I>
I augmenting_flow_bfs(I s, I t, graph<I> &G, vector<vector<I>> &residual_capacity, vector<I> &parents,vector<bool> &visited)
{
    visited.assign(G.n,false);
    queue<pair<I,I>> Q;
    Q.push(make_pair(s,G.inf));
    visited[s]=true;
    
    while (!Q.empty())
    {
        I u = Q.front().first;
        I af = Q.front().second;
        Q.pop();

        for(auto v : G.adjl[u])
        {
            if(visited[v]||(residual_capacity[u][v]<=0))
            {
                continue;
            }
            
            parents[v] = u;
            visited[v] = true;
            if(v==t)
            {
                parents[v] = u;
                return min(residual_capacity[u][v],af);
            }
            Q.push(make_pair(v,min(residual_capacity[u][v],af)));
        }
    }

    return 0;
}

template <typename I>
I edmonds_karp_max_flow(I s, I t, graph<I> &G, vector<vector<I>> &residual_capacity, vector<bool> &min_cut)
{
    min_cut.assign(G.n,false);
    I flow=0;
    I augmenting_flow=0;
    do
    {
        vector<I> parents(G.n,-1);
        augmenting_flow = augmenting_flow_bfs(s,t,G,residual_capacity,parents,min_cut);
        flow+=augmenting_flow;
        I ut = t;
        while (parents[ut]!=-1)
        {
            residual_capacity[parents[ut]][ut] -= augmenting_flow;
            residual_capacity[ut][parents[ut]] += augmenting_flow;
            ut = parents[ut];
        }
        
    } while (augmenting_flow>0);

    return flow;
}

