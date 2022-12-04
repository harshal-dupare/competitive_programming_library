#pragma once
// FIXME tests
#include <vector>
#include <numeric>
#include <set>
#include "../graphs/graph.hpp"
#include "../graphs/tree.hpp"
using namespace std;

// opt <= output <= 2*opt
template <typename I, typename R>
R metric_minimum_hamiltoninan_cycle_2_approx_using_mst(const wgraph<I, R> &g, vector<I>& cycle_order)
{
    vector<I> parent;
    prims<I,R>(g,parent);
    vector<vector<I>> adjl;
    tree::get_adjl_using_parent(parent,adjl);
    vector<I> eseq;
    tree::eulerian_sequence(parent,eseq);
    vector<bool> visited(g.n,false);
    
    cycle_order.clear();
    for(I eseq_i: eseq)
    {
        if(visited[eseq_i])
        {
            continue;
        }
        cycle_order.push_back(eseq_i);
        visited[eseq_i] = true;
    }
    
    R _cost = R(0);
    for(I i=0;i<g.n-1;i++)
    {
        _cost+=g.edge_weight[g.N*cycle_order[i]+cycle_order[i+1]];
    }
    _cost+=g.edge_weight[g.N*cycle_order[g.n-1]+cycle_order[0]];
    return _cost;
}

// opt <= output <= 1.5*opt
template <typename I, typename R>
R metric_minimum_hamiltoninan_cycle_1p5_approx_using_mst_and_matching(const wgraph<I, R> &g, vector<I>& cycle_order)
{

}
