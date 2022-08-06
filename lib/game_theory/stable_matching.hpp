#pragma once
#include <vector>

// always gives better allotment for men
// O(log(sum(max_num_wpartners))*sum(max_num_mpartners)*sum(max_num_wpartners)  +  num_men*num_women)
// O(m*w*log(w))
template<typename I>
void stable_matching(const std::vector<std::vector<I>>& menp, const std::vector<std::vector<I>> &womenp,
                     const std::vector<I> &max_num_mpartners, const std::vector<I> &max_num_wpartners, 
                     std::vector<std::vector<I>> & wpartner)
{
    // set the initial data 
    I n_men = (I)menp.size();
    I n_women = (I)womenp.size();
    std::vector<I> men_sid(n_men,0);// all men first prorpose the most prefered women
    // O(m*w)
    std::vector<std::vector<I>> women(n_women, std::vector<I>(n_men,-1));
    for (I i = 0; i < n_women; i++)
    {
        for (I j = 0; j < n_men; j++)
        {
            women[i][womenp[i][j]] = j;
        }
    }
    wpartner.assign(n_women, std::vector<I>(0));
    std::vector<I> num_matchings_done(n_men,0);

    
    I inpool = 0;
    // O(|Sm|=|#pm1|+|#pm2|+...) totoal number of partners of men
    for(I i=0;i<n_men;i++)inpool+=max_num_mpartners[i];

    // O(log(Sw)*Sm*Sw)
    while (inpool > 0)
    {
        // all men make their proposals
        // O(m(not_fully_matched))
        for (I man = 0; man < n_men; man++)
        {
            if (num_matchings_done[man]>=max_num_mpartners[man])
                continue;
            if(men_sid[man]<(I)menp[man].size())
            {
                // get the best women
                I best_women = menp[man][men_sid[man]];
                men_sid[man]++;

                // propose the best women
                wpartner[best_women].push_back(man);
            }
            num_matchings_done[man]++;
            inpool--;
        }
        
        // let |Sw|=|#pw1|+|#pw2|+...) totoal number of partners of men
        // O(log(|#pw1|*||#pw1|+m1|+log(|#pw2|*||#pw2|+m2|+...) <= O(log(Sw)*(Sw+m(not_fully_matched)))
        for (I i = 0; i < n_women; i++)
        {
            if ((I)wpartner[i].size() > max_num_wpartners[i])
            {
                // O(log(k)*|wprt[i]|)
                std::vector<I> best_men;
                for(I j=0;j<max_num_wpartners[i];j++) best_men.push_back(wpartner[i][j]);
                auto comps = [&](I men1,I men2){return women[i][men1]<women[i][men2];};
                std::make_heap(best_men.begin(),best_men.end(),comps);
                for (auto man = wpartner[i].begin() +  max_num_wpartners[i]; man != wpartner[i].end(); man++)
                {
                    // O(log(k))
                    if (women[i][(*man)] < women[i][best_men[0]])
                    {
                        // current man is better than the current worst man
                        num_matchings_done[best_men[0]]--;
                        inpool++;
                        std::pop_heap(best_men.begin(), best_men.end(),comps);
                        best_men.pop_back();
                        best_men.push_back((*man));
                        std::push_heap(best_men.begin(), best_men.end(),comps);
                    }
                    else
                    {
                        num_matchings_done[*man]--;
                        inpool++;
                    }
                }
                wpartner[i] = best_men;
            }
        }
    }
}
