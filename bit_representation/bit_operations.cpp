#include <bits/stdc++.h>

using namespace std;

template <typename I>
class bit_operations
{
public:
    // O(log(x)) time
    I msb(I n)
    {
        I m = 0;
        while (n > 0)
        {
            m++;
            n >>= 1;
        }

        return m;
    }

    // O(log(x)) time
    I lsb(I n)
    {
        I l = 0;
        while (n > 0)
        {
            l++;
            if (n & 1)
                break;
            n >>= 1;
        }
        return l;
    }
};

template <typename I>
class bit_encodings
{
public:
    I gray(I n)
    {
        return n ^ (n >> 1);
    }

    I igray(I g)
    {
        I n = 0;
        while (g)
        {
            n ^= g;
            g >>= 1;
        }
        return n;
    }
};

int beqfind(vector<int> &a, int l, int r)
{
    if (l >= r)
    {
        if (a[r] == r)
            return r;
        else
            return -1;
    }
    int m = (l + r) / 2;
    if (a[m] >= m)
        return beqfind(a, l, m);
    else
        return beqfind(a, m + 1, r);
}

int main()
{
    bit_operations<int> bo;
    bit_encodings<int> be;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        // cout << std::bitset<sizeof(i) * 8>(i) << ":" << bo.msb(i) << ", " << bo.lsb(i) << endl;
        // cout << std::bitset<sizeof(i) * 8>(i) << ": " << std::bitset<sizeof(i) * 8>(be.gray(i)) << ": " << std::bitset<sizeof(i) * 8>(be.igray(be.gray(i))) << endl;
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
        cout << a[i] << ",";
    cout << endl;
    cout << beqfind(a, 0, n - 1) << endl;

    return 0;
}