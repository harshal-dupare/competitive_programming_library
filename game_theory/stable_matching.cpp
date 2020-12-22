#include <bits/stdc++.h>
#include "../utils/timer.h"

using namespace std;

#define ok(x) cerr << #x << ": " << x << endl;

template <typename I>
class stable_matching
{
public:
    I n;
    vector<vector<I>> women;
    vector<vector<I>> men;
    vector<vector<I>> wpartner;
    vector<vector<I>> mpartner;
    
    // input preferences must be in reverse
    stable_matching(I n, vector<vector<I>> men, vector<vector<I>> &womenp)
    {
        this->n = n;
        this->men = men;
        this->women = vector<vector<I>>(n, vector<I>(n));
        for (I i = 0; i < n; i++)
        {
            for (I j = 0; j < n; j++)
            {
                this->women[i][womenp[i][j]] = j;
            }
            reverse(this->men[i].begin(), this->men[i].end());
        }
        this->wpartner = vector<vector<I>>(n, vector<I>(0));
        // ok("created")
    }

    void match()
    {
        vector<bool> pool(this->n, true);
        I inpool = this->n;
        while (inpool > 0)
        {
            // make all the proposals
            for (I man = 0; man < this->n; man++)
            {
                if (!pool[man])
                    continue;

                I best_women = this->men[man][this->men[man].size() - 1];
                this->men[man].pop_back();
                // propose the best women
                this->wpartner[best_women].push_back(man);
                pool[man]=false;
                inpool--;
            }

            for (I i = 0; i < this->n; i++)
            {
                if (this->wpartner[i].size() > 1)
                {
                    auto best_man = this->wpartner[i].begin();
                    for (auto man = this->wpartner[i].begin() + 1; man != this->wpartner[i].end(); man++)
                    {
                        if (this->women[i][(*man)] < this->women[i][(*best_man)])
                        {
                            pool[*best_man]= true;
                            inpool++;
                            best_man = man;
                        }
                        else
                        {
                            pool[*man]=true;
                            inpool++;
                        }
                    }
                    // this->wpartner[i].clear();
                    // this->wpartner[i].push_back((*best_man));
                    this->wpartner[i] = vector<I>(1,(*best_man));
                }
            }
            // ok("pool created")
        }
    }

    void show_matching()
    {
        for (I i = 0; i < this->n; i++)
        {
            cout << i << ": " << this->wpartner[i][0] << endl;
        }
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> rang(n);
    for (int i = 0; i < n; i++)
        rang[i] = i;
    vector<vector<int>> men(n), women(n);
    for (int i = 0; i < n; i++)
    {
        random_shuffle(rang.begin(), rang.end());
        men[i] = rang;

        random_shuffle(rang.begin(), rang.end());
        women[i] = rang;
    }
    timer tm;
    tm.set();
    stable_matching<int> sm(n, men, women);
    tm.save("making");
    // for (int i = 0; i < n; i++)
    // {
    //     cout << "men " << i << ": ";
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << men[i][j] << ", ";
    //     }
    //     cout << endl;
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << "women " << i << ": ";
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << women[i][j] << ", ";
    //     }
    //     cout << endl;
    // }
    sm.match();
    tm.save("computing");
    sm.show_matching();
    tm.show_events();
    cout<<tm.event_time[0]+tm.event_time[1]<<endl;
    // stable_matching<int> sm2(n, women, men);
    // sm2.match();
    // sm2.show_matching();

    return 0;
}

/*

5

men 0: 4, 3, 1, 2, 0,
men 1: 4, 0, 2, 1, 3,
men 2: 1, 2, 3, 4, 0,
men 3: 2, 1, 4, 0, 3,
men 4: 3, 4, 1, 2, 0,
women 0: 4, 1, 0, 3, 2,
women 1: 0, 3, 4, 1, 2,
women 2: 1, 2, 3, 4, 0,
women 3: 2, 0, 3, 4, 1,
women 4: 3, 1, 0, 2, 4,

0: 4
1: 3
2: 2
3: 0
4: 1

men 0: 1, 2, 0,
men 1: 0, 2, 1, 3,
men 2: 3, 4, 0,
men 3: 1, 4, 0, 3,
men 4:  0,

4:1
1:3
2:2
3:0
0:4

*/