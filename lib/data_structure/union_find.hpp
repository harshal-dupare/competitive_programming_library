#pragma once
#include <vector>
#include <queue>
#include <iostream>

template <typename I, const bool Size_Heuristic = false, const bool Compression_Order_2 = true, const bool Inf_Path_Compression_Queue = false>
class union_find
{
public:
    std::vector<I> parent;
    std::vector<I> size;
    I n;
    union_find(I _n)
    {
        this->n = _n;
        this->parent = std::vector<I>(_n, -1); // no element in the sets hence all empty as -1
        if (Size_Heuristic)
        {
            this->size = std::vector<I>(_n, 0); // no element in the sets hence all empty as
        }
    }
    void make_set(I x)
    {
        this->parent[x] = x;
        if (Size_Heuristic)
        {
            this->size[x] = 1;
        }
    }
    bool union_sets(I x, I y)
    {
        I sx = this->find_set(x);
        I sy = this->find_set(y);
        if (sx != sy)
        {
            if (Size_Heuristic)
            {
                // sx must have the larger size
                if (this->size[sx] < this->size[sy])
                {
                    std::swap(sx, sy);
                }
                this->size[sx] += this->size[sy];
            }
            this->parent[sy] = sx;
            return true;
        }
        return false;
    }
    // FIXME: convert this to enable if
    I find_set(I x)
    {
        if (this->parent[x] == -1)
            return -1;
        // decreases the path length to top by half for x and everyone above it
        if (Inf_Path_Compression_Queue)
        {
            std::queue<I> q;
            q.push(x);
        }
        while (x != this->parent[x])
        {
            if (Compression_Order_2)
            {
                x = this->parent[x] = this->parent[this->parent[x]];
            }
            else
            {
                x = this->parent[x];
            }

            if (Inf_Path_Compression_Queue)
            {
                q.push(x);
            }
        }

        if (Inf_Path_Compression_Queue)
        {
            while (!q.empty())
            {
                this->parent[q.front()] = x;
                q.pop();
            }
        }
        return x;
    }
    I _const_find_set(I x) const
    {
        if (this->parent[x] == -1)
            return -1;
        while (x != this->parent[x])
        {
            x = this->parent[x];
        }
        return x;
    }
    I _count_jumps_to_find_parent_of(I x) const
    {
        I ct = 0;
        if (this->parent[x] == -1)
            return ct;
        while (x != this->parent[x])
        {
            x = this->parent[x];
            ct++;
        }
        return ct;
    }
    friend std::ostream &operator<<(std::ostream &os, const union_find<I, Size_Heuristic, Compression_Order_2, Inf_Path_Compression_Queue> &uf)
    {
        for (I i = 0; i < uf.n; i++)
        {
            I u = uf._const_find_set(i);

            if (Size_Heuristic)
            {
                os << i << ":(" << u << ",";
                if (u == -1)
                {
                    os << "0), ";
                }
                else
                {
                    os << uf.size[u] << "), ";
                }
            }
            else
            {
                os << i << ":" << uf._const_find_set(i) << ", ";
            }
        }
        os << "\n";
        return os;
    }
};

