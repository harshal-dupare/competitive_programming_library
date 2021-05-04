#include <bits/stdc++.h>

#include "utils/debug_out.h"

// namespaces starts
using namespace std;
// namespaces ends

typedef long long ll;

double _EPSILON = 1e-4;


template<typename R>
R fractional_part(R x)
{
    R x_ssc = (R)(((ll)(x)) + 3ll);
    R x_sc = (R)(((ll)(x)) + 2ll);
    R x_c = (R)(((ll)(x)) + 1ll);
    R x_f = (R)((ll)(x));
    R x_s = (R)(((ll)(x)) - 1ll);
    R x_sf = (R)(((ll)(x)) - 2ll);
    R x_ssf = (R)(((ll)(x)) - 3ll);

    for(ll i=-2;i<3;i++)
    {
        R x_i = (R)(i);
        if(x==x_i+_EPSILON||x==x_i-_EPSILON)
        {
            return 0;
        }
    }

    if (abs(x_c - x) <= _EPSILON || abs(x_f - x) <= _EPSILON || abs(x-x_s)<=_EPSILON || abs(x-x_sc)<=_EPSILON || abs(x-x_sf)<=_EPSILON || abs(x-x_ssf)<=_EPSILON || abs(x-x_ssc)<=_EPSILON)
    {
        return 0;
    }

    if (x < 0)
    {
        return 1 - x_f + x;
    }
    else
    {
        return x - x_f;
    }

    return 0;
}

template<typename R>
R integral_part(R x)
{
    R x_sc = (R)(((ll)(x)) + 2ll);
    R x_c = (R)(((ll)(x)) + 1ll);
    R x_f = (R)((ll)(x));
    R x_s = (R)(((ll)(x)) - 1ll);
    R x_sf = (R)(((ll)(x)) - 2ll);

    for(ll i=-2;i<3;i++)
    {
        R x_i = (R)(i);
        if(x==x_i+_EPSILON||x==x_i-_EPSILON)
        {
            return x_i;
        }
    }

    // cout<<x_c<<":"<<x_f<<endl;
    if(abs(x)<=_EPSILON)
    {
        return 0;
    }

    if (abs(x_f - x) <= _EPSILON)
    {
        return x_f;
    }

    if (abs(x_c - x) <= _EPSILON)
    {
        return x_c;
    }

    if (abs(x_sc - x) <= _EPSILON)
    {
        return x_sc;
    }

    if (abs(x_sf - x) <= _EPSILON)
    {
        return x_sf;
    }

    if (abs(x_s - x) <= _EPSILON)
    {
        return x_s;
    }

    if (x > 0)
    {
        return x_f;
    }
    else if (x < 0)
    {
        return x_f - 1;
    }

    return 0;
}

template <typename R>
struct linear_eq
{
    vector<vector<R>> A;
    vector<R> B;
    vector<ll> xids;
    ll n_eq;
    ll n_var;
    R EPS = 1e-6;
    R _pEPS = 1e-9;
    R ninf = -1e20;

    linear_eq(ll _n_eq, ll _n_var)
    {
        this->n_eq = _n_eq;
        this->n_var = _n_var;
        this->A.assign(_n_eq, vector<R>(_n_var, (R)0));
        this->B.assign(_n_var, 0);
        this->xids.assign(_n_var, 0);
    }

    void rswap(ll i, ll j)
    {
        vector<R> tp = this->A[j];
        this->A[j] = this->A[i];
        this->A[i] = tp;

        R btp = this->B[j];
        this->B[j] = this->B[i];
        this->B[i] = btp;
    }

    // R[i]<-R[i]-C*R[j]
    void r_reduce(ll i, ll j, R C)
    {
        for (ll k = 0; k < this->n_var; k++)
        {
            this->A[i][k] -= this->A[j][k] * C;
        }
        this->B[i] -= this->B[j] * C;
    }

    void scale(ll j, R C)
    {
        for (ll i = 0; i < n_var; i++)
        {
            this->A[j][i] /= C;
        }
        this->B[j] /= C;
    }

    bool row_echilon_form(bool reduced = false)
    {
        bool full_rank = true;
        for (ll i = 0; i < min(n_eq, n_var); i++)
        {
            ll mxid = -1;
            R mxv = 0;
            for (ll j = i; j < n_eq; j++)
            {
                if (abs(this->A[j][i]) >= mxv)
                {
                    mxid = j;
                    mxv = abs(this->A[j][i]);
                }
            }

            if (mxv < EPS)
            {
                full_rank = false;
                continue;
            }

            if (mxid != i)
                this->rswap(mxid, i);

            for (ll j = i + 1; j < n_eq; j++)
            {
                this->r_reduce(j, i, this->A[j][i] / this->A[i][i]);
            }

            if (reduced)
            {
                this->scale(i, this->A[i][i]);
            }
        }

        return full_rank;
    }

