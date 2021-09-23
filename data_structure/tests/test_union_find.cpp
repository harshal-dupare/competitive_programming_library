#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../union_find.hpp"

using namespace std;
typedef long long int ll;
typedef double R;

void test_dsu()
{
    union_find<int> uf(100);

    int t;
    cin >> t;
    while ((t--) > 0)
    {
        int c;
        int x, y;
        cin >> c;
        if(c==0)
        {
            cin >> x;
            cout << uf.find_set(x) << endl;
        }
        if(c==1)
        {
            cin>>x;
            uf.make_set(x);
            cout<<uf;
        }
        if(c==2)
        {
            cin >> x >> y;
            uf.union_sets(x, y);
            cout<<uf;
        }
    }

}

int main()
{
    return 0;
}
