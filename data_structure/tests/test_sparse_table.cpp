#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../sparse_table.hpp"
using namespace std;

typedef long long ll;
typedef double R;

int fc(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

void test_sparse_table()
{

    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    sparse_table<int> tb(n,*fc,a);
    tb.compute();
    int k;
    cin>>k;
    int i,j;
    while (k--)
    {
        cin>>i>>j;
        int h= tb.query(i,j);
        cout<<h<<endl;
    }

}

int main()
{
    return 0;
}