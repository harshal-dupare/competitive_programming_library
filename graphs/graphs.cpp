#include <bits/stdc++.h>
#include "../utils/timer.h"

using namespace std;

#define ok(vari) cerr << #vari << " = " << (vari) << endl;
#define oka(a, L, R)              \
    cerr << #a << " : " << endl;  \
    for (int64 i = L; i < R; i++) \
        cerr << a[i] << " ";      \
    cerr << endl;
#define oks(s)                   \
    cerr << #s << " : " << endl; \
    for (auto x : s)             \
        cerr << x << " ";        \
    cerr << endl;
#define okp(ps)                                         \
    cerr << #ps << " : " << endl;                       \
    for (auto x : ps)                                   \
        cerr << (x.first) << ":" << (x.second) << ", "; \
    cerr << endl;
#define reply(a) cout << a << endl;

template <typename I>
class graph;

template <typename I>
class generator
{
public:
    void line(I n, graph<I> &G)
    {
    }

    void complete(I n, graph<I> &G)
    {
    }

    void cycle(I n, graph<I> &G)
    {
    }

    void k_regular(I k, I n, graph<I> &G)
    {
    }

    void hypercube(I n, graph<I> &G)
    {
    }

    void octahedral(I n, graph<I> &G)
    {
        // scope to optimize
        this->complete(2, G);
        graph<I> K2;
        for (I i = 1; i < n; i++)
        {
            G = G + K2;
        }
    }

    void complete_biparted(I n, I m, graph<I> &G)
    {
    }

    void perterson(graph<I> &G)
    {
    }

}

template <typename I>
class graph
{
public:
    class edge
    {
    public:
        I v1;
        I v2;
        I weight;
        edge(I v1, I v2, I weight)
        {
            if (v2 > v1)
                swap(v2, v1);
            this->v2 = v2;
            this->v1 = v1;
            this->weight = weight;
        }

        bool operator<(const edge &other)
        {
            return this->weight < other.weight;
        }
    };

    // primary data
    I n;
    I edge_count;
    vector<vector<I>> adjl;
    vector<I> deg;

    // secondary data
    I inf = 1e+12;
    I null_value = 0;
    vector<vector<I>> adjm;

    graph();
    graph(I n)
    {
        this->n = n;
        this->edge_count = 0;
        this->adjl = vector<vector<I>>(n, vector<I>(0));
        this->deg = vector<I>(n, 0);
    }

    void add_edge(I x, I y)
    {
        this->adjl[x].push_back(y);
        this->adjl[y].push_back(x);
        this->deg[x]++;
        this->deg[y]++;
        this->edge_count++;
    }

    void set_adjM()
    {
        this->adjm.assign(n, vector<I>(n, this->inf));
        for (I i = 0; i < n; i++)
        {
            adjm[i][i] = this->null_value;
            for (auto j : this->adjl[i])
            {
                adjm[i][j] = 1;
            }
        }
    }

    void add_vertex(vector<pair<I, I>> &adj)
    {
        this->adjl.push_back(vector<I>(0));
        this->deg.push_back(adj.size());
        for (auto x : adj)
        {
            this->adjl[this->n].push_back(x);
            this->adjl[x.first].push_back(this->n);
            this->deg[x.first]++;
        }
        this->n++;
    }

