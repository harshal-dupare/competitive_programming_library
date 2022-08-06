#include <bits/stdc++.h>
#include "../../lib/number_theory/general_linear_recurrence.hpp"

using namespace std;
typedef long long ll;

void test_gen_matrix_seq()
{
    int n, m;
    cin >> n >> m;
    vector<ll> base(m);
    vector<vector<ll>> recmatrix(m, vector<ll>(m));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> recmatrix[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        cin >> base[i];
    }

    general_matrix_sequence<ll> gs(n, recmatrix, m, base);

    for (int i = 0; i < n; i++)
    {
        cout << i << " : " << gs.get_ith(i) << endl;
    }

    gs.extend(100);

}

int main()
{
    return 0;
}