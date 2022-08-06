#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/linear_programming/simplex.hpp"
#include "../../lib/linear_programming/linear_programming_problem.hpp"

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
