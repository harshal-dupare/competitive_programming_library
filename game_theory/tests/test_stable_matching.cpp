#include <bits/stdc++.h>
#include "../../utils/timer.hpp"
#include "../stable_matching.hpp"

using namespace std;

#define ok(x) cerr << #x << ": " << x << endl;

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