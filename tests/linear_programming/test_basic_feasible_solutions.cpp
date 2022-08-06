#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/linear_programming/basic_feasible_solutions.hpp"
#include "../../lib/linear_programming/linear_programming_problem.hpp"

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
