#include <bits/stdc++.h>
#include "../utils/debug_out.h"

// namespaces starts
using namespace std;
// namespaces ends
typedef long long int ll;

template <typename I, typename R>
class algebra
{
public:
    R EPS = 1e-6;
    I itr = 50;

    I power(I a, I n)
    {
        I t = 1;
        while (n > 0)
        {
            if (n & 1 > 0)
            {
                t *= a;
            }
            n >>= 1;
            a *= a;
        }
        return t;
    }

    algebra(R EPS = 1e-6)
    {
        this->EPS = EPS;
    }

    // return a^(1/r) if its an integer O(log(a)*POW(r))
    R nroot(R a, R r)
    {
        if (abs(a) < this->EPS)
        {
            return 0.0;
        }
        I itrr = this->itr;
        R xr = 2.0;
        R xn = 1.0;
        while (itrr > 0 && abs(xn - xr) > this->EPS)
        {
            xn = xr;
            xr = xr * (1 - (1 / r)) + (a / r) / pow(xr, r - 1);
            itrr--;
        }

        return xr;
    }

    // return a^(1/n) if its an integer O(2err*long(n)+)
    I inroot(I a, I n, I err = 3)
    {
        R ra = (R)a, rn = (R)n;
        I est = I(this->nroot(ra, rn));
        
        for (I k = est-err; k < est+err + 1; k++)
        {
            if (a == this->power(k, n))
            {
                return k;
            }
        }

        return 0;
    }

    I sqt(I n)
    {
        if (n == 0)
            return 0;
        I dl = 1;
        I dr = n;
        while (dl < dr)
        {
            I mid = (dr + dl) / 2;
            if (mid * mid < n)
            {
                dl = mid + 1;
            }
            else
            {
                dr = mid;
            }
        }

        return dl;
    }

    
};

void test_iroot()
{
    algebra<ll, double> a;
    ll lim = 1000;
    for (ll i = -lim ; i < lim+1; i++)
    {
        if(a.inroot(i,2)!=0)
            cout << i << ": " << a.inroot(i,2) << endl;
    }
}

int main()
{
    test_iroot();
    return 0;
}
