#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
// FIXME compile 
// FIXME correctness
// FIXME restructure classes vs without classes
using namespace std;

template <typename I, typename D>
class tree
{
public:
    struct edge
    {
        I v1;
        I v2;
        I w;
        edge();
        edge(I v1, I v2, I w = 0)
        {
            this->v1 = v1;
            this->v2 = v2;
            this->w = w;
        }

        bool operator<(const edge &o)
        {
            if (this->v1 != o.v1)
            {
                return this->v1 < o.v1;
            }
            else
            {
                return this->v2 < o.v2;
            }
        }
    };

    struct node
    {
        I idx;
        I deg;
        D data;
        vector<I> adjl;
        node();
        node(I idx, D data)
        {
            this->deg = 0;
            this->idx = idx;
            this->data = data;
        }
    };

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
    I roooted_at = -1;
    vector<node> nodes;
    vector<edge> edges;
    unordered_map<pair<I, I>, I, hash_pair> edge_weight;
    vector<I> parent;

    tree(I n)
    {
        this->n = n;
        this->nodes = vector<node>(n, node(0, 0));
        this->parent.clear();
    }

    void add_edge(I v1, I v2, I w = 0)
    {
        this->nodes[v1].deg++;
        this->nodes[v2].deg++;
        this->nodes[v1].adjl.push_back(v2);
        this->nodes[v2].adjl.push_back(v1);

        // edge list
        this->edges.push_back(edge(v1, v2, w));
        this->edges.push_back(edge(v2, v1, w));

        // edge weight map
        this->edge_weight[make_pair(v1, v2)] = w;
        this->edge_weight[make_pair(v2, v1)] = w;
    }

    void root_at(I root)
    {
        this->roooted_at = root;
        this->parent.assign(this->n, -1);
        this->parent[root] = root;
        queue<I> Q;
        Q.push(root);
        while (!Q.empty())
        {
            I v = Q.front();
            Q.pop();
            for (I i = 0; i < this->nodes[v].adjl.size(); i++)
            {
                I u = this->nodes[v].adjl[i];
                if (this->parent[u] == -1)
                {
                    this->parent[u] = v;
                    Q.push(u);
                }
            }
        }
    }

