#pragma once
#include <bits/stdc++.h>
using namespace std;
// FIXME compile problems
// FIXME dinitz and emp correctness
template <typename I>
class dgraph
{
public:
    I inf = 1e16;
    I n;
    vector<vector<I>> oadjl;
    vector<vector<I>> iadjl;
    vector<I> odeg;
    vector<I> ideg;

    dgraph(I n)
    {
        this->n = n;
        this->oadjl = vector<vector<I>>(n, vector<I>(0));
        this->iadjl = vector<vector<I>>(n, vector<I>(0));
        this->odeg = vector<I>(n, 0);
        this->ideg = vector<I>(n, 0);
    }

    void resize(I n)
    {
        this->n = n;
        this->oadjl = vector<vector<I>>(n, vector<I>(0));
        this->iadjl = vector<vector<I>>(n, vector<I>(0));
        this->odeg = vector<I>(n, 0);
        this->ideg = vector<I>(n, 0);
    }

    void add_edge(I x, I y)
    {
        this->oadjl[x].push_back(y);
        this->iadjl[y].push_back(x);
        this->odeg[x]++;
        this->ideg[y]++;
    }

    void add_vertex(vector<I> &id, vector<I> &od)
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
        }

        for (I i = 0; i < od.size(); i++)
        {
            this->oadjl[this->n].push_back(od[i]);
            this->iadjl[od[i]].push_back(this->n);
            this->ideg[od[i]]++;
        }

        this->n++;
    }

    void invert_edges()
    {
        swap(this->oadjl, this->iadjl);
        swap(this->odeg, this->ideg);
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
};

template <typename I>
void bfs(I x, dgraph<I> &G, vector<I> &level, vector<bool> &visted)
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

template <typename I>
void dfs(I x, dgraph<I> &G, vector<I> &order, vector<I> &parent, vector<bool> &visited)
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

template <typename I>
void dfs(I x, dgraph<I> &G, vector<I> &tin, vector<I> &tout, vector<I> &parent, vector<bool> &visited)
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

template <typename I>
I underlining_connected_components(dgraph<I> &G, vector<I> &component)
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

template <typename I>
bool topological_sort(dgraph<I> &G, vector<I> &sorted_vertices)
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

template <typename I>
void assign_adj_matrix(dgraph<I> &G, vector<vector<I>> &adjm)
{
    adjm.assign(G.n, vector<I>(G.n, 0));
    for(I i=0;i<G.n;i++)
    {
        for(auto u: G.oadjl[i])
        {
            adjm[i][u] = 1;
        }
    }
}

// O(V^3)
template <typename I>
void floyd_warshall_transative_closure(dgraph<I> &G, vector<vector<I>> &closure)
{
    assign_adj_matrix(G, closure);
    vector<vector<I>> tclosure = closure;
    for (I k = 0; k < G.n; k++)
    {
        for (I i = 0; i < G.n; i++)
        {
            if (closure[i][k] == 0)
            {
                continue;
            }

            for (I j = 0; j < G.n; j++)
            {
                tclosure[i][j] = min(closure[i][j], closure[i][k] + closure[k][j]);
            }
        }
        closure = tclosure;
    }
}

template <typename I>
I tuckers_algorithm()
{
    return 0;
}

template <typename I>
I dinics_algorithm()
{
    I max_flow;

    return max_flow;
}

template <typename I>
I augmenting_flow_bfs(I s, I t, dgraph<I> &G, vector<vector<I>> &residual_capacity, vector<I> &parents,vector<bool> &visited)
{
    visited.assign(G.n,false);
    queue<pair<I,I>> Q;
    Q.push(make_pair(s,G.inf));
    visited[s]=true;
    
    while (!Q.empty())
    {
        pair<I,I> uaf = Q.front();
        I u = uaf.first;
        I af = uaf.second;
        Q.pop();

        for(auto v : G.oadjl[u])
        {
            if(visited[v]||(residual_capacity[u][v]<=0))
            {
                continue;
            }
            parents[v] = u;
            visited[v] = true;
            if(v==t)
            {
                return min(residual_capacity[u][v],af);
            }
            Q.push(make_pair(v,min(residual_capacity[u][v],af)));
        }
    }

    return 0;
}

// FIXME correct the error of not finding optimal path check other resources
template <typename I>
I edmonds_karp_max_flow(I s, I t, dgraph<I> &G, vector<vector<I>> &residual_capacity, vector<bool> &min_cut)
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

