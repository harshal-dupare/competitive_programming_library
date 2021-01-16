#pragma once
#include <bits/stdc++.h>

using namespace std;

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
    I n = 0;
    I edge_count = 0;
    vector<vector<I>> adjl;
    vector<I> deg;
    I mytimer = 0;

    // secondary data
    I inf = 1e+12;
    I null_value = 0;
    vector<vector<I>> adjm, min_distance;

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

    void dfs_rec(I x, vector<I> &intime, vector<I> &otime, vector<I> &parent, vector<bool> &visited)
    {
        intime[x] = mytimer++;
        visited[x] = true;
        for (auto y : this->adjl[x])
        {
            if (!visited[y])
            {
                parent[y]=x;
                dfs_rec(y, intime, otime, parent, visited);
            }
        }
        otime[x] = mytimer++;
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
        // Braces and Rigidity in n x m grid if the graph with edges as braces at b[r][c] is biparted and connected
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

    // need to complete section

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

    void characterstics_polynomial()
    {
    }

    void eignevalues()
    {
        // adj matrix
        // all are real if symmetric matrix, AM = GM ,
        // sum of all eigenvalues is 0 as all diagonal is 0
        // if graph is connected then Multiplicity of largest eigenvalue is 1
        // graph is biparted iff r is largest eigenvalue and -r is also the eigenvalue
        // value of largest eigenvalue is between avg degree and largets degree
    }

    I tuckers_algorithm()
    {
        // new idea is to pair all the edges on a vertex into (in, out) pair
    }

    // O(V^3)
    void floyd_warshall()
    {
        this->min_distance = this->adjm;
        vector<vector<I>> dd = this->min_distance;
        for (I k = 0; k < n; k++)
        {
            for (I i = 0; i < n; i++)
            {
                if (this->min_distance[i][k] == this->inf)
                {
                    continue;
                }

                for (I j = 0; j < n; j++)
                {
                    dd[i][j] = min(this->min_distance[i][j], this->min_distance[i][k] + this->min_distance[k][j]);
                }
            }
            this->min_distance = dd;
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
            cerr << i << ":" << this->deg[i] << ", ";
        }
        cerr << endl;
        cerr << endl;
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

        cerr << endl;
    }
};
