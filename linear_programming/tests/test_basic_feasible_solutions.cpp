#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../basic_feasible_solutions.hpp"
#include "../linear_programming_problem.hpp"

using namespace std;
typedef long long int ll;
typedef double R;

int main()
{
    linear_programming_problem<int, R> lpp;
    lpp.input();
    cout << lpp << endl;
    vector<vector<R>> bfs;
    basic_feasible_solutions(lpp,bfs);
    debug(bfs);
    return 0;
}
