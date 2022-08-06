#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/linear_programming/big_M.hpp"
#include "../../lib/linear_programming/linear_programming_problem.hpp"

using namespace std;
typedef long long int ll;
typedef double R;

int main()
{
    linear_programming_problem<int, R> lpp;
    lpp.input();
    cout << lpp << endl;
    big_M<int, R> bm(lpp);
    cout << bm << endl;
    bm.make_consistent();
    cout << bm << endl;
    bm.compute_table();
    return 0;
}
