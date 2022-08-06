#include <bits/stdc++.h>
#include "../../lib/utils/timer.hpp"
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/data_structure/binary_indexed_tree.hpp"

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
    cout<<bit2;
    for (int i = 0; i < n; i++)
    {
        cout << bit2.get(i) << ", ";
    }
    cout << endl;

    bit2.update(3, 4, 4);
    cout<<bit2;

}

int main()
{
    return 0;
}