#include <bits/stdc++.h>
using namespace std;

#define ok(vari) cerr << #vari << " = " << (vari) << "\n";
#define oka(a, L, R)              \
    cerr << #a << " : \n[ ";      \
    for (int64 i = L; i < R; i++) \
        cerr << a[i] << " ";      \
    cerr << "]\n";
#define oks(s)               \
    cerr << #s << " : \n{ "; \
    for (auto x : s)         \
        cerr << x << " ";    \
    cerr << "}\n";
#define okp(ps)                                         \
    cerr << #ps << " : \n";                             \
    for (auto x : ps)                                   \
        cerr << (x.first) << ":" << (x.second) << ", "; \
    cerr << "\n";
#define okvv(vv)              \
    cerr << #vv << " : \n";   \
    for (auto x : vv)         \
    {                         \
        cerr << "[ ";         \
        for (auto y : x)      \
            cerr << y << " "; \
        cerr << "]\n";        \
    }

#define reply(a) cout << a << "\n";
#define replyf(a, i) cout << fixed << setprecision(i) << a << "\n";

typedef long long ll;

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
        if (this->parent[i] == i)
        {
            return;
        }

        if (ct[i] + 1 == this->nodes[i].deg)
        {
            cerr << i << endl;
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

            pruf[id]=v.second;
            id++;
            if(id==n-2)
            {
                break;
            }
            de[v.second]++;

            if (de[v.second] + 1 == this->nodes[v.second].deg)
            {
                for (I i = 0; i < this->nodes[v.second].adjl.size(); i++)
                {
                    if(de[this->nodes[v.second].adjl[i]] + 1 < this->nodes[this->nodes[v.second].adjl[i]].deg)
                    {
                        S.insert(make_pair(v.second,this->nodes[v.second].adjl[i]));
                        de[v.second]++;
                    }
                }
            }
        }

    }

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

int main()
{
    ll n, m;
    cin >> n >> m;
    tree<ll, ll> tr(n);

    for (ll i = 0; i < m; i++)
    {
        ll x, y, w;
        cin >> x >> y >> w;
        tr.add_edge(x, y, w);
    }

    // tr.print();
    tr.root_at(1);
    tr.print();

    vector<ll> ct(n, 0);

    for (ll i = 0; i < n; i++)
    {
        if (tr.nodes[i].deg == 1)
        {
            tr.climb_search(i, ct);
        }
    }
    vector<ll> level(n), intime(n), outtime(n), pruf(n-2);

    tr.bfs(1, level);
    tr.dfs(1, intime, outtime);
    tr.prufer_seq(pruf);

    oks(level);
    oks(intime);
    oks(outtime);
    oks(pruf)

        return 0;
}

/*

6 5
0 1 1
0 2 2
1 3 5
2 4 -1
2 5 8
adj list:
[0, 2] : 1, 2,
[1, 2] : 0, 3,
[2, 3] : 0, 4, 5,
[3, 1] : 1,
[4, 1] : 2,
[5, 1] : 2,
parent:
[0 : 1], [1 : 1], [2 : 0], [3 : 1], [4 : 2], [5 : 2],
edge weight:
[5, 2: 8], [2, 5: 8], [4, 2: -1], [2, 4: -1], [3, 1: 5], [1, 3: 5], [2, 0: 2], [0, 2: 2], [1, 0: 1], [0, 1: 1],
3
4
5
2
0
S :
3:1, 4:2, 5:2,
S :
1:0, 4:2, 5:2,
S :
0:2, 4:2, 5:2,
S :
4:2, 5:2,
level :
{ 1 0 2 1 3 3 }
intime :
{ 2 0 6 3 8 9 }
outtime :
{ 5 1 7 4 11 10 }
pruf :
{ 1 0 2 2 }

*/