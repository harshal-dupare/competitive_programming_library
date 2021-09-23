#include <bits/stdc++.h>
#include "../../utils/timer.hpp"
#include "../../utils/new_debug_out.hpp"
#include "../stable_matching.hpp"

using namespace std;
auto rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());


double test_stable_matching(int n, int m)
{
    vector<int> rangm(n);
    vector<int> rangw(m);
    for (int i = 0; i < n; i++)
        rangm[i] = i;
    for (int i = 0; i < m; i++)
        rangw[i] = i;

    auto  myrandom =  [&](int i) { return rng()%i;};
    vector<vector<int>> men(n), women(m),wprt;
    for (int i = 0; i < n; i++)
    {
        random_shuffle(rangw.begin(), rangw.end(),myrandom);
        men[i] = rangw;
    }
    for (int i = 0; i < m; i++)
    {
        random_shuffle(rangm.begin(), rangm.end(),myrandom);
        women[i] = rangm;
    }
    vector<int> maxmp(n,2);
    vector<int> maxwp(m,3);
    timer tm;
    tm.set();
    stable_matching<int>(men, women,maxmp,maxwp,wprt);
    tm.save("computing");
    // debug(men);
    // debug(women);
    // debug(wprt);
    // tm.show_events();
    return tm.event_time[0];
}

int main()
{
    freopen("output.txt","w",stdout);
    for(int n=10;n<1000;n+=10)
    {
        for(int m=10;m<1000;m+=10)
        {
            cout<<n<<" "<<m<<" "<<test_stable_matching(n,m)<<"\n";
        }
    }

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