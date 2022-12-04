#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

namespace tree
{
    template <typename I>
    class tree
    {
        struct hash_pair
        {
            size_t operator()(const pair<I, I> &p) const
            {
                auto hash1 = hash<I>{}(p.first);
                auto hash2 = hash<I>{}(p.second);
                return hash1 ^ hash2;
            }
        };

        I n;
        vector<I> deg;
        vector<vector<I>> adjl;

        I roooted_at = -1;
        vector<I> parent;

        tree(I n)
        {
            this->n = n;
            this->adjl = vector<vector<I>>(n);
            this->parent.clear();
        }

        void add_edge(I v1, I v2)
        {
            this->deg[v1]++;
            this->deg[v2]++;
            this->adjl[v1].push_back(v2);
            this->adjl[v2].push_back(v1);
        }

        friend ostream &operator<<(ostream &os, const tree<I> &t)
        {
            os << "adj list:\n";
            for (I i = 0; i < this->n; i++)
            {
                os << "[" << i << ", " << this->deg[i] << "] : ";
                for (I j = 0; j < this->adjl[i].size(); j++)
                {
                    os << this->adjl[i][j] << ", ";
                }
                os << "\n";
            }

            os << "parent:\n";
            for (I i = 0; i < this->parent.size(); i++)
            {
                os << "[" << i << " : " << this->parent[i] << "], ";
            }
            os << "\n";
        }
    };

    template <typename I>
    void get_parents_when_rooted(I n, I root, const vector<vector<I>>& adjl, vector<I>& parent)
    {
        parent.assign(n, -1);
        parent[root] = root;
        queue<I> Q;
        Q.push(root);
        while (!Q.empty())
        {
            I v = Q.front();
            Q.pop();
            for (I i = 0; i < (I)adjl[v].size(); i++)
            {
                I u = adjl[v][i];
                if (parent[u] == -1)
                {
                    parent[u] = v;
                    Q.push(u);
                }
            }
        }
    }

    template<typename I>
    void get_adjl_using_parent(I n, const vector<I>& parent, vector<vector<I>>& adjl)
    {
        adjl.assign(n,vector<I>());
        for(I i=0;i<n;i++)
        {
            if(parent[i]==i)
            {
                continue;
            }
            adjl[i].push_back(parent[i]);
            adjl[parent[i]].push_back(i);
        }
    }
    
    template<typename I>
    void dfs(I n, I root, const vector<vector<I>>& adjl, vector<I> &intime, vector<I> &outtime)
    {
        vector<bool> visited(n, false);

        stack<I> S;
        I ct = 0;

        S.push(root);
        intime[root] = ct;
        ct++;

        while (!S.empty())
        {
            I v = S.top();
            outtime[v] = ct;
            visited[v] = true;
            ct++;
            S.pop();
            for (I i = 0; i < (I)adjl[v].size(); i++)
            {
                if (!visited[adjl[v][i]])
                {
                    visited[adjl[v][i]] = true;
                    intime[adjl[v][i]] = ct;
                    ct++;
                    S.push(adjl[v][i]);
                }
            }
        }
    }

    template<typename I>
    void bfs(I n, I root, const vector<vector<I>>& adjl, vector<I> &level)
    {
        vector<bool> visited(n, false);

        queue<I> Q;
        I l = 0;

        Q.push(root);
        level[root] = l;

        while (!Q.empty())
        {
            I v = Q.front();
            visited[v] = true;
            Q.pop();
            for (I i = 0; i < (I)adjl[v].size(); i++)
            {
                if (!visited[adjl[v][i]])
                {
                    visited[adjl[v][i]] = true;
                    level[adjl[v][i]] = level[v] + 1;
                    Q.push(adjl[v][i]);
                }
            }
        }
    }

    template<typename I>
    void climb_search(I i, const vector<I>& parent, vector<I> &ct)
    {
        // Central and Bicentral Trees and the Nodes can be identified
        if (parent[i] == i)
        {
            return;
        }

        if (ct[i] + 1 == nodes[i].deg)
        {
            // do the calculations
            ct[i]++;
            ct[parent[i]]++;
            climb_search(parent[i], ct);
        }
    }

    template<typename I>
    void prufer_seq_from_adjl(I n,const vector<I>& deg, const vector<vector<I>>& adjl, vector<I> &pruf)
    {
        vector<I> de(n, 0);
        set<pair<I, I>> S;
        I id = 0;
        for (I i = 0; i < n; i++)
        {
            if (deg[i] == 1)
            {
                S.insert(make_pair(i, adjl[i][0]));
                de[i]++;
            }
        }

        while (!S.empty())
        {
            auto v = *S.begin();
            S.erase(v);

            pruf[id] = v.second;
            id++;
            if (id == n - 2)
            {
                break;
            }
            de[v.second]++;

            if (de[v.second] + 1 == deg[v.second])
            {
                for (I i = 0; i < adjl[v.second].size(); i++)
                {
                    if (de[adjl[v.second][i]] + 1 < deg[adjl[v.second][i]])
                    {
                        S.insert(make_pair(v.second, adjl[v.second][i]));
                        de[v.second]++;
                    }
                }
            }
        }
    }

