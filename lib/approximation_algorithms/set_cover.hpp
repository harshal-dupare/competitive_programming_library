#pragma once
// FIXME tests
#include <vector>
#include <numeric>
#include <set>
/*
assumes that a solution is possible, i.e. all elements have occured in atleast 1 of the sets
i.e. all vectors in `elements_to_set` have non-zero size and there are `n` such vectors
returns `H_n`-approximation solution cost i.e. opt <= output <= H_n*opt
*/
template<typename I, typename R>
R greedy_min_cost_per_newelements_solution_of_set_cover(const I& n, const I& m, const std::vector<R>& cost_of_set,
const std::vector<std::vector<I>>& element_to_sets,const std::vector<std::vector<I>>& sets_to_elements, std::vector<I> set_sizes, std::vector<R>& solution_set)
{
    R cost_net = R(0);
    std::vector<I> set_choices(m);
    std::vector<bool> element_selected(n,false);
    std::iota(set_choices.begin(),set_choices.end(),I(0));
    solution_set.clear();
    I selected_elems_count = I(0);
    I num_set_choices = I(m);
    while (selected_elems_count < n)
    {
        I opt_i = 0;
        R min_cost_per_newelements = cost_of_set[set_choices[opt_i]]/((R)set_sizes[set_choices[opt_i]]);
        for(I i=1;i<num_set_choices;i++)
        {
            if(cost_of_set[set_choices[i]]/((R)set_sizes[set_choices[i]]) < min_cost_per_newelements)
            {
                min_cost_per_newelements = cost_of_set[set_choices[i]]/((R)set_sizes[set_choices[i]]);
                opt_i = i; 
            }
        }
        num_set_choices--;
        std::swap(set_choices[num_set_choices],set_choices[opt_i]);
        solution_set.push_back(set_choices[num_set_choices]);
        cost_net+=cost_of_set[set_choices[num_set_choices]];

        for(I ele: sets_to_elements[set_choices[num_set_choices]])
        {
            if(element_selected[ele]) 
            {
                continue;
            }
            selected_elems_count++;
            for(I sets_ele : element_to_sets[ele])
            {
                set_sizes[sets_ele]--;
            }
            element_selected[ele] = true;
        }

        for(I i=0;i<num_set_choices;i++)
        {
            if(set_sizes[set_choices[i]]==I(0))
            {
                num_set_choices--;
                std::swap(set_choices[num_set_choices],set_choices[i]);
                i--;
            }
        }
    }
    return cost_net;
}