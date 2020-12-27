#pragma once
#include <bits/stdc++.h>


template <typename I>
class generator
{
public:
    void erdos_renyi(I n, I m, graph<I> &G)
    {
        
    }

    void line(I n, graph<I> &G)
    {
        G = graph<I>(n);
        for (I i = 1; i < n; i++)
        {
            G.add_edge(i - 1, i);
        }
    }

    void complete(I n, graph<I> &G)
    {
        G = graph<I>(n);

        for (I i = 0; i < n; i++)
        {
            for (I j = i + 1; j < n; j++)
            {
                G.add_edge(i, j);
            }
        }
    }

    void cycle(I n, graph<I> &G)
    {
        G = graph<I>(n);
        for (I i = 1; i < n; i++)
        {
            G.add_edge(i - 1, i);
        }
        G.add_edge(n - 1, 0);
    }

    void k_regular(I k, I n, graph<I> &G)
    {
    }

    void hypercube(I n, graph<I> &G)
    {
        // 2^n vertices
        // O(n*2^n)
        I vn = 1 << n;
        G = graph<I>(vn);

        for (I i = 0; i < vn; i++)
        {
            for (I j = 0; j < n; j++)
            {
                if (i < (i ^ (1 << j)))
                {
                    G.add_edge(i, i ^ (1 << j));
                }
            }
        }
    }

    void octahedral(I n, graph<I> &G)
    {
        // scope to optimize
        this->complete(2, G);
        graph<I> K2;
        this->complete(2, K2);
        for (I i = 1; i < n; i++)
        {
            G = G + K2;
        }
    }

    void complete_biparted(I n, I m, graph<I> &G)
    {
        G = graph<I>(n + m);
        for (I i = 0; i < n; i++)
        {
            for (I j = n; j < n + m; j++)
            {
                G.add_edge(i, j);
            }
        }
    }

    void perterson(graph<I> &G)
    {
        G = graph<I>(10);
        G.add_edge(0, 1);
        G.add_edge(1, 2);
        G.add_edge(2, 3);
        G.add_edge(3, 4);
        G.add_edge(4, 0);

        G.add_edge(5, 7);
        G.add_edge(6, 8);
        G.add_edge(7, 9);
        G.add_edge(8, 5);
        G.add_edge(9, 6);

        G.add_edge(0, 0 + 5);
        G.add_edge(1, 1 + 5);
        G.add_edge(2, 2 + 5);
        G.add_edge(3, 3 + 5);
        G.add_edge(4, 4 + 5);
    }
};
