#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/linear_programming/linear_programming_problem.hpp"

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
