#pragma once

#include <bits/stdc++.h>
#include "../utils/debug_out.hpp"

// FIXME correctness
template<typename I>
class group
{
public:
    I order;
    std::vector<std::vector<I>> table;
    group(I order)
    {
        this->order = order;
        this->table.assign(order, std::vector<I>(order));
    }

    void input(std::map<I, I> &mp)
    {
        for (I i = 0; i < order; i++)
        {
            for (I j = 0; j < order; j++)
            {
                I tp;
                std::cin >> tp;
                table[i][j] = tp;
            }
        }
    }

    void iter_over_subsets(std::vector<I> &subset, I nxt, std::vector<std::vector<I>> &subg, std::map<I, I> &imp)
    {
        // check if its subgroup
        std::set<I> elems;
        for (I i = 0; i < subset.size(); i++)
        {
            for (I j = 0; j < subset.size(); j++)
            {
                elems.insert(table[subset[i]][subset[j]]);
            }
        }

        if (elems.size() == subset.size())
        {
            I i = 0;
            std::vector<I> apnd;
            for (auto y : elems)
            {
                if (subset[i] != y)
                    break;
                apnd.push_back(imp[subset[i]]);
                i++;
            }
            if (i == subset.size())
            {
                subg.push_back(apnd);
            }
        }

        for (I i = nxt; i < order; i++)
        {
            subset.push_back(i);
            iter_over_subsets(subset, i + 1, subg, imp);
            subset.pop_back();
        }
    }

    void find_subgroups(std::vector<std::vector<I>> &subg, std::map<I, I> &imp)
    {
        std::vector<I> subset;
        iter_over_subsets(subset, 0, subg, imp);
    }

    I inverse(I a)
    {
        for(I i=0;i<order;i++)
        {
            if(table[a][i]==0)
            {
                return i;
            }
        }
        
        // must be never retured
        return -1;
    }

    bool is_abelian()
    {
        for(I i=0;i<order;i++)
        {
            for(I j=i+1;j<order;j++)
            {
                if(table[i][j]!=table[j][i])
                {
                    return false;
                }
            }
        }

        return true;
    }

    I order_of(I a)
    {
        if(a==0) return 0;
        I ct = 1;

        while(ct<order+1)
        {
            if(table[a][a]==0)
            {
                return ct;
            }
            ct++;
        }

        return -1;
    }

};
