#pragma once
#include <vector>
#include <queue>
#include <iostream>
// FIXME check for which one is more optimal in x=f[x]=f[f[x]] or using queue with size heuristic and without
// FIXME combine into 1 big template guy to accomodate all of them

/**
 * ( NO Size heuristic, Level-2 path compression)
 */
template <typename I>
class union_find_2pc
{
public:
    std::vector<I> parent;
    I n;
    union_find_szh_2pc(I _n)
    {
        this->n = _n;
        this->parent = std::vector<I>(_n, -1); // no element in the sets hence all empty as -1
    }
    void make_set(I x)
    {
        this->parent[x] = x;
    }
    bool union_sets(I x, I y)
    {
        I sx = this->find_set(x);
        I sy = this->find_set(y);
        if (sx != sy)
        {
            this->parent[sy] = sx;
            return true;
        }
        return false;
    }
    I find_set(I x)
    {
        if (this->parent[x] == -1)
            return -1;
        // decreases the path length to top by half for x and everyone above it
        while (x != this->parent[x])
        {
            x = this->parent[x] = this->parent[this->parent[x]]; 
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
    friend std::ostream &operator<<(std::ostream &os, const union_find_szh_2pc<I> &uf)
    {
        for (I i = 0; i < uf.n; i++)
        {
            os << i << ":" << uf._const_find_set(i) << ", ";
        }
        os << "\n";
        return os;
    }
};

/**
 * ( Size heuristic, Level-2 path compression)
 */
template <typename I>
class union_find_szh_2pc
{
public:
    std::vector<I> parent;
    std::vector<I> size;
    I n;
    union_find_szh_2pc(I _n)
    {
        this->n = _n;
        this->parent = std::vector<I>(_n, -1); // no element in the sets hence all empty as -1
        this->size = std::vector<I>(_n, 0);    // no element in the sets hence all empty as -
    }
    void make_set(I x)
    {
        this->parent[x] = x;
        this->size[x] = 1;
    }
    bool union_sets(I x, I y)
    {
        I sx = this->find_set(x);
        I sy = this->find_set(y);
        if (sx != sy)
        {
            // sx must have the larger size
            if (this->size[sx] < this->size[sy])
                std::swap(sx, sy);
            this->parent[sy] = sx;
            this->size[sx] += this->size[sy];
            return true;
        }
        return false;
    }
    I find_set(I x)
    {
        if (this->parent[x] == -1)
            return -1;
        // decreases the path length to top by half for x and everyone above it
        while (x != this->parent[x])
        {
            x = this->parent[x] = this->parent[this->parent[x]]; 
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
    friend std::ostream &operator<<(std::ostream &os, const union_find_szh_2pc<I> &uf)
    {
        for (I i = 0; i < uf.n; i++)
        {
            I u = uf._const_find_set(i);
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
        os << "\n";
        return os;
    }
};

/**
 * ( NO Size heuristic, Level-inf path compression using queue )
 */
template <typename I>
class union_find_infpcq
{
public:
    std::vector<I> parent;
    I n;
    union_find_infpcq(I _n)
    {
        this->n = _n;
        this->parent = std::vector<I>(_n, -1); // no element in the sets hence all empty as -1
    }
    void make_set(I x)
    {
        this->parent[x] = x;
    }
    bool union_sets(I x, I y)
    {
        I sx = this->find_set(x);
        I sy = this->find_set(y);
        if (sx != sy)
        {
            this->parent[sy] = sx;
            return true;
        }
        return false;
    }
    I find_set(I x)
    {
        if (this->parent[x] == -1)
            return -1;
        std::queue<I> q;
        q.push(x);
        while (x != this->parent[x])
        {
            x = this->parent[x];
            q.push(x);
        }
        while (!q.empty())
        {
            this->parent[q.front()] = x;
            q.pop();
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
    friend std::ostream &operator<<(std::ostream &os, const union_find_infpcq<I> &uf)
    {
        for (I i = 0; i < uf.n; i++)
        {
            os << i << ":" << uf._const_find_set(i) << ", ";
        }
        os << "\n";
        return os;
    }
};

/**
 * ( Size heuristic, Level-inf path compression using queue )
 */
template <typename I>
class union_find_szh_infpcq
{
public:
    std::vector<I> parent;
    std::vector<I> size;
    I n;
    union_find_szh_infpcq(I _n)
    {
        this->n = _n;
        this->parent = std::vector<I>(_n, -1); // no element in the sets hence all empty as -1
        this->size = std::vector<I>(_n, 0);    // no element in the sets hence all empty as -
    }
    void make_set(I x)
    {
        this->parent[x] = x;
        this->size[x] = 1;
    }
    bool union_sets(I x, I y)
    {
        I sx = this->find_set(x);
        I sy = this->find_set(y);
        if (sx != sy)
        {
            // sx must have the larger size
            if (this->size[sx] < this->size[sy])
                std::swap(sx, sy);
            this->parent[sy] = sx;
            this->size[sx] += this->size[sy];
            return true;
        }
        return false;
    }
    I find_set(I x)
    {
        if (this->parent[x] == -1)
            return -1;
        std::queue<I> q;
        q.push(x);
        while (x != this->parent[x])
        {
            x = this->parent[x];
            q.push(x);
        }
        while (!q.empty())
        {
            this->parent[q.front()] = x;
            q.pop();
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
    friend std::ostream &operator<<(std::ostream &os, const union_find_szh_infpcq<I> &uf)
    {
        for (I i = 0; i < uf.n; i++)
        {
            I u = uf._const_find_set(i);
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
        os << "\n";
        return os;
    }
};
