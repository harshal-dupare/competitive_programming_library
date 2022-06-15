#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../simplex.hpp"
#include "../linear_programming_problem.hpp"

using namespace std;
typedef long long int ll;
typedef double R;

int main()
{
    linear_programming_problem<int, R> lpp;
    lpp.input();
    cout << lpp << endl;
    simplex<int, R> si(lpp);
    cout << si << endl;
    si.compute_table();
    return 0;
}
