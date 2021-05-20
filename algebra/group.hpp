#pragma once

#include <bits/stdc++.h>
#include "../utils/debug_out.hpp"

class group
{
public:
    int order;
    std::vector<std::vector<int>> table;
    group(int order)
    {
        this->order = order;
        this->table.assign(order, std::vector<int>(order));
    }

    void input(std::map<int, int> &mp)
    {
        for (int i = 0; i < order; i++)
        {
            for (int j = 0; j < order; j++)
            {
                int tp;
                cin >> tp;
                table[i][j] = element(tp);
            }
        }
    }

    void iter_over_subsets(std::vector<int> &subset, int nxt, std::vector<std::vector<int>> &subg, std::map<int, int> &imp)
    {
        // check if its subgroup
        set<int> elems;
        for (int i = 0; i < subset.size(); i++)
        {
            for (int j = 0; j < subset.size(); j++)
            {
                elems.insert(table[subset[i]][subset[j]]);
            }
        }

        if (elems.size() == subset.size())
        {
            int i = 0;
            std::vector<int> apnd;
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

        for (int i = nxt; i < order; i++)
        {
            subset.push_back(i);
            iter_over_subsets(subset, i + 1, subg, imp);
            subset.pop_back();
        }
    }

    void find_subgroups(std::vector<std::vector<int>> &subg, std::map<int, int> &imp)
    {
        std::vector<int> subset;
        iter_over_subsets(subset, 0, subg, imp);
    }

    int inverse(int a)
    {
        for(int i=0;i<order;i++)
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

    int order_of(int a)
    {
        if(a==0) return 0;
        int ct = 1;

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


template<typename I>
struct element
{
    I id;

    friend element<I> operator*(element a)
    {
        // define the operator of the group
    }
};

template<typename I>
struct general_group
{
    
};