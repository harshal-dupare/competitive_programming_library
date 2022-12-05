#pragma once
// FIXME tests
#include <vector>
#include <numeric>
#include <set>
#include "../graphs/graph.hpp"
#include "../randoms/random_gen.hpp"
#include "../data_structure/union_find.hpp"

using namespace std;

// O(|V|+|E|*log_star(|V|))
template<typename I>
void kargers_randomized_algorithm_for_min_cut(const graph<I>& g, vector<I>& min_cut)
{
    vector<pair<I,I>> edge_list;
    assign_edge_list(g,edge_list);

    simple_fast_union_find<I> uf(g.n);
    for(I i=0;i<g.n;i++){uf.make_set(i);}

    // since this requires log_2(n!) random bits, if we want to minimize the number of random bits 
    // required and dynamically get the next edge only if there are not any edges in the list 
    // connecting 2 vertcies in the same set, since this can be too complex and can make it O(n^2) 
    // we can only keep track of last k edges and ensure that all of them are not already in same set 
    // k=1, looks better as it ensures cache friendliness and any other k>1 is an early-pruning version of k=1
    vector<I> eid(edge_list.size());
    std::iota(eid.begin(),eid.end(),0);
    random_shuffle(eid.begin(),eid.end());

    I v_count = g.n;
    for(I i=0; v_count>(I)2 && i<(I)edge_list.size();i++)
    {
        if(uf.union_sets(edge_list[i].first,edge_list[i].second))
        {
            // if it was not merged before, so one vertex reduced
            v_count--;
        }
    }

    I _one_val = uf.find_set(0);
    min_cut[0] = 0;
    for(I i=1;i<g.n;i++)
    {
        if(uf.find_set(i)==_one_val)
        {
            min_cut[i] = 0;
        }
        else
        {
            min_cut[i] = 1;
        }
    }
}
