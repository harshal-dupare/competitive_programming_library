#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/data_structure/trie.hpp"
using namespace std;

typedef long long ll;
typedef double R;

void test_trie()
{
    ll n;
    cin >> n;
    vector<string> vs(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> vs[i];
    }
    trie<ll> tr;
    tr.construct(vs);
    tr.print();
    string s;
    tr.sorted_print(0,s);
}

int main()
{
    return 0;
}