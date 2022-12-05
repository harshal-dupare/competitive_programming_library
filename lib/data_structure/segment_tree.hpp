#include <bits/stdc++.h>
using namespace std;

template <typename I>
class segment_tree
{
public:
    // only tree is one indexed to allow for better access
    vector<I> tree;
    I null_value = 0;
    I n;

    segment_tree();
    segment_tree(I n)
    {
        this->n = n;
        this->tree.assign(2 * n + 1, null_value);
    }

    inline I f(I a, I b)
    {
        return a + b;
    }

    void compute(vector<I> &a)
    {
        I k = 1;
        while (k < n)
        {
            k <<= 1;
        }

        for (I i = 0; i < this->n; i++)
        {
            this->tree[k] = a[i];
            k++;
            if (k >= 2 * this->n)
            {
                k = this->n;
            }
        }

        for (I i = this->n - 1; i > 0; i--)
        {
            I lc = i << 1;
            I rc = lc + 1;
            if (rc >= 2 * this->n)
                rc = 0;
            tree[i] = this->f(tree[lc], tree[rc]);
        }
    }

    void update(I i, I val)
    {
        i += this->n + 1;
        this->tree[i] = val;
        i >>= 1;
        while (i > 0)
        {
            I lc = i << 1;
            I rc = lc + 1;
            if (rc > 2 * this->n)
                rc = 0;
            this->tree[i] = this->f(this->tree[rc], this->tree[lc]);
            i >>= 1;
        }
    }

    // give zero indexed
    I get(I i, I l, I r, I szl, I szr)
    {
        debug(i);
        debug(szl);
        debug(szr);
        if (szl >= l && szr <= r)
        {
            debug(this->tree[i]); 
            return this->tree[i];
        }
        if (szr < l || szl > r)
        {
            return this->null_value;
        }

        I mid = (szl + szr) / 2;
        I lc = i << 1;
        I rc = lc + 1;
        if (rc < 2 * this->n)
        {
            debug("rl");
            return this->f(get(lc, l, r, szl, mid), get(rc, l, r, mid + 1, szr));
        }
        else
        {
            debug("l");
            return get(lc, l, r, szl, mid);
        }
    }

    // give zero indexed query
    // @param i : 0 <= i <= n-1 
    // @param j : i <= j <= n-1
    // @return sum a[t], t=i,...,j
    I query(I i, I j)
    {
        return get(1, i, j, 0, this->n - 1);
    }

    void print()
    {
        for (I i = 1; i < 2 * this->n; i++)
        {
            cerr << "(" << i << ", " << this->tree[i] << ") ";
        }
        cerr << "\n";
    }
};

template <typename I>
class segment_heap
{
public:
    // only heap is one indexed to allow for better access
    // elements of original array starts from `n`
    vector<I> heap;
    I null_value = 0;
    I N; // original array length
    I n; // n = 2^k >= N, for such smallest k

    segment_heap();
    // @param
    segment_heap(I n)
    {
        this->N = n;
        n = 1;
        while (n < this->N)
            n <<= 1;
        this->n = n;
        this->heap.assign(2*n + 1, null_value);
    }

    inline I f(I a, I b)
    {
        return a + b;
    }

    void compute(vector<I> &a)
    {

        for (I i = 0; i < this->N; i++)
        {
            this->heap[this->n + i] = a[i];
        }
        for (I i = this->N; i < this->n; i++)
        {
            this->heap[this->n + i] = this->null_value;
        }

        for (I i = this->n - 1; i > 0; i--)
        {
            I lc = i << 1;
            I rc = lc + 1;
            if (rc >= 2 * this->n)
                rc = 0; // 0th element of heap is null value
            heap[i] = this->f(heap[lc], heap[rc]);
        }
    }
    
    void update(I i, I val)
    {
        i += this->n;
        this->heap[i] = val;
        i >>= 1;
        while (i > 0)
        {
            I lc = i << 1;
            I rc = lc + 1;
            if (rc > 2 * this->n)
                rc = 0;
            this->heap[i] = this->f(this->heap[rc], this->heap[lc]);
            i >>= 1;
        }
    }

    // give zero indexed
    I get(I i, I l, I r, I szl, I szr)
    {
        if (szl >= l && szr <= r)
        {
            return this->heap[i];
        }
        if (szr < l || szl > r)
        {
            return this->null_value;
        }

        I mid = (szl + szr) / 2;
        I lc = i << 1;
        I rc = lc + 1;
        if (rc < 2 * this->n)
        {
            return this->f(get(lc, l, r, szl, mid), get(rc, l, r, mid + 1, szr));
        }
        else
        {
            return get(lc, l, r, szl, mid);
        }
    }

    // give zero indexed query
    I query(I i, I j)
    {
        return get(1, i, j, 0, this->n - 1);
    }

    void print()
    {
        for (I i = 1; i < 2 * this->n; i++)
        {
            cerr << "(" << i << ", " << this->heap[i] << ") ";
        }
        cerr << "\n";
    }
};
