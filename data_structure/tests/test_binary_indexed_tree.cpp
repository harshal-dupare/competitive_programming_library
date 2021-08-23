#include <bits/stdc++.h>
#include "../../utils/timer.h"
#include "../../utils/debug_out.hpp"
#include "../binary_indexed_tree.hpp"
#include "../segment_tree.hpp"
#include "../sqrt_decomposition.hpp"
#include "../sparse_table.hpp"
#include "../suffix_tree.hpp"
#include "../union_find.hpp"
#include "../trie.hpp"

using namespace std;

void test_bit()
{

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // // point update and range query
    // binary_indexed_tree_purq<int> bit(n);
    // bit.construct(a);
    // bit.print();

    // for (int i = 0; i < n; i++)
    // {
    //     cout << bit.get(i) << ", ";
    // }
    // cout << endl;

    // bit.update(3, 100, bit.a[3]);
    // bit.print();

    // // range update and point query
    // binary_indexed_tree_rupq<int> bit1(n);
    // bit1.construct(a);
    // bit1.print();

    // for (int i = 0; i < n; i++)
    // {
    //     cout << bit1.get(i) << ", ";
    // }
    // cout << endl;

    // bit1.update(3,3,4);
    // bit1.print();

    // range update and range query
    binary_indexed_tree_rurq<int> bit2(n);
    bit2.construct(a);
    bit2.print();

    for (int i = 0; i < n; i++)
    {
        cout << bit2.get(i) << ", ";
    }
    cout << endl;

    bit2.update(3, 4, 4);
    bit2.print();

}

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

void test()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sqrt_dec_rupq<int> sqd(n);
    sqd.construct(a);
    sqd.print();

    for (int i = 0; i < n; i++)
    {
        cout << sqd.get(i) << ", ";
    }
    cout << endl;

    int q;
    cin >> q;
    while (q--)
    {
        int l, r, uv;
        cin >> l >> r >> uv;
        sqd.update(l, r, uv);
        sqd.print();
        for (int i = 0; i < n; i++)
        {
            cout << sqd.get(i) << ", ";
        }
        cout << endl;
    }
}

void test_gen()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sqrt_dec_gen<int> sqd(n);
    sqd.construct(a);
    sqd.print();

    for (int i = 0; i < n; i++)
    {
        cout << sqd.point_query(i) << ", ";
    }
    cout << endl;

    int q;
    cin >> q;
    while (q--)
    {
        int c, l, r, uv;
        cin >> c;

        if (c == 0)
        {
            cin >> l >> r >> uv;
            sqd.range_update(l, r, uv);
        }
        else
        {
            cin >> l >> uv;
            sqd.point_update(l, uv);
        }
        sqd.print();

        for (int i = 0; i < n; i++)
        {
            cout << sqd.point_query(i) << ", ";
        }
        cout << endl;
    }
}

void test_old()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sqrt_dec_rupq<int> sqd(n);
    sqd.construct(a);
    sqd.print();

    for (int i = 0; i < n; i++)
    {
        cout << sqd.get(i) << ", ";
    }
    cout << endl;

    // sqd.update(3, 4, sqd.a[3]);
    sqd.update(1, 4, 7);
    sqd.print();
}

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

    return 0;
}

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
            uf.print();
        }
        if(c==2)
        {
            cin >> x >> y;
            uf.union_sets(x, y);
            uf.print();
        }
    }

}

int main()
{
    return 0;
}