#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../suffix_tree.hpp"
using namespace std;

typedef long long ll;
typedef double R;

void test_suffix_tree()
{
    tree<ll> sft;

    ll n;
    cin >> n;
    vector<string> vs(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> vs[i];
    }

    sft.construct(vs);
    sft.print();

}

int main()
{
    return 0;
}