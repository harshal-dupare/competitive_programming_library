#include <bits/stdc++.h>
#include "../utils/timer.h"
#include "../utils/debugger.h"

using namespace std;

template <typename I>
class suffix_tree
{
public:
    struct node
    {
        vector<I> next;
        I parent = -1;
        string str;

        node()
        {
            this->next = vector<I>(27, -1);
        }

        node(string _s)
        {
            this->str = _s;
            this->next = vector<I>(27, -1);
        }

        node(string _s, I p)
        {
            this->str = _s;
            this->parent = p;
            this->next = vector<I>(27, -1);
        }

        node(string &_s, I i, I p)
        {
            this->str = _s.substr(i);
            this->parent = p;
            this->next = vector<I>(27, -1);
        }

        friend ostream &operator<<(ostream &os, const node &n)
        {
            os << "[ " << n.str << " , " << n.parent << "] : {";
            for (auto x : n.next)
            {
                if (x != -1)
                {
                    os << x << ", ";
                }
            }
            os << "}\n";
            return os;
        }
    };

    vector<node> nodes;
    char min_char = 'a';
    char max_char = 'z';
    I char_size = max_char - min_char + 1;

    suffix_tree(char _min_char = 'a', char _max_char = 'z')
    {
        this->min_char = _min_char;
        this->max_char = _max_char;
        this->char_size = _max_char - _min_char + 1;
    }

    void add(string &s)
    {
        s = string("$") + s;
        if (nodes.size() == 0)
        {
            nodes.push_back(node(s));
            return;
        }

        I id = 0;
        I i = 0;
        I j = 0;
        I n = s.size();

        while (i < n)
        {
            if (s[i] == nodes[id].str[j])
            {
                i++;
                j++;
                if (i >= n)
                {
                    break;
                }

                if (j < nodes[id].str.size())
                {
                    continue;
                }

                if (nodes[id].next[s[i] - min_char] == -1)
                {
                    nodes[id].next[s[i] - min_char] = nodes.size();
                    string ss = s.substr(i);
                    nodes.push_back(node(ss));
                    return;
                }
                else
                {
                    id = nodes[id].next[s[i] - min_char];
                    j = 0;
                }
            }
            else
            {
                string ss = nodes[id].str.substr(j);
                nodes.push_back(node(ss));
                nodes[nodes.size() - 1].next = nodes[id].next;

                nodes[id].next.assign(char_size, -1);
                nodes[id].next[nodes[id].str[j] - min_char] = nodes.size() - 1;

                nodes[id].str = nodes[id].str.substr(0, j);

                ss = s.substr(i);
                nodes.push_back(node(ss));
                nodes[id].next[s[i] - min_char] = nodes.size() - 1;
                return;
            }
        }
    }

    void construct(vector<string> const &vs)
    {
        for (auto s : vs)
        {
            this->add(s);
        }
    }

    void sorted_print(I id, string &s)
    {
    }

    void print()
    {
        I i = 0;
        for (I i = 0; i < this->nodes.size(); i++)
        {
            cerr << i << " : " << nodes[i];
        }
        cerr << "\n";
    }
};

typedef long long ll;

int main()
{
    suffix_tree<ll> sft;

    ll n;
    cin >> n;
    vector<string> vs(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> vs[i];
    }

    sft.construct(vs);
    sft.print();

    return 0;
}