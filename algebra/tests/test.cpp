#include <bits/stdc++.h>

// namespaces starts
using namespace std;

int main()
{
    int n;
    cin >> n;
    matrix<int> c(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> c.a[i][j];
        }
    c.print();
    matrix tc = c.per(c, 10);
    tc.print();

    return 0;
}
