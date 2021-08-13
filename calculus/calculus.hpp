#pragma once
#include <vector>
#include "../algebra/linear_eq.hpp"
#include "../number_theory/math_constants.hpp"

typedef long long ll;

template<typename R>
R fractional_part(R x,double _EPSILON = 1e-4)
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

    if (std::abs(x_c - x) <= _EPSILON || std::abs(x_f - x) <= _EPSILON || std::abs(x-x_s)<=_EPSILON || std::abs(x-x_sc)<=_EPSILON || std::abs(x-x_sf)<=_EPSILON || std::abs(x-x_ssf)<=_EPSILON || std::abs(x-x_ssc)<=_EPSILON)
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
R integral_part(R x,double _EPSILON = 1e-4)
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

    if(std::abs(x)<=_EPSILON)
    {
        return 0;
    }

    if (std::abs(x_f - x) <= _EPSILON)
    {
        return x_f;
    }

    if (std::abs(x_c - x) <= _EPSILON)
    {
        return x_c;
    }

    if (std::abs(x_sc - x) <= _EPSILON)
    {
        return x_sc;
    }

    if (std::abs(x_sf - x) <= _EPSILON)
    {
        return x_sf;
    }

    if (std::abs(x_s - x) <= _EPSILON)
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
std::vector<R> add_poly(std::vector<R> &x, std::vector<R> &y)
{
    std::vector<R> xpy;
    int i;
    for (i = 0; i < std::min(x.size(), y.size()); i++)
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

namespace calculus
{
    template <typename R>
    R nroot(R a, R r, R EPS = 1e-6, int itrr = 50)
    {
        if (std::abs(a) < EPS)
        {
            return 0.0;
        }
        R xr = 2.0;
        R xn = 1.0;
        while (itrr > 0 && std::abs(xn - xr) > EPS)
        {
            xn = xr;
            xr = xr * (1 - (1 / r)) + (a / r) / pow(xr, r - 1);
            itrr--;
        }

        return xr;
    }

    template <typename R>
    R compute_polynomial(std::vector<R> &a, R x)
    {
        int n = (int)a.size();
        if (n < 1)
            return 0.0;

        R val = a[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            val *= x;
            val += a[i];
        }

        return val;
    }

    // template <typename R>
    // std::vector<R> poly_root(std::vector<R> a,R EPS = 1e-6)
    // {
    //     int n = (int)a.size() - 1;
    //     int mxdeg = n;
    //     while (mxdeg >= 0)
    //     {
    //         if (std::abs(a[mxdeg]) > EPS)
    //             break;
    //         mxdeg--;
    //     }
    //     R mxrange = 0;
    //     for (int i = mxdeg - 1; i >= 0; i--)
    //     {
    //         a[i] /= a[mxdeg];
    //         mxrange = max(mxrange, std::abs(a[i]));
    //     }
    //     a[mxdeg] = (R)1.0;
    //     mxrange += 1.0;
    // }

    template <typename R, typename I>
    R integrate_trapezoidal(R (*f)(R), R a, R b, I n)
    {
        n = std::max((I)2, n);
        R h = (b - a) / ((R)n);

        R ans = (f(a) + f(b)) / 2;

        for (I i = 1; i < n; i++)
        {
            ans += f(a + h * i);
        }

        ans *= h;
        return ans;
    }

    template <typename R, typename I>
    R integrate_simpson(R (*f)(R), R a, R b, I n)
    {
        n = (n / 2) * 2;
        n = std::max(n, (I)2);
        R h = (b - a) / ((R)n);

        R ans = (f(a) + f(b));

        std::vector<R> coeff(2);
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

    template <typename R, typename I>
    R integrate_simpson38(R (*f)(R), R a, R b, I n)
    {
        n = (n / 3) * 3;
        n = std::max(n, (I)3);
        R h = (b - a) / ((R)n);

        R ans = (f(a) + f(b));

        std::vector<R> coeff(3);
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

    template <typename R>
    R differentate2(R (*f)(R), R x, R h)
    {
        return (f(x + h) - f(x - h)) / (2.0 * h);
    }

    template <typename R, typename I>
    R differentate2_n(R (*fl)(R), R x, R h, I n)
    {
        if (n <= 0)
        {
            return fl(x);
        }
        std::vector<R> vf;
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

    template <typename R>
    R differentate4(R (*f)(R), R x, R h)
    {
        return (f(x - 2.0 * h) + 8.0 * f(x + h) - 8.0 * f(x - h) - f(x + 2.0 * h)) / (12.0 * h);
    }

    template <typename R, typename I=int>
    R find_zero(R (*f)(R), R low, R high,R EPS = 1e-6,I itter = 50)
    {
        R flow = f(low), fhigh = f(high);
        R mid = (low + high) / 2;
        while (--itter)
        {
            mid = (low + high) / 2;
            R fmid = f(mid);
            if (std::abs(fmid) < EPS)
                return mid;

            if (fmid * flow > (R)0.0)
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

    template <typename R>
    std::vector<R> interpolate(std::vector<R> &x, std::vector<R> &y)
    {
        int n = y.size();
        linear_eq<R> le(n, n);
        for (int i = 0; i < n; i++)
        {
            le.A[i][0] = 1;
            for (int j = 1; j < n; j++)
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
    template <typename R, typename I>
    std::vector<R> taylor_series(R (*fl)(R), R a, R h, I deg)
    {
        std::vector<R> vf,coeff;
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