    bool gauss_elemination(bool reduce = false)
    {
        bool full_rank = true;
        for (ll i = 0; i < min(n_eq, n_var); i++)
        {
            ll mxid = -1;
            R mxv = 0;
            for (ll j = i; j < n_eq; j++)
            {
                if (abs(this->A[j][i]) >= mxv)
                {
                    mxid = j;
                    mxv = abs(this->A[j][i]);
                }
            }

            if (mxv < EPS)
            {
                full_rank = false;
                continue;
            }
            // debug(mxv);
            // debug(mxid);
            // debug(i);
            if (mxid != i)
                this->rswap(mxid, i);

            for (ll j = 0; j < n_eq; j++)
            {
                if (j != i)
                {
                    this->r_reduce(j, i, this->A[j][i] / this->A[i][i]);
                }
            }

            if (reduce)
            {
                this->scale(i, this->A[i][i]);
            }
        }

        return full_rank;
    }

    friend ostream &operator<<(ostream &os, linear_eq &le)
    {
        for (ll i = 0; i < le.n_eq; i++)
        {
            os << "[ ";
            for (ll j = 0; j < le.n_var; j++)
            {
                os << le.A[i][j] << " ";
            }
            os << " | " << le.B[i];
            os << " ]\n";
        }

        return os;
    }
};

template <typename R>
vector<R> add_poly(vector<R> &x, vector<R> &y)
{
    vector<R> xpy;
    ll i;
    for (i = 0; i < min(x.size(), y.size()); i++)
    {
        xpy.push_back(x[i] + y[i]);
    }
    while (i < y.size())
    {
        xpy.push_back(y[i]);
        i++;
    }
    while (i < x.size())
    {
        xpy.push_back(x[i]);
        i++;
    }
    return xpy;
}

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

    R differentate2_n(R (*fl)(R), R x, R h, I n)
    {
        if (n <= 0)
        {
            return fl(x);
        }
        vector<R> vf;
        for (I i = -n; i < n + 1; i++)
        {
            vf.push_back(fl(x + i * h));
        }
        /*

        -4 -3 -2 -1  0 1 2 3 4
         \  \ / \ /

        */
        I lim = 2 * n - 2;
        R temp = 0;
        while (lim >= 0)
        {
            for (I i = 0; i <= lim; i++)
            {
                vf[i] = (vf[i + 2] - vf[i]) / (2.0 * h);
            }
            lim -= 2;
        }

        return vf[0];
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
                low = mid;
                flow = fmid;
            }
            else
            {
                high = mid;
                fhigh = fmid;
            }
        }

        return mid;
    }

    vector<R> interpolate(vector<R> &x, vector<R> &y)
    {
        ll n = y.size();
        linear_eq<R> le(n, n);
        for (ll i = 0; i < n; i++)
        {
            le.A[i][0] = 1;
            for (ll j = 1; j < n; j++)
            {
                le.A[i][j] = x[i] * le.A[i][j - 1];
            }
            le.B[i] = y[i];
        }

        bool working = le.gauss_elemination(true);

        return le.B;
    }

    // very sensitive to small h values as accuracy gets lost in small precision, cant be propogated beyond 2-3 degree
    // use large enough h value so as to not be distrubed by precission loss
    vector<R> taylor_series(R (*fl)(R), R a, R h, I deg)
    {
        vector<R> vf,coeff;
        for (I i = -deg; i < deg + 1; i++)
        {
            vf.push_back(fl(a + i * h));
        }

        I id = deg;
        coeff.push_back(vf[id]);
        I lim = 2 * deg - 2;
        while (lim >= 0)
        {
            for (I i = 0; i <= lim; i++)
            {
                vf[i] = (vf[i + 2] - vf[i]) / ((2.0*deg-lim) * h  );
            }
            lim -= 2;
            id-=1;
            
            coeff.push_back(vf[id]);
        }

        return coeff;
    }
};

// tests

double f(double x)
{
    return sin(x);
    return x * x * x * x * x;
    return tanh(3.1415926535 * 3.0 * x) / (x * x * x + x);
}

double p(double x)
{
    return x * x + 3 * x + 5;
}

void test_diff()
{
    double h = 1e-5;
    calculus<ll, double> cal;
    ll n = 5;
    vector<double> diff;
    for (ll i = 0; i < n; i++)
    {
        // auto f = [&](double x) { return tanh(3.1415926535 * 3.0 * x) / (x * x * x + x); };
        diff.push_back(cal.differentate2_n(f, 1.0, h, i));
    }
    debug(diff);
}

void test_taylor_series()
{
    double h = 1e-2;
    calculus<ll, double> cal;
    ll n = 9;
    vector<double> coeff = cal.taylor_series(f,0,h,n);
    debug(coeff);
}

void test_integration()
{
    ll prec = 10;
    double h = 1e-3;
    calculus<ll, double> cal;

    // cout << fixed << setprecision(prec) << cal.integrate_trapezoidal(f, 0.0001, 20000, 10000) << endl;
    // cout << fixed << setprecision(prec) << cal.integrate_simpson(f, 0.001, 20000, 10000) << endl;
    cout << fixed << setprecision(prec) << cal.integrate_simpson38(f, 0.001, 20000, 100000000) << endl;

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

    calculus<ll, double> cal;

    auto coeff = cal.interpolate(x, y);
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

int main()
{
    // test_interpolation();
    // test_liner();
    // test_diff();
    test_taylor_series();
    return 0;
}