    void bfs(I x, vector<I> &level, vector<bool> &visted)
    {
        queue<I> snow;

        snow.push(x);
        level[x] = 0;

        while (!snow.empty())
        {
            auto t = snow.front();
            visted[t] = true;
            snow.pop();
            for (auto y : adjl[t])
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

    void dfs(I x, vector<I> &order, vector<I> &parent, vector<bool> &visted)
    {
        stack<I> snow;
        snow.push(x);

        I ct = 0;
        parent[x] = x;

        while (!snow.empty())
        {
            auto t = snow.top();
            visted[t] = true;
            order[t] = ct;
            ct++;
            snow.pop();
            for (auto y : adjl[t])
            {
                if (!visted[y])
                {
                    order[y] = ct;
                    parent[y] = t;
                    ct++;
                    visted[y] = true;
                    snow.push(y);
                }
            }
        }
    }

    I connected_components(vector<I> &component)
    {
        component.assign(this->n, -1);

        I c = 0;
        I at = 0;

        while (at < this->n)
        {
            // do bfs for each vertex and get the component indexed
            queue<I> snow;
            snow.push(at);

            while (!snow.empty())
            {
                auto t = snow.front();
                component[t] = c;
                snow.pop();
                for (auto y : adjl[t])
                {
                    if (component[y] == -1)
                    {
                        component[y] = c;
                        snow.push(y);
                    }
                }
            }
            c++;
            while (component[at] != -1 && at < this->n)
                at++;
        }

        return c;
    }

    bool is_biparted(vector<I> &partition)
    {
        bool poss = true;
        queue<I> q;
        q.push(0);
        partition.assign(this->n, -1);
        partition[0] = 0;
        while (!q.empty())
        {
            I x = q.front();
            q.pop();
            for (auto y : this->adjl[x])
            {
                if (partition[y] == partition[x])
                {
                    poss = false;
                    break;
                }
                if (partition[y] == -1)
                {
                    partition[y] = partition[x] ^ 1;
                    q.push(y);
                }
            }

            if (!poss)
                break;
        }

        return poss;
    }

    bool is_eulerian(pair<I, I> &p)
    {
        p.first = -1;
        p.second = -1;
        I ct = 0;
        for (I i = 0; i < n; i++)
        {
            if (this->deg[i] & 1)
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
        else
        {
            return true;
        }
    }

    void compliment_graph(graph<I> &Gc)
    {
        vector<bool> allset(n);
        for (I i = 0; i < n; i++)
        {
            allset[i] = true;
        }

        for (I i = 0; i < n; i++)
        {
            for (auto j : this->adjl[i])
            {
                allset[j] = false;
            }

            for (I j = 0; j < n; j++)
            {
                if (allset[j] & i != j)
                {
                    Gc.add_edge(i, j);
                    allset[j] = true;
                }
            }
        }
    }

    bool degree_isomorphic(const graph<I> &O)
    {
        if (O.n != this->n)
        {
            return false;
        }

        vector<I> dct(n, 0);
        for (I i = 0; i < n; i++)
        {
            dct[O.deg[i]]++;
            dct[this->deg[i]]--;
        }

        for (I i = 0; i < n; i++)
        {
            if (dct[i] != 0)
            {
                return false;
            }
        }

        return true;
    }

    // calcultes the coloring which will be given by the greedy method with the given ordering
    void ordering_to_coloring(vector<I> &ordering, vector<I> &coloring)
    {
        vector<bool> cposs(this->n, true);
        stack<I> toremove;
        coloring.assign(this->n, -1);
        coloring[ordering[0]] = 0;

        for (I i = 1; i < this->n; i++)
        {
            for (auto nbr : this->adjl[ordering[i]])
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

    void degree_order_coloring(vector<I> &coloring)
    {
        vector<pair<I, I>> plst;
        vector<I> ordering(n);
        for (I i = 0; i < this->n; i++)
        {
            plst.push_back(make_pair(this->deg[i], i));
        }

        sort(plst.begin(), plst.end());
        for (I i = 0; i < this->n; i++)
        {
            ordering[i] = plst[this->n - 1 - i].second;
        }

        this->ordering_to_coloring(ordering, coloring);
    }

    graph<I> operator+(const graph<I> &O)
    {
        graph<I> GO(O.n + this->n);

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

    // need to complete section

    void radius()
    {
    }

    void diameter()
    {
    }

    void eccentricity(I v)
    {
    }

    void center()
    {
    }

    void line_graph()
    {
    }

    I tuckers_algorithm()
    {
        // new idea is to pair all the edges on a vertex into (in, out) pair
    }

    void floyd_warshall(vector<vector<I>> &d)
    {
        d = this->adjm;
        for (I k = 0; k < n; k++)
        {
            for (I i = 0; i < n; i++)
            {
                for (I j = 0; j < n; j++)
                {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    I grith()
    {
        // length of shortest cycle
    }

    void bridges(vector<pair<I, I>> &bridges)
    {
        stack<I> st;
        stack<I> back_vertex;
        vector<I> processed(this->n, -1);
        st.push(0);

        while (!st.empty())
        {
            I x = st.top();
            st.pop();
            processed[x] = 1;
            for (auto y : this->adj[x])
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

    void prims()
    {
        set<pair<I, I>> pq;
        pq.insert(make_pair(0, 0));
        for (I i = 1; i < this->n; i++)
        {
        }
    }

    I dinics_algorithm()
    {
        I max_flow;

        return max_flow;
    }

    // utils

    void print_deg()
    {
        for (I i = 0; i < this->n; i++)
        {
            cout << i << ":" << this->deg[i] << ", ";
        }
        cout << endl;
    }

    void print_adjl()
    {
        I i = 0;
        for (auto x : this->adjl)
        {
            cout << i << ": ";
            for (auto y : x)
            {
                cout << y << ", ";
            }
            cout << endl;
            i++;
        }
    }
};

template <typename I, typename V>
class wgraph
{
public:
    class edge
    {
    public:
        I v1;
        I v2;
        I weight;
        edge(I v1, I v2, I weight)
        {
            if (v2 > v1)
                swap(v2, v1);
            this->v2 = v2;
            this->v1 = v1;
            this->weight = weight;
        }

        bool operator<(const edge &other)
        {
            return this->weight < other.weight;
        }
    };

    // primary data
    I n;
    vector<vector<I>> adjl;
    vector<I> deg;

    // secondary data
    I inf = 1e+12;
    I null_value = 0;
    vector<vector<I>> adjm;
    unordered_map<I, I> edge_weight;

    wgraph(I n)
    {
        this->n = n;
        this->adjl = vector<vector<I>>(n, vector<I>(0));
        this->deg = vector<I>(n, 0);
    }

    void add_edge(I x, I y, I w)
    {
        this->adjl[x].push_back(y);
        this->adjl[y].push_back(x);
        this->deg[x]++;
        this->deg[y]++;
        this->edge_weight[x * n + y] = w;
    }

    void set_adjWM()
    {
        this->adjm.assign(n, vector<I>(n, this->inf));
        for (I i = 0; i < n; i++)
        {
            adjm[i][i] = this->null_value;
            for (auto j : this->adjl[i])
            {
                adjm[i][j] = edge_weight[i * n + j];
            }
        }
    }

    void add_vertex(vector<pair<I, I>> &adj)
    {
        this->adjl.push_back(vector<I>(0));
        this->deg.push_back(adj.size());
        for (auto x : adj)
        {
            this->adjl[this->n].push_back(x);
            this->adjl[x.first].push_back(this->n);
            this->deg[x.first]++;
        }
        this->n++;
    }

    void bfs(I x, vector<I> &level, vector<bool> &visted)
    {
        queue<I> snow;

        snow.push(x);
        level[x] = 0;

        while (!snow.empty())
        {
            auto t = snow.front();
            visted[t] = true;
            snow.pop();
            for (auto y : adjl[t])
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

    void dfs(I x, vector<I> &order, vector<I> &parent, vector<bool> &visted)
    {
        stack<I> snow;

        snow.push(x);
        I ct = 0;
        parent[x] = x;

        while (!snow.empty())
        {
            auto t = snow.top();
            visted[t] = true;
            order[t] = ct;
            ct++;
            snow.pop();
            for (auto y : adjl[t])
            {
                if (!visted[y])
                {
                    order[y] = ct;
                    parent[y] = t;
                    ct++;
                    visted[y] = true;
                    snow.push(y);
                }
            }
        }
    }

    I connected_components(vector<I> &component)
    {
        component.assign(this->n, -1);

        I c = 0;
        I at = 0;

        while (at < this->n)
        {
            // do bfs for each vertex and get the component indexed
            queue<I> snow;
            snow.push(at);

            while (!snow.empty())
            {
                auto t = snow.front();
                component[t] = c;
                snow.pop();
                for (auto y : adjl[t])
                {
                    if (component[y] == -1)
                    {
                        component[y] = c;
                        snow.push(y);
                    }
                }
            }
            c++;
            while (component[at] != -1 && at < this->n)
                at++;
        }

        return c;
    }

    // need to complete
    void bridges(vector<pair<I, I>> &bridges)
    {
        stack<I> st;
        stack<I> back_vertex;
        vector<I> processed(this->n, -1);
        st.push(0);

        while (!st.empty())
        {
            I x = st.top();
            st.pop();
            processed[x] = 1;
            for (auto y : this->adj[x])
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

    // O(Elog(E)) time
    void dijkstra(I x, vector<I> &dist, vector<I> &prev)
    {
        dist.assign(this->n, 1000007);
        vector<bool> relaxed(this->n, false);
        dist[x] = 0;
        prev.assign(this->n, 0);
        prev[x] = x;
        // value and index
        priority_queue<pair<I, I>> q;
        q.push(make_pair(0, x));

        while (!q.empty())
        {
            auto vw = q.top();
            I v = vw.second;
            I w = (vw.first) * (-1);
            q.pop();
            if (relaxed[v])
            {
                continue;
            }
            else
            {
                relaxed[v] = true;
            }

            for (auto nbr : this->adjl[v])
            {
                I weg = adjm[make_pair(v, nbr)];
                if ((!relaxed[nbr]) && dist[v] + w < dist[nbr])
                {
                    dist[nbr] = dist[v] + w;
                    prev[nbr] = v;
                    q.push(make_pair((-1) * dist[nbr], nbr));
                }
            }
        }
    }

    // need to complete
    void floyd_warshall(vector<vector<I>> &d)
    {
        d = this->adjm;
        for (I k = 0; k < n; k++)
        {
            for (I i = 0; i < n; i++)
            {
                for (I j = 0; j < n; j++)
                {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    bool is_biparted(vector<I> &partition)
    {
        bool poss = true;
        queue<I> q;
        q.push(0);
        partition.assign(this->n, -1);
        partition[0] = 0;
        while (!q.empty())
        {
            I x = q.front();
            q.pop();
            for (auto y : this->adjl[x])
            {
                if (partition[y] == partition[x])
                {
                    poss = false;
                    break;
                }
                if (partition[y] == -1)
                {
                    partition[y] = partition[x] ^ 1;
                    q.push(y);
                }
            }

            if (!poss)
                break;
        }

        return poss;
    }

    // need to complete
    void prims()
    {
        set<pair<I, I>> pq;
        pq.insert(make_pair(0, 0));
        for (I i = 1; i < this->n; i++)
        {
        }
    }

    // need to complete
    I dinics_algorithm()
    {
        I max_flow;

        return max_flow;
    }

    // calcultes the coloring which will be given by the greedy method with the given ordering
    void ordering_to_coloring(vector<I> &ordering, vector<I> &coloring)
    {
        vector<bool> cposs(this->n, true);
        stack<I> toremove;
        coloring.assign(this->n, -1);
        coloring[ordering[0]] = 0;

        for (I i = 1; i < this->n; i++)
        {
            for (auto nbr : this->adjl[ordering[i]])
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

    void degree_order_coloring(vector<I> &ordering)
    {
        vector<pair<I, I>> plst;
        for (I i = 0; i < this->n; i++)
        {
            plst.push_back(make_pair(this->deg[i], i));
        }

        sort(plst.begin(), plst.end());
        for (I i = 0; i < this->n; i++)
        {
            ordering[i] = plst[this->n - 1 - i].second;
        }

        return this->ordering_to_coloring(ordering);
    }

    void print_deg()
    {
        for (I i = 0; i < this->n; i++)
        {
            cout << i << ":" << this->deg[i] << ", ";
        }
        cout << endl;
    }

    void print_adjl()
    {
        I i = 0;
        for (auto x : this->adjl)
        {
            cout << i << ": ";
            for (auto y : x)
            {
                cout << y << ", ";
            }
            cout << endl;
            i++;
        }
    }
};

template <typename I>
class dgraph
{
public:
    class dedge
    {
    public:
        I from;
        I to;
        I weight;
        dedge(I from, I to, I weight)
        {
            this->from = from;
            this->to = to;
            this->weight = weight;
        }
    };

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

    void add_edge(I x, I y)
    {
        this->oadjl[x].push_back(y);
        this->iadjl[y].push_back(x);
        this->odeg[x]++;
        this->ideg[y]++;
    }

    void bfs(I x, vector<I> &level, vector<bool> &visted)
    {
        queue<I> snow;

        snow.push(x);
        level[x] = 0;

        while (!snow.empty())
        {
            auto t = snow.front();
            visted[t] = true;
            snow.pop();
            for (auto y : oadjl[t])
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

    void dfs(I x, vector<I> &order, vector<I> &parent, vector<bool> &visted)
    {
        stack<I> snow;

        snow.push(x);
        I ct = 0;
        parent[x] = x;

        while (!snow.empty())
        {
            auto t = snow.top();
            visted[t] = true;
            order[t] = ct;
            ct++;
            snow.pop();
            for (auto y : oadjl[t])
            {
                if (!visted[y])
                {
                    order[y] = ct;
                    parent[y] = t;
                    ct++;
                    visted[y] = true;
                    snow.push(y);
                }
            }
        }
    }

    // need to complete section

    I tuckers_algorithm()
    {
    }

    void floyd_warshall(vector<vector<I>> &d)
    {
        d = this->adjm;
        for (I k = 0; k < n; k++)
        {
            for (I i = 0; i < n; i++)
            {
                for (I j = 0; j < n; j++)
                {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    I grith()
    {
        // length of shortest cycle
    }

    void bridges(vector<pair<I, I>> &bridges)
    {
        stack<I> st;
        stack<I> back_vertex;
        vector<I> processed(this->n, -1);
        st.push(0);

        while (!st.empty())
        {
            I x = st.top();
            st.pop();
            processed[x] = 1;
            for (auto y : this->adj[x])
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

    void prims()
    {
        set<pair<I, I>> pq;
        pq.insert(make_pair(0, 0));
        for (I i = 1; i < this->n; i++)
        {
        }
    }

    I dinics_algorithm()
    {
        I max_flow;

        return max_flow;
    }

    I connected_components(vector<I> &component)
    {
        component.assign(this->n, -1);

        I c = 0;
        I at = 0;

        while (at < this->n)
        {
            // do bfs for each vertex and get the component indexed
            queue<I> snow;
            snow.push(at);

            while (!snow.empty())
            {
                auto t = snow.front();
                component[t] = c;
                snow.pop();
                for (auto y : adjl[t])
                {
                    if (component[y] == -1)
                    {
                        component[y] = c;
                        snow.push(y);
                    }
                }
            }
            c++;
            while (component[at] != -1 && at < this->n)
                at++;
        }

        return c;
    }

    void topological_sort()
    {
    }

    // utils
    void print_deg()
    {
        for (I i = 0; i < this->n; i++)
        {
            cout << "[ " << i << ":" << this->ideg[i] << "," << this->odeg[i] << " ], ";
        }
        cout << endl;
    }

    void print_adjl()
    {
        I i = 0;
        cerr << "Out adj\n";
        for (auto x : this->oadjl)
        {
            cout << i << ": ";
            for (auto y : x)
            {
                cout << y << ", ";
            }
            cout << endl;
            i++;
        }

        i = 0;
        cerr << "In adj\n";
        for (auto x : this->iadjl)
        {
            cout << i << ": ";
            for (auto y : x)
            {
                cout << y << ", ";
            }
            cout << endl;
            i++;
        }
    }
};

template <typename I, typename V>
class wdgraph
{
public:
    class dedge
    {
    public:
        I from;
        I to;
        I weight;
        dedge(I from, I to, I weight)
        {
            this->from = from;
            this->to = to;
            this->weight = weight;
        }
    };

    I n;
    vector<vector<I>> adjl;
    vector<I> odeg;
    vector<I> ideg;

    wdgraph(I n)
    {
        this->n = n;
        this->adjl = vector<vector<I>>(n, vector<I>(0));
        this->odeg = vector<I>(n, 0);
        this->ideg = vector<I>(n, 0);
    }

    void add_edge(I x, I y, I weight = 1)
    {
        this->adjl[x].push_back(y);
        this->odeg[x]++;
        this->ideg[y]++;
    }

    void bfs(I x, vector<I> &level, vector<bool> &visted)
    {
        queue<I> snow;

        snow.push(x);
        level[x] = 0;

        while (!snow.empty())
        {
            auto t = snow.front();
            visted[t] = true;
            snow.pop();
            for (auto y : adjl[t])
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

    void dfs(I x, vector<I> &order, vector<I> &parent, vector<bool> &visted)
    {
        stack<I> snow;

        snow.push(x);
        I ct = 0;
        parent[x] = x;

        while (!snow.empty())
        {
            auto t = snow.top();
            visted[t] = true;
            order[t] = ct;
            ct++;
            snow.pop();
            for (auto y : adjl[t])
            {
                if (!visted[y])
                {
                    order[y] = ct;
                    parent[y] = t;
                    ct++;
                    visted[y] = true;
                    snow.push(y);
                }
            }
        }
    }

    void print_deg()
    {
        for (I i = 0; i < this->n; i++)
        {
            cout << i << ":" << this->deg[i] << ", ";
        }
        cout << endl;
    }

    void print_adjl()
    {
        I i = 0;
        for (auto x : this->adjl)
        {
            cout << i << ": ";
            for (auto y : x)
            {
                cout << y << ", ";
            }
            cout << endl;
            i++;
        }
    }

    I connected_components(vector<I> &component)
    {
        component.assign(this->n, -1);

        I c = 0;
        I at = 0;

        while (at < this->n)
        {
            // do bfs for each vertex and get the component indexed
            queue<I> snow;
            snow.push(at);

            while (!snow.empty())
            {
                auto t = snow.front();
                component[t] = c;
                snow.pop();
                for (auto y : adjl[t])
                {
                    if (component[y] == -1)
                    {
                        component[y] = c;
                        snow.push(y);
                    }
                }
            }
            c++;
            while (component[at] != -1 && at < this->n)
                at++;
        }

        return c;
    }

    void dijkstra(I x, vector<I> dist, vector<I> prev)
    {
        dist.assign(this->n, 1000007);
        vector<bool> relaxed(this->n, false);
        dist[x] = 0;
        prev.assign(this->n, 0);
        // index and value
        priority_queue<pair<I, I>> q;
        q.push(make_pair(0, x));

        while (!q.empty())
        {
            auto vw = q.top();
            I v = vw.second;
            I w = (vw.first) * (-1);
            q.pop();
            if (relaxed[v])
            {
                continue;
            }
            else
            {
                relaxed[v] = true;
            }

            for (auto nbr : this->adjl[v])
            {
                if ((!relaxed[nbr]) && dist[v] + w < dist[nbr])
                {
                    dist[nbr] = dist[v] + w;
                    prev[nbr] = v;
                    q.push(make_pair((-1) * dist[nbr]), nbr);
                }
            }
        }
    }
};

#define ll long long

int main()
{
    ll n, m;
    cin >> n >> m;
    graph<ll> g(n);
    while (m--)
    {
        ll u, v;
        cin >> v >> u;
        g.add_edge(u, v);
    }

    vector<ll> ord(n, 0), lev(n, 0), par(n, 0);
    vector<bool> vis(n, false);

    g.print_deg();
    g.print_adjl();

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

    vector<ll> order(n), coloring(n), coloring2(n), partision(n);

    cout << "Is biparted : " << g.is_biparted(partision) << endl;

    pair<ll, ll> pairvs;
    cout << "Is eulerian : " << g.is_eulerian(pairvs) << endl;

    for (ll i = 0; i < n; i++)
    {
        order[i] = i;
    }

    g.ordering_to_coloring(order, coloring);
    for (ll i = 0; i < g.n; i++)
    {
        cout << i << ":" << coloring[i] << endl;
    }

    g.degree_order_coloring(coloring2);
    for (ll i = 0; i < g.n; i++)
    {
        cout << i << ":" << coloring2[i] << endl;
    }

    graph<ll> gc(n);

    g.compliment_graph(gc);

    gc.print_deg();
    gc.print_adjl();

    return 0;
}

/*


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



*/