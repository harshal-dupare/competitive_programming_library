#pragma once
#include <bits/stdc++.h>
#include "graph.hpp"
#include "dgraph.hpp"
#include <random>
#include <chrono>
// FIXME tests
namespace special_graph
{
    template <typename I, class E=mt19937>
    class erdos_renyi : public graph<I>
    {
        public:
        erdos_renyi(I n, I m) : graph<I>(n)
        {
            I M = n * n;
            E rg = E(chrono::steady_clock::now().time_since_epoch().count());
            std::vector<I> per(M,0);
            for(I i=0;i<M;i++)per[i]=i;
            for(I i=M-1;m>(I)0;i--,m--)
            {
                I rn = rg()%(1+i);
                if(rn<(I)0)rn+=i+1;
                swap(per[i],per[rn]);
                this->add_edge(per[i]%n,per[i]/n);
            }
        }

        erdos_renyi(I n, double p) : graph<I>(n)
        {
            auto randgen = bind(std::bernoulli_distribution(p), E(chrono::steady_clock::now().time_since_epoch().count()));
            for (I i = 0; i < n; i++)
            {
                for (I j = i + 1; j < n; j++)
                {
                    if (randgen())
                    {
                        this->add_edge(i, j);
                    }
                }
            }
        }
    };
    template <typename I>
    class k_regular : public graph<I>
    {
        public:
        k_regular(I k, I n) : graph<I>(n)
        {
        }
    };
    template <typename I>
    class line : public graph<I>
    {
        public:
        line(I n) : graph<I>(n)
        {
            for (I i = 1; i < n; i++)
            {
                this->add_edge(i - 1, i);
            }
        }
    };
    template <typename I>
    class complete : public graph<I>
    {
        public:
        complete(I n) : graph<I>(n)
        {
            for (I i = 0; i < n; i++)
            {
                for (I j = i + 1; j < n; j++)
                {
                    this->add_edge(i, j);
                }
            }
        }
    };
    template <typename I>
    class cycle : public graph<I>
    {
        public:
        cycle(I n) : graph<I>(n)
        {
            for (I i = 1; i < n; i++)
            {
                this->add_edge(i - 1, i);
            }
            this->add_edge(n - 1, 0);
        }
    };
    template <typename I>
    class star : public graph<I>
    {
        public:
        star(I n) : graph<I>(n)
        {
            for (I i = 1; i < n; i++)
            {
                this->add_edge(0, i);
            }
        }
    };
    template <typename I>
    class wheel : public graph<I>
    {
        public:
        wheel(I n):
        graph<I>(n + 1)
        {
            for (I i = 1; i < n; i++)
            {
                this->add_edge(0, i);
                this->add_edge(i, i + 1);
            }
            this->add_edge(n, 1);
        }
    };
    template <typename I>
    class friendship_graph : public graph<I>
    {
        public:
        friendship_graph(I n) : graph<I>(2 * n + 1)
        {
            for (I i = 1; i < 2 * n + 1; i++)
            {
                this->add_edge(0, i);
            }
            for (I i = 0; i < n; i++)
            {
                this->add_edge(2 * i + 2, 2 * i + 1);
            }
        }
    };
    template <typename I>
    class hypercube : public graph<I>
    {
        public:
        hypercube(I n) : graph<I>(1 << n)
        {
            // 2^n vertices
            // O(n*2^n)
            I vn = 1 << n;

            for (I i = 0; i < vn; i++)
            {
                for (I j = 0; j < n; j++)
                {
                    if (i < (i ^ (1 << j)))
                    {
                        this->add_edge(i, i ^ (1 << j));
                    }
                }
            }
        }
    };
    template <typename I>
    class octahedral : public graph<I>
    {
        public:
        octahedral(I n) : graph<I>(2)
        {
            // scope to optimize
            this->add_edge(0, 1);
            special_graph::complete<I> K2(2);
            for (I i = 1; i < n; i++)
            {
                (*this) = (this) + K2;
            }
        }
    };
    template <typename I>
    class complete_biparted : public graph<I>
    {
        public:
        complete_biparted(I n, I m) : graph<I>(n + m)
        {
            for (I i = 0; i < n; i++)
            {
                for (I j = n; j < n + m; j++)
                {
                    this->add_edge(i, j);
                }
            }
        }
    };
    template <typename I>
    class perterson : public graph<I>
    {
        public:
        perterson() : graph<I>((I)10)
        {
            this->add_edge(0, 1);
            this->add_edge(1, 2);
            this->add_edge(2, 3);
            this->add_edge(3, 4);
            this->add_edge(4, 0);

            this->add_edge(5, 7);
            this->add_edge(6, 8);
            this->add_edge(7, 9);
            this->add_edge(8, 5);
            this->add_edge(9, 6);

            this->add_edge(0, 0 + 5);
            this->add_edge(1, 1 + 5);
            this->add_edge(2, 2 + 5);
            this->add_edge(3, 3 + 5);
            this->add_edge(4, 4 + 5);
        }
    };
};
