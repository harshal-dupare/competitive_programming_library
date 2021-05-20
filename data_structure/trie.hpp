
template <typename I>
class trie
{
public:
    char top_char = '$';
    char start_char = 'a';
    char end_char = 'z';
    I char_count = 26;
    I word_ct = 0;

    struct node
    {
        bool word_end = false;
        char c;
        I parent;
        vector<I> next;

        node(char c = '$', I par = -1, I c_count = 26)
        {
            this->c = c;
            this->parent = par;
            this->next = vector<I>(c_count, -1);
        }

        friend ostream &operator<<(ostream &os, const node &n)
        {
            os << "[" << n.c << ',' << n.parent << "," << n.word_end << "] : {";
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

    // start and end both inclusive
    trie(char start_c = 'a', char end_c = 'z')
    {
        this->start_char = start_c;
        this->end_char = end_c;
        this->char_count = end_c - start_c + 1;
        this->nodes = vector<node>(1, node(this->top_char, -1, this->char_count));
        this->word_ct = 0;
    }

    void insert(string const &s)
    {
        I node_id = 0;
        for (char c : s)
        {
            I c_id = c - this->start_char;

            if (this->nodes[node_id].next[c_id] == -1)
            {
                this->nodes[node_id].next[c_id] = this->nodes.size();
                this->nodes.push_back(node(c, node_id, this->char_count));
            }
            node_id = this->nodes[node_id].next[c_id];
        }
        this->nodes[node_id].word_end = true;
        word_ct++;
    }

    void construct(vector<string> const &vs)
    {
        for (auto s : vs)
        {
            this->insert(s);
        }
    }

    void sorted_print(I id, string &s)
    {
        if (id != 0)
            s += this->nodes[id].c;

        if (this->nodes[id].word_end)
        {
            cerr << s << endl;
        }

        for (auto x : this->nodes[id].next)
        {
            if (x != -1)
                sorted_print(x, s);
        }

        s.pop_back();
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
