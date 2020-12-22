#include <bits/stdc++.h>

using namespace std;

class trie
{
public:
    struct Vertex
    {
        bool leaf = false;
        const int K = 26;
        vector<int> next;
        int p;
        char ch;

        Vertex(int p = -1, char ch = '$')
        {
            this->next = vector<int>(this->K);
            this->p = p;
            this->ch = ch;
        }
    };
    
    const int K = 26;
    vector<Vertex> t;

    trie()
    {
        this->t = vector<Vertex>(1);
    }

    void add_string(string const &s)
    {
        int v = 0;
        for (char ch : s)
        {
            int c = ch - 'a';
            if (this->t[v].next[c] == -1)
            {
                this->t[v].next[c] = this->t.size();
                this->t.emplace_back(v, ch);
            }
            v = this->t[v].next[c];
        }
        t[v].leaf = true;
    }
};

int main()
{
    return 0;
}