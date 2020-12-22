#include <bits/stdc++.h>

// namespaces starts
using namespace std;
// namespaces ends

#define ll long long

template <typename I, typename R>
class calculus
{
public:
    R EPS = 1e-6;
    I itr = 50;
    long double PI = 3.14159265358979324l;
    long double E = 2.71828182845904524l;
    long double gamma = 0.577215664901533l;

    calculus()
    {
    }

    calculus(R EPS)
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

    R compute_polynomial(vector<R> &a, R x)
    {
        if (a.size() < 1)
            return 0.0;

        R val = a[a.size() - 1];
        for (I i = a.size() - 2; i >= 0; i--)
        {
            val *= x;
            val += a[i];
        }

        return val;
    }

    vector<R> poly_root(vector<R> a)
    {
        I n = a.size() - 1;
        I mxdeg = n;
        while (mxdeg >= 0)
        {
            if (abs(a[mxdeg]) > this->EPS)
                break;
            mxdeg--;
        }

        R mxrange = 0;
        for (I i = mxdeg - 1; i >= 0; i--)
        {
            a[i] /= a[mxdeg];
            mxrange = max(mxrange, abs(a[i]));
        }
        a[mxdeg] = (R)1.0;
        mxrange += 1.0;
    }

    R integrate_trapezoidal(R (*f)(R), R a, R b, I n)
    {
        n = max((I)2, n);
        R h = (b - a) / ((R)n);

        R ans = (f(a) + f(b)) / 2;

        for (I i = 1; i < n; i++)
        {
            ans += f(a + h * i);
        }

        ans *= h;
        return ans;
    }

    R integrate_simpson(R (*f)(R), R a, R b, I n)
    {
        n = (n / 2) * 2;
        n = max(n, (I)2);
        R h = (b - a) / ((R)n);

        R ans = (f(a) + f(b));

        vector<R> coeff(2);
        coeff[0] = 2.0;
        coeff[1] = 4.0;
        for (I i = 1; i < n; i++)
        {
            ans += coeff[(i % 2)] * f(a + h * i);
        }

        ans *= h;
        ans /= 3.0;

        return ans;
    }

    R integrate_simpson38(R (*f)(R), R a, R b, I n)
    {
        n = (n / 3) * 3;
        n = max(n, (I)3);
        R h = (b - a) / ((R)n);

        R ans = (f(a) + f(b));

        vector<R> coeff(3);
        coeff[0] = 2.0;
        coeff[1] = 3.0;
        coeff[2] = 3.0;
        for (I i = 1; i < n; i++)
        {
            ans += coeff[(i % 3)] * f(a + h * i);
        }

        ans *= h;
        ans *= (R)(0.375);

        return ans;
    }

    R differentate2(R (*f)(R), R x, R h)
    {
        return (f(x + h) - f(x - h)) / (2.0 * h);
    }

    R differentate4(R (*f)(R), R x, R h)
    {
        return (f(x - 2.0 * h) + 8.0 * f(x + h) - 8.0 * f(x - h) - f(x + 2.0 * h)) / (12.0 * h);
    }

    R find_zero(R (*f)(R), R low, R high)
    {
        I itter = this->itr;
        R flow = f(low), fhigh = f(high);
        R mid = (low + high) / 2;
        while (--itter)
        {
            mid = (low + high) / 2;
            R fmid = f(mid);
            if (abs(fmid) < this->EPS)
                return mid;

            if (fmid * flow > 0)
            {
                low=mid;
                flow=fmid;
            }
            else
            {
                high=mid;
                fhigh=fmid;
            }
        }

        return mid;
    }

};

double f(double x)
{
    return tanh(3.1415926535 * 3.0 * x) / (x * x * x + x);
}

int main()
{

    ll prec = 10;
    double h = 1e-3;
    calculus<ll, double> cal;

    // cout << fixed << setprecision(prec) << cal.integrate_trapezoidal(f, 0.0001, 20000, 10000) << endl;
    // cout << fixed << setprecision(prec) << cal.integrate_simpson(f, 0.001, 20000, 10000) << endl;
    cout << fixed << setprecision(prec) << cal.integrate_simpson38(f, 0.001, 20000, 100000000) << endl;

    // cout << fixed << setprecision(prec) << cal.differentate2(f, 2, h) << endl;
    // cout << fixed << setprecision(prec) << cal.differentate4(f, 2, h) << endl;

    return 0;
}
