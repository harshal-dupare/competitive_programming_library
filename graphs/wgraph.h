#pragma once
#include <bits/stdc++.h>
#include "../utils/debugger.h"

template <typename I, typename V>
class wgraph
{
public:
    class edge
    {
    public:
        I v1;
        I v2;
        V weight;
        edge(I v1, I v2, V weight)
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
    V inf = 1e+12;
    V null_value = 0;
    vector<vector<I>> adjm, min_distance;
    unordered_map<I, I> edge_weight;

    wgraph(I n)
    {
        this->n = n;
        this->adjl = vector<vector<I>>(n, vector<I>(0));
        this->deg = vector<I>(n, 0);
    }

    void add_edge(I x, I y, V w)
    {
        this->adjl[x].push_back(y);
        this->adjl[y].push_back(x);
        this->deg[x]++;
        this->deg[y]++;
        this->edge_weight[x * n + y] = w;
        this->edge_weight[y * n + x] = w;
    }

    void set_adjWM()
    {
        this->adjm.assign(n, vector<V>(n, this->inf));
        for (I i = 0; i < n; i++)
        {
            adjm[i][i] = this->null_value;
            for (auto j : this->adjl[i])
            {
                adjm[i][j] = edge_weight[i * n + j];
            }
        }
    }

    void add_vertex(vector<pair<I, V>> &adj)
    {
        this->adjl.push_back(vector<I>(0));
        for (auto x : adj)
        {
            this->add_edge(n, x.first, x.second);
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

    // O(Elog(E)+V)
    void dijkstra(I x, vector<V> &dist, vector<I> &prev)
    {
        vector<bool> relaxed(this->n, false);
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

            for (auto nbr : this->adjl[v])
            {
                if (relaxed[nbr])
                {
                    continue;
                }

                V egw = edge_weight[v * n + nbr];
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
    V prims(vector<I> &parent)
    {
        set<pair<V, I>> pq;
        I fp;
        V tweight = this->inf;
        for (I i = 0; i < adjl[0].size(); i++)
        {
            V w = this->edge_weight[adjl[0][i]];
            if (w < tweight)
            {
                fp = adjl[0][i];
                tweight = w;
            }
        }

        vector<bool> done(n);
        vector<V> lowedge(n, this->inf);
        parent[fp] = 0;
        parent[0] = 0;
        lowedge[0] = 0;
        done[0] = true;
        lowedge[fp] = tweight;
        done[fp] = true;

        // relax 0
        I arr[2] = {0, fp};
        for (I tpi : arr)
        {
            for (I i = 0; i < adjl[tpi].size(); i++)
            {
                if (done[adjl[tpi][i]])
                {
                    continue;
                }
                // ok(adjl[tpi][i])

                V w = this->edge_weight[tpi * n + adjl[tpi][i]];
                if (lowedge[adjl[tpi][i]] > w)
                {
                    auto itr = pq.find(make_pair(lowedge[adjl[tpi][i]], adjl[tpi][i]));
                    if (itr != pq.end())
                    {
                        pq.erase(itr);
                    }
                    pq.insert(make_pair(w, adjl[tpi][i]));
                    lowedge[adjl[tpi][i]] = w;
                    parent[adjl[tpi][i]] = tpi;
                }
            }
        }

        while (!pq.empty())
        {
            pair<V, I> tp = *pq.begin();
            tweight += tp.first;
            I id = tp.second;
            done[id] = true;
            pq.erase(tp);

            for (I i = 0; i < adjl[id].size(); i++)
            {
                if (done[adjl[id][i]])
                {
                    continue;
                }
                // ok(id);
                // ok(adjl[id][i]);
                V w = this->edge_weight[id * n + adjl[id][i]];
                // ok(w);
                if (lowedge[adjl[id][i]] > w)
                {
                    auto itr = pq.find(make_pair(lowedge[adjl[id][i]], adjl[id][i]));
                    if (itr != pq.end())
                    {
                        pq.erase(itr);
                    }
                    pq.insert(make_pair(w, adjl[id][i]));
                    lowedge[adjl[id][i]] = w;
                    parent[adjl[id][i]] = id;
                }
            }

            // oks(done);
            // okp(pq);
            // ok(tweight);
        }

        return tweight;
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

    // O(E*log(E)+V)
    V krushal(vector<pair<I, I>> &elist)
    {
        priority_queue<pair<V, I>> epq;
        vector<I> dsu(n), sz(n);
        V tweight = this->null_value;

        for (I i = 0; i < n; i++)
        {
            dsu[i] = i;
            sz[i] = 1;
            for (auto j : adjl[i])
            {
                if (j > i)
                    epq.push({(-1) * edge_weight[i * n + j], i * n + j});
            }
        }

        I idx = 0;
        while ((idx < n-1) && !epq.empty())
        {
            pair<V, I> itr = epq.top();
            I a = itr.second / n;
            I b = itr.second % n;
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

                tweight -= itr.first;
                elist[idx].first = a;
                elist[idx].second = b;
                idx++;
            }
            epq.pop();
        }

        return tweight;
    }

    // O(E*W+V)
    V krushal_wrange(vector<pair<I, I>> &elist, V W_max)
    {
        vector<vector<pair<I, I>>> weight_buckets(W_max + 1);
        vector<I> dsu(n), sz(n);
        V tweight = this->null_value;

        for (I i = 0; i < n; i++)
        {
            dsu[i] = i;
            sz[i] = 1;
            for (auto j : adjl[i])
            {
                if (j > i)
                {
                    weight_buckets[edge_weight[i * n + j]].push_back({i,j});
                }
            }
        }
        // weight_buckets.shrink_to_fit();
        
        I idx = 0;
        I W = 0, id = 0;
        I weight;
        pair<I, I> itr;
        while (idx < n-1)
        {
            while(W <= W_max)
            {
                if(id>=weight_buckets[W].size())
                {
                    W++;
                    id=0;
                }
                else
                {
                    weight=W;
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
                elist[idx].first = a;
                elist[idx].second = b;
                idx++;
            }
        }

        return tweight;
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
            cerr << i << ": ";
            for (auto y : x)
            {
                cerr << "[" << y << ", " << edge_weight[i * n + y] << "], ";
            }
            cerr << endl;
            i++;
        }
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

    I dinics_algorithm()
    {
        I max_flow;

        return max_flow;
    }
};

