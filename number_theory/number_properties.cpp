#include <bits/stdc++.h>
#include "../utils/timer.h"

using namespace std;

template <typename I>
class number_properties
{
public:
    I gcd(I n, I m)
    {
        n = abs(n);
        m = abs(m);
        while (m > 0)
        {
            I temp = m;
            m = n % m;
            n = temp;
            // tie(n, m) = make_pair(m, n % m);
        }

        return n;
    }

    I extended_gcd(I n, I n0, I &x, I &y)
    {
        x = 1;
        y = 0;
        I xp = 0, yp = 1;

        // n  - n0*k = n1
        // n0 - n1*x1=n2
        // n1 - n2*x2=n3
        while (n0 > 0)
        {
            I k = n / n0;
            tie(x, xp) = make_pair(xp, x - k * xp);
            tie(y, yp) = make_pair(yp, y - k * yp);
            tie(n, n0) = make_pair(n0, n % n0);
        }

        return n;
    }

    I gcd_set(vector<I> &s)
    {
        ans = 1;
        for (auto x : s)
        {
            ans = gcd(x, ans);
            if (ans == 1)
                return;
        }

        return ans;
    }

    I frobenius(vector<I> &nl)
    {
        if (nl.size() < 2 || this->gcd_set(nl) != 1)
            return -1;
        if (nl.size() == 2)
        {
            return 
        }
    }
};

int main()
{
    number_properties<int> np;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        int x, y;
        int g = np.extended_gcd(a, b, x, y);
        cout << a << "*(" << x << ") + (" << y << ")*" << b << " = " << g << endl;
    }

    return 0;
}