    void dfs(I root, vector<I> &intime, vector<I> &outtime)
    {
        vector<bool> visited(this->n, false);

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
            for (I i = 0; i < this->nodes[v].adjl.size(); i++)
            {
                if (!visited[this->nodes[v].adjl[i]])
                {
                    visited[this->nodes[v].adjl[i]] = true;
                    intime[this->nodes[v].adjl[i]] = ct;
                    ct++;
                    S.push(this->nodes[v].adjl[i]);
                }
            }
        }
    }

    void bfs(I root, vector<I> &level)
    {
        vector<bool> visited(this->n, false);

        queue<I> Q;
        I l = 0;

        Q.push(root);
        level[root] = l;

        while (!Q.empty())
        {
            I v = Q.front();
            visited[v] = true;
            Q.pop();
            for (I i = 0; i < this->nodes[v].adjl.size(); i++)
            {
                if (!visited[this->nodes[v].adjl[i]])
                {
                    visited[this->nodes[v].adjl[i]] = true;
                    level[this->nodes[v].adjl[i]] = level[v] + 1;
                    Q.push(this->nodes[v].adjl[i]);
                }
            }
        }
    }

    void climb_search(I i, vector<I> &ct)
    {
        // Central and Bicentral Trees and the nodes can be identified
        if (this->parent[i] == i)
        {
            return;
        }

        if (ct[i] + 1 == this->nodes[i].deg)
        {
            // do the calculations
            ct[i]++;
            ct[this->parent[i]]++;
            climb_search(this->parent[i], ct);
        }
    }

    void prufer_seq(vector<I> &pruf)
    {
        vector<I> de(n, 0);
        set<pair<I, I>> S;
        I id = 0;
        for (I i = 0; i < n; i++)
        {
            if (this->nodes[i].deg == 1)
            {
                S.insert(make_pair(i, this->nodes[i].adjl[0]));
                de[i]++;
            }
        }

        while (!S.empty())
        {
            okp(S);
            auto v = *S.begin();
            S.erase(v);

            pruf[id] = v.second;
            id++;
            if (id == n - 2)
            {
                break;
            }
            de[v.second]++;

            if (de[v.second] + 1 == this->nodes[v.second].deg)
            {
                for (I i = 0; i < this->nodes[v.second].adjl.size(); i++)
                {
                    if (de[this->nodes[v.second].adjl[i]] + 1 < this->nodes[this->nodes[v.second].adjl[i]].deg)
                    {
                        S.insert(make_pair(v.second, this->nodes[v.second].adjl[i]));
                        de[v.second]++;
                    }
                }
            }
        }
    }

    void rec_euler_seq(I root, vector<bool> &vis, vector<I> &eseq)
    {
        vis[root] = true;
        eseq.push_back(root);
        for (auto x : nodes[root].adjl)
        {
            if (!vis[x])
            {
                rec_euler_seq(x, vis, eseq);
                eseq.push_back(root);
            }
        }
    }

    void euler_seq(I root, vector<I> &eseq)
    {
        eseq.clear();

        stack<I> S;
        vector<bool> vis(this->n, false);
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

            for (auto x : this->nodes[u].adjl)
            {
                if (!vis[x])
                {
                    S.push(u);
                    S.push(x);
                }
            }
        }
    }

    void lca_euler_seq(I root, vector<I> &eseq, vector<I> &heightseq, vector<I> &fstoccr)
    {
        eseq.clear();

        stack<I> S;
        vector<bool> vis(this->n, false);
        S.push(root);
        vector<I> height(this->n);
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

            for (auto x : this->nodes[u].adjl)
            {
                if (!vis[x])
                {
                    height[x] = 1 + height[u];
                    S.push(u);
                    S.push(x);
                }
            }
        }

        eseq.shrink_to_fit();
        fstoccr.assign(this->n, -1);
        heightseq.resize(eseq.size());
        for (I i = 0; i < eseq.size(); i++)
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
    void binary_lifting(vector<vector<I>> &up, vector<I> &tin, vector<I> &tout,I root=-1)
    {
        if(root!=-1&&this->roooted_at!=root)
        {
            this->root_at(root);
        }
        I itimer = 0;
        stack<I> Q;
        Q.push(this->roooted_at);
        tin[this->roooted_at]=itimer;
        itimer++;

        I k=2,tn=this->n;
        while(n>0)
        {
            k++;
            n>>=1;
        }

        up.assign(this->n,vector<I>(k,-1));
        tin.assign(this->n,-1);
        tout.assign(this->n,-1);
        vector<bool> done(n,false);

        while(!Q.empty())
        {
            I u = Q.top();
            Q.pop();
            if(done[u])
            {
                tout[u]=itimer;
                itimer++;
                continue;
            }
            done[u]=true;

            for(auto v: this->nodes[u].adjl)
            {
                if(v!=this->parent[u])
                {
                    I i=0;
                    up[v][i]=u;
                    while(up[v][i]!=-1)
                    {
                        up[v][i+1] = up[up[v][i]][i];
                        i++;
                    }
                    Q.push(u);
                    Q.push(v);

                    tin[v]=itimer;
                    itimer++;
                }
            }
        }
    }

    // O(1)
    bool is_ancestor(I anc_u, I u,const vector<I> &tin, const vector<I> &tout)
    {
        return tin[anc_u]<=tin[u] && tout[anc_u]>=tout[anc_u];
    }

    // O(log(V))
    bool lca_binary_lifting(I u,I v,vector<vector<I>> &up, vector<I> &tin, vector<I> &tout)
    {
        for(I i=up[0].size()-1;i>=0;i--)
        {
            if(!is_ancestor(u,v,tin,tout))
            {
                u = up[u][i];
            }
        }

        return up[u][0];
    }
    // Binary Lifting

    void print()
    {
        cerr << "adj list:\n";
        for (I i = 0; i < this->n; i++)
        {
            cerr << "[" << i << ", " << this->nodes[i].deg << "] : ";
            for (I j = 0; j < this->nodes[i].adjl.size(); j++)
            {
                cerr << this->nodes[i].adjl[j] << ", ";
            }
            cerr << endl;
        }

        cerr << "parent:\n";
        for (I i = 0; i < this->parent.size(); i++)
        {
            cerr << "[" << i << " : " << this->parent[i] << "], ";
        }
        cerr << endl;

        cerr << "edge weight:\n";
        for (auto x : this->edge_weight)
        {
            cerr << "[" << x.first.first << ", " << x.first.second << ": " << x.second << "], ";
        }
        cerr << endl;
    }

};

