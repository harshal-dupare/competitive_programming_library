#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/randoms/random_gen.hpp"
#include "../../lib/data_structure/union_find.hpp"

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

void test_simple_fast_dsu_performance()
{
    ll n = 1000;
    auto rg = random_gens::uniform_int<ll>(0,n);
    union_find<ll> dsu(n);
    dsu.parent[0] = 0;
    for(ll i=1;i<n;i++)
    {
        dsu.parent[i]=i-1;
    }

    int k = 20;
    for(int i=0;i<k;i++)
    {
        dsu.find_set(rg());
        ll net = 0;
        for(int j=0;j<n;j++)
        {
            net += dsu._count_jumps_to_find_parent_of(j);
        }
        cout<<i<<": "<<net<<endl;
    }
}

int main()
{
    test_simple_fast_dsu_performance();
    return 0;
}
