#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/data_structure/sqrt_decomposition.hpp"
using namespace std;

typedef long long ll;
typedef double R;


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


int main()
{
    return 0;
}