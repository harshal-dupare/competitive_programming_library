#include <bits/stdc++.h>
#include "../symmetric_function.hpp"

using namespace std;

int main()
{
    int n, k;
    cin >> n;
    k=n;
    vector<long long> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    newtons_formula<long long> nf = newtons_formula<long long>(x); // template argument is needed
    nf.compute(k);
    for (int i = 0; i <= k; i++)
    {
        cout << nf.e[i] << ", " << nf.p[i] << endl;
    }

    return 0;
}