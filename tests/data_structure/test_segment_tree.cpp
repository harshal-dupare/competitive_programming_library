#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/data_structure/segment_tree.hpp"
using namespace std;

typedef long long ll;
typedef double R;

void test_seg_tree()
{
    ll n;
    cin >> n;
    segment_heap<ll> sh(n);
    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sh.compute(a);

    while (true)
    {
        int c;
        int x, y;
        cin >> c;
        if (c == 0)
        {
            cin >> x >> y;
            ll ans = sh.query(x, y);
            cout << ans << "\n";
        }
        if (c == 1)
        {
            cin >> x >> y;
            sh.update(x, y);
            sh.print();
        }
        if (c == 2)
        {
            sh.print();
        }
        if (c == 3)
        {
            break;
        }
    }

}

int main()
{
    return 0;
}