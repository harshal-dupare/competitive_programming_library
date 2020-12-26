#pragma once
#include <bits/stdc++.h>

using namespace std;


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
    vector<vector<I>> iadjl;
    vector<vector<I>> oadjl;
    vector<I> odeg;
    vector<I> ideg;
    V inf = 1e+12;
    V null_value = 0;
    vector<vector<V>> adjm;
    unordered_map<I, I> edge_weight;

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
        this->edge_weight[x * n + y] = w;
    }

    void set_adjWM()
    {
        this->adjm.assign(n, vector<V>(n, this->inf));
        for (I i = 0; i < n; i++)
        {
            adjm[i][i] = this->null_value;
            for (auto j : this->oadjl[i])
            {
                adjm[i][j] = edge_weight[i * n + j];
            }
        }
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

    I underlining_connected_components(vector<I> &component)
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
                for (auto y : oadjl[t])
                {
                    if (component[y] == -1)
                    {
                        component[y] = c;
                        snow.push(y);
                    }
                }

                for (auto y : iadjl[t])
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

    // O(Elog(E)+V)
    void dijkstra(I x, vector<V> &dist, vector<I> &prev)
    {
        vector<bool> relaxed(this->n, false);
        dist[x] = 0;
        prev[x] = x;

        set<pair<V, I>> q;
        q.insert(make_pair((V)0, x));

        while (!q.empty())
        {
            auto vw = q.begin();
            I v = vw->second;
            V w = vw->first;
            q.erase(vw);
            relaxed[v] = true;

            for (auto nbr : this->oadjl[v])
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
        for (I i = 0; i < oadjl[0].size(); i++)
        {
            V w = this->edge_weight[oadjl[0][i]];
            if (w < tweight)
            {
                fp = oadjl[0][i];
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
            for (I i = 0; i < oadjl[tpi].size(); i++)
            {
                if (done[oadjl[tpi][i]])
                {
                    continue;
                }
                // ok(oadjl[tpi][i])

                V w = this->edge_weight[tpi * n + oadjl[tpi][i]];
                if (lowedge[oadjl[tpi][i]] > w)
                {
                    auto itr = pq.find(make_pair(lowedge[oadjl[tpi][i]], oadjl[tpi][i]));
                    if (itr != pq.end())
                    {
                        pq.erase(itr);
                    }
                    pq.insert(make_pair(w, oadjl[tpi][i]));
                    lowedge[oadjl[tpi][i]] = w;
                    parent[oadjl[tpi][i]] = tpi;
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

            for (I i = 0; i < oadjl[id].size(); i++)
            {
                if (done[oadjl[id][i]])
                {
                    continue;
                }
                // ok(id);
                // ok(oadjl[id][i]);
                V w = this->edge_weight[id * n + oadjl[id][i]];
                // ok(w);
                if (lowedge[oadjl[id][i]] > w)
                {
                    auto itr = pq.find(make_pair(lowedge[oadjl[id][i]], oadjl[id][i]));
                    if (itr != pq.end())
                    {
                        pq.erase(itr);
                    }
                    pq.insert(make_pair(w, oadjl[id][i]));
                    lowedge[oadjl[id][i]] = w;
                    parent[oadjl[id][i]] = id;
                }
            }

            // oks(done);
            // okp(pq);
            // ok(tweight);
        }

        return tweight;
    }

    // O(V^3)
    void floyd_warshall(vector<vector<I>> &d)
    {
        d = this->adjm;
        vector<vector<I>> dd = d;
        for (I k = 0; k < n; k++)
        {
            for (I i = 0; i < n; i++)
            {
                for (I j = 0; j < n; j++)
                {
                    dd[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
            d = dd;
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
            for (auto j : oadjl[i])
            {
                epq.push({(-1) * edge_weight[i * n + j], i * n + j});
            }
        }

        I idx = 0;
        while (!epq.empty())
        {
            pair<V, I> itr = epq.top();
            I a = itr.second / n;
            I b = itr.second % n;
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
                elist[idx].first = a;
                elist[idx].second = b;
                idx++;
            }
            epq.pop();
        }

        return tweight;
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
        cerr << "\nOut adj\n";
        for (auto x : this->oadjl)
        {
            cout << i << ": ";
            for (auto y : x)
            {
                cout << "[" << y << "," << edge_weight[i * n + y] << "], ";
            }
            cout << endl;
            i++;
        }

        i = 0;
        cerr << "\nIn adj\n";
        for (auto x : this->iadjl)
        {
            cout << i << ": ";
            for (auto y : x)
            {
                cout << "[" << y << "," << edge_weight[y * n + i] << "], ";
            }
            cout << endl;
            i++;
        }
    }
};

