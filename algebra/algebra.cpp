#include <bits/stdc++.h>

// namespaces starts
using namespace std;
// namespaces ends

template <typename I, typename R>
class algebra
{
public:
    R EPS = 1e-6;
    I itr = 50;

    algebra(R EPS = 1e-6)
    {
        this->EPS = EPS;
    }

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

int main()
{

    return 0;
}

