#pragma once
// FIXME tests
#include <vector>
#include <numeric>
#include <set>
#include <utility>
#include <algorithm>
#include "../graphs/graph.hpp"
#include "../randoms/random_gen.hpp"
#include "../data_structure/union_find.hpp"

using namespace std;

// assumes graph is connected
// O(|V|+|E|*log_star(|V|))
// P[|solution|==|min_cut|] >= tC2/nC2
template <typename I>
I kargers_randomized_algorithm_for_min_cut(I n, const vector<pair<I, I>> &edge_list, vector<I> &min_cut, vector<pair<I, I>> &min_cut_edges, I t = 2)
{

    simple_fast_union_find<I> uf(n);
    for (I i = 0; i < n; i++)
    {
        uf.make_set(i);
    }

    // since this requires log_2(n!) random bits, if we want to minimize the number of random bits
    // required and dynamically get the next edge only if there are not any edges in the list
    // connecting 2 vertcies in the same set, since this can be too complex and can make it O(n^2)
    // we can only keep track of last k edges and ensure that all of them are not already in same set
    // k=1, looks better as it ensures cache friendliness and any other k>1 is an early-pruning version of k=1
    vector<I> eid(edge_list.size());
    std::iota(eid.begin(), eid.end(), 0);
    random_shuffle(eid.begin(), eid.end());

    I v_count = n;
    I j = 0;
    for (j; v_count > t && j < (I)edge_list.size(); j++)
    {
        if (uf.union_sets(edge_list[j].first, edge_list[j].second))
        {
            // if it was not merged before, so one vertex reduced
            v_count--;
        }
    }

    vector<I> set_id_compression(n, (I)-1);
    v_count = 0;
    min_cut.assign(n);
    for (I i = 0; i < n; i++)
    {
        min_cut[i] = uf.find_set(i);
        if (set_id_compression[min_cut[i]] == (I)-1)
        {
            set_id_compression[min_cut[i]] = v_count;
            v_count++;
        }
        min_cut[i] = set_id_compression[min_cut[i]];
    }

    min_cut_edges.clear();
    for (; j < (I)edge_list.size(); j++)
    {
        if (min_cut[edge_list[j].first] == min_cut[edge_list[j].second])
        {
            continue;
        }
        min_cut_edges.push_back(edge_list[j]);
    }
    return (I)min_cut_edges.size();
}

// assumes graph is connected
// brute force : O(2^(n/2)*|E|)
// if |E| = O(|V|^2) at all stages then we have : O(n^2*log_star(n)*log(n))
// P[|solution|==|min_cut|] >= c/log(n) , for some c
template <typename I>
I karger_stine_randomized_algorithm_for_min_cut(I n, const vector<pair<I, I>> &edge_list, vector<I> &min_cut, vector<pair<I, I>> &min_cut_edges, const I n_bruteforce_limit = 6)
{
    if (n <= n_bruteforce_limit)
    {
        // bruteforce correct answer
        // 2^(n/2)*|E| bruteforce
        vector<I> min_cut_i(n, (I)0);
        I min_cut_size = 1 + (I)edge_list.size();
        for (I i = 1; 2 * i <= n; i++)
        {
            min_cut_i[n - i] = 1;
            do
            {
                I min_cut_size_i = 0;
                for (pair<I, I> edg : edge_list)
                {
                    if (min_cut_i[edg.first] != min_cut_i[edg.second])
                    {
                        min_cut_size_i++;
                    }
                }
                if (min_cut_size_i < min_cut_size)
                {
                    min_cut.assign(min_cut_i.begin(), min_cut_i.end());
                }
            } while (std::next_permutation(min_cut_i.begin(), min_cut_i.end()));
        }

        min_cut_edges.clear();
        for (pair<I, I> edg : edge_list)
        {
            if (min_cut[edg.first] == min_cut[edg.second])
            {
                min_cut_edges.push_back(make_pair(min_cut[edg.first], min_cut[edg.second]));
            }
        }
        
        return min_cut_size;
    }
    
    double sqrt2 = 1.414213562373095048;
    I t = 1 + (I)ceil(((double)n) / sqrt2);
    vector<I> min_cut_1, min_cut_2;
    vector<pair<I, I>> min_cut_edges_1, min_cut_edges_2;

    kargers_randomized_algorithm_for_min_cut(n, edge_list, min_cut_1, min_cut_edges_1, t);
    for (I i = 0; i < (I)min_cut_edges_1.size(); i++)
    {
        min_cut_edges_1[i] = make_pair(min_cut_1[min_cut_edges_1[i].first], min_cut_1[min_cut_edges_1[i].second])
    }

    kargers_randomized_algorithm_for_min_cut(n, edge_list, min_cut_2, min_cut_edges_2, t);
    for (I i = 0; i < (I)min_cut_edges_2.size(); i++)
    {
        min_cut_edges_2[i] = make_pair(min_cut_2[min_cut_edges_2[i].first], min_cut_2[min_cut_edges_2[i].second])
    }

    vector<I> r_min_cut_1, r_min_cut_2;
    vector<pair<I, I>> r_min_cut_edges_1, r_min_cut_edges_2;
    I new_t_1 = karger_stine_randomized_algorithm_for_min_cut(t, min_cut_edges_1, r_min_cut_1, r_min_cut_edges_1, n_limit);
    I new_t_2 = karger_stine_randomized_algorithm_for_min_cut(t, min_cut_edges_2, r_min_cut_2, r_min_cut_edges_2, n_limit);

    min_cut.assign(n, (I)-1);
    if (new_t_2 < new_t_1)
    {
        for (I i = 0; i < n; i++)
        {
            min_cut[i] = r_min_cut_2[min_cut_2[i]];
        }
    }
    else
    {
        for (I i = 0; i < n; i++)
        {
            min_cut[i] = r_min_cut_1[min_cut_1[i]];
        }
    }
    min_cut_edges.clear();
    for (pair<I, I> edg : edge_list)
    {
        if (min_cut[edg.first] == min_cut[edg.second])
        {
            min_cut_edges.push_back(make_pair(min_cut[edg.first], min_cut[edg.second]));
        }
    }
    assert(std::min(new_t_1, new_t_2) == (I)min_cut_edges.size());
    return (I)min_cut_edges.size();
}
