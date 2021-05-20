
// this is doc info
template <typename I>
class union_find
{
public:
    vector<I> parent;
    vector<I> size;
    I n;

    union_find(I n)
    {
        this->n = n;
        this->parent = vector<I>(n, -1); // no element in the sets hence all empty as -1
        this->size = vector<I>(n, 0);    // no element in the sets hence all empty as -
    }

    // makes new set as {x} if x is already used
    void make_set(I x)
    {
        this->parent[x] = x;
        this->size[x] = 1;
    }

    void union_sets(I x, I y)
    {
        I sx = this->find_set(x);
        I sy = this->find_set(y);
        if (sx != sy)
        {
            // sx must have the larger size
            if (this->size[sx] < this->size[sy])
                swap(sx, sy);
            this->parent[sy] = sx;
            this->size[sy] += this->size[sx];
        }
    }

    /*
    this is large
    multiline doc
    */
    I find_set(I x)
    {
        if (this->parent[x] == -1)
            return -1;

        while (x != this->parent[x])
        {
            x = this->parent[this->parent[x]];
        }

        return x;
    }

    // prints the sets with elements and sizes
    void print()
    {
        for (int i = 0; i < this->n; i++)
        {
            cout << i << ":("<<this->find_set(i) <<",";
            if(this->find_set(i)==-1)
            {
                cout<<"0), ";
            }
            else
            {
                cout<<this->size[this->find_set(i)]<<"), ";
            }
            
        }
        cout << endl;
    }
};
