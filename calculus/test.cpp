#include <bits/stdc++.h>

#include "../utils/debug_out.hpp"
#include "../utils/timer.hpp"
#include "../algebra/linear_eq.hpp"
#include "../number_theory/math_constants.hpp"

#include "calculus.hpp"

using namespace std;

typedef long long ll;
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}

double f(double x)
{
    return sin(x);
    return x * x * x * x * x;
    return tanh(math_constants::pi * 3.0 * x) / (x * x * x + x);
}

double p(double x)
{
    return x * x + 3 * x + 5;
}

void test_diff()
{
    double h = 1e-5;
    ll n = 5;
    vector<double> diff;
    for (ll i = 0; i < n; i++)
    {
        // auto f = [&](double x) { return tanh(3.1415926535 * 3.0 * x) / (x * x * x + x); };
        diff.push_back(calculus::differentate2_n<double,ll>(f, 1.0, h, i));
    }
    debug(diff);
}

void test_taylor_series()
{
    double h = 1e-2;
    ll n = 9;
    vector<double> coeff = calculus::taylor_series<double,ll>(f,0,h,n);
    debug(coeff);
}

void test_integration()
{
    ll prec = 10;
    double h = 1e-3;

    // cout << fixed << setprecision(prec) << cal.integrate_trapezoidal(f, 0.0001, 20000, 10000) << endl;
    // cout << fixed << setprecision(prec) << cal.integrate_simpson(f, 0.001, 20000, 10000) << endl;
    cout << fixed << setprecision(prec) << calculus::integrate_simpson38<double,ll>(f, 0.001, 20000, 100000000) << endl;

    // cout << fixed << setprecision(prec) << cal.differentate2(f, 2, h) << endl;
    // cout << fixed << setprecision(prec) << cal.differentate4(f, 2, h) << endl;
}

void test_interpolation()
{
    vector<double> x = {1, 2, 3};
    vector<double> y;
    for (auto xi : x)
    {
        y.push_back(p(xi));
    }

    auto coeff = calculus::interpolate<double>(x, y);
}

void test_liner()
{
    ll n = 1 + (abs(rand())) % 300;
    default_random_engine generator;
    uniform_real_distribution<double> distribution(-100.0, 100.0);

    ll mxitr = 300;
    vector<double> err(mxitr, 0);
    while (mxitr--)
    {

        linear_eq<double> le(n, n);

        vector<double> x(n);
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                le.A[i][j] = distribution(generator);
            }
            x[i] = distribution(generator);
        }

        for (ll i = 0; i < n; i++)
        {
            le.B[i] = 0;
            for (ll j = 0; j < n; j++)
            {
                le.B[i] += le.A[i][j] * x[j];
            }
        }

        le.gauss_elemination(true);

        for (ll i = 0; i < n; i++)
        {
            err[mxitr - 1] += abs(le.B[i] - x[i]);
        }
    }

    double nerr = accumulate(err.begin(), err.end(), 0);
}

void test()
{
    ll n;
    cin>>n;
    for(ll i=2;i<=n;i++)
    {
        for(ll j=1;j<i;j++)
        {
            if(__gcd(i,j)!=1) continue;
            mdebug(j,i,inverse<ll>(j,i));
        }
    }
}

int main()
{
    // test_interpolation();
    // test_liner();
    // test_diff();
    // test_taylor_series();
    return 0;
}
