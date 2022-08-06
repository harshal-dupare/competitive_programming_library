#pragma once
#include <vector>
#include <algorithm>
#include "../algebra/linear_eq.hpp"
#include "linear_programming_problem.hpp"
#include "simplex.hpp"

template <typename I,typename R>
void basic_feasible_solutions(const linear_programming_problem<I,R> &lpp,std::vector<std::vector<R>> &bfs)
{
    std::vector<int> comb(lpp.n_tot,0);
    for(int i=0;i<lpp.n_eq;i++)
    {
        comb[lpp.n_tot-i-1]=1;
    }
    linear_eq<R> le(lpp.n_eq, lpp.n_eq);
    simplex<I,R> si(lpp);
    while (std::next_permutation(comb.begin(),comb.end()))
    {    
        int k=0;
        for (int i = 0; i < si.n_tot; i++)
        {
            if(comb[i]!=1)
            {
                continue;
            }
            for (int j = 0; j < si.n_eq; j++)
            {
                le.A[j][k] = si.a[j][i+1];
            }
            le.B[k] = si.sol[k];
            k++;
        }
        bool converge = le.gauss_elemination(true);
        std::vector<R> x(si.n_tot, (R)0);
        k = 0;
        for (int i = 0; i < si.n_tot; i++)
        {
            if(comb[i]==1)
            {
                x[i] = le.B[k];
                k++;
            }
        }
        bfs.push_back(x);
    }
};