    // FIXME : complete the code
    template<typename I>
    void tree_from_prufer_seq(I n, const vector<I>& prufer_seq, tree<I>& tree)
    {

    }

    template<typename I>
    void recursive_eulerian_sequence(I root, const vector<vector<I>>& adjl, vector<bool> &vis, vector<I> &eseq)
    {
        vis[root] = true;
        eseq.push_back(root);
        for (auto x : adjl[root])
        {
            if (!vis[x])
            {
                recursive_eulerian_sequence(x, vis, eseq);
                eseq.push_back(root);
            }
        }
    }

    template<typename I>
    void eulerian_sequence(I n, I root, const vector<vector<I>>& adjl, vector<I> &eseq)
    {
        eseq.clear();

        stack<I> S;
        vector<bool> vis(n, false);
        S.push(root);

        while (!S.empty())
        {
            I u = S.top();
            S.pop();
            if (vis[u])
            {
                eseq.push_back(u);
                continue;
            }

            vis[u] = true;
            eseq.push_back(u);

            for (auto x : adjl[u])
            {
                if (!vis[x])
                {
                    S.push(u);
                    S.push(x);
                }
            }
        }
    }

    // FIXME :: complete the code
    template<typename I>
    void lca_eulerian_sequence(I n, I root, const vector<vector<I>>& adjl, vector<I> &eseq, vector<I> &heightseq, vector<I> &fstoccr)
    {
        eseq.clear();

        stack<I> S;
        vector<bool> vis(n, false);
        S.push(root);
        vector<I> height(n);
        height[root] = 0;
        while (!S.empty())
        {
            I u = S.top();
            S.pop();
            if (vis[u])
            {
                eseq.push_back(u);
                continue;
            }

            vis[u] = true;
            eseq.push_back(u);

            for (auto x : adjl[u])
            {
                if (!vis[x])
                {
                    height[x] = height[u]+(I)1;
                    S.push(u);
                    S.push(x);
                }
            }
        }

        fstoccr.assign(n, -1);
        heightseq.resize(eseq.size());
        for (I i = 0; i < (I)eseq.size(); i++)
        {
            heightseq[i] = height[eseq[i]];
            if (fstoccr[eseq[i]] == -1)
            {
                fstoccr[eseq[i]] = i;
            }
        }
    }

    // Binary Lifting
    // O(Vlog(V))
    template<typename I>
    void binary_lifting(I n,I root, const vector<vector<I>>& adjl, const vector<I>& parents, vector<vector<I>> &up, vector<I> &tin, vector<I> &tout)
    {
        I itimer = 0;
        stack<I> Q;
        Q.push(root);
        tin[root] = itimer;
        itimer++;

        I k = 2, tn = n;
        while (n > 0)
        {
            k++;
            n >>= 1;
        }

        up.assign(n, vector<I>(k, -1));
        tin.assign(n, -1);
        tout.assign(n, -1);
        vector<bool> done(n, false);

        while (!Q.empty())
        {
            I u = Q.top();
            Q.pop();
            if (done[u])
            {
                tout[u] = itimer;
                itimer++;
                continue;
            }
            done[u] = true;

            for (auto v : adjl[u])
            {
                if (v != parent[u])
                {
                    I i = 0;
                    up[v][i] = u;
                    while (up[v][i] != -1)
                    {
                        up[v][i + 1] = up[up[v][i]][i];
                        i++;
                    }
                    Q.push(u);
                    Q.push(v);

                    tin[v] = itimer;
                    itimer++;
                }
            }
        }
    }

    // O(1)
    template<typename I>
    bool is_ancestor(I anc_u, I u, const vector<I> &tin, const vector<I> &tout)
    {
        return tin[anc_u] <= tin[u] && tout[anc_u] >= tout[anc_u];
    }

    // O(log(V))
    template<typename I>
    bool lca_binary_lifting(I u, I v, vector<vector<I>> &up, vector<I> &tin, vector<I> &tout)
    {
        for (I i = up[0].size() - 1; i >= 0; i--)
        {
            if (!is_ancestor(u, v, tin, tout))
            {
                u = up[u][i];
            }
        }

        return up[u][0];
    }
    // Binary Lifting

}