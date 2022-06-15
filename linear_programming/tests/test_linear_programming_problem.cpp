#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../linear_programming_problem.hpp"

using namespace std;
typedef long long int ll;
typedef double R;

int main()
{
    linear_programming_problem<ll, R> lp;
    lp.input();
    cout << lp << endl;
    auto dual = dual_problem(lp);
    cout << dual << endl;
    return 0;
}
