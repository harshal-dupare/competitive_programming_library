#pragma once

#include<vector>
#include<complex>

namespace roots
{
    template <typename I>
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

    // return a^(1/r) if its an integer O(log(a)*POW(r))
    template <typename R=double, typename I=long>
    R nroot(R a, R r,R EPS = 1e-6,I itr = 50)
    {
        if (std::abs(a) < EPS)
        {
            return 0.0;
        }
        I itrr = itr;
        R xr = 2.0;
        R xn = 1.0;
        while (itrr > 0 && std::abs(xn - xr) > EPS)
        {
            xn = xr;
            xr = xr * (1 - (1 / r)) + (a / r) / std::pow(xr, r - 1);
            itrr--;
        }

        return xr;
    }

    // return a^(1/n) if its an integer O(log(a)*log(n))
    // use bin search insted and if root doesnt exist returns 0
    template <typename I>
    I inroot(I a, I n)
    {
        I l=1,r=a;
        I sgn=1;
        if(a<(I)0&&n%2==1)
        {
            sgn=-1;
            r=-a;
            a=r;
        }
        I ra=0;
        if(a==1)
        {
            ra=1;
        }
        while (l<r)
        {
            // std::cerr<<l<<","<<r<<"\n";
            I mid = l+(r-l)/2;
            I tn = n-1;
            ra=a;
            while(tn--)
            {
                ra/=mid;
            }
            if(ra==mid)
            {
                // std::cerr<<ra<<":"<<roots::power<I>(mid,n-1)<<"\n";
                if(a==ra*roots::power<I>(mid,n-1))
                {
                    // std::cerr<<"c11\n";
                    l=r=mid;
                    ra=mid;
                }
                else
                {
                    // std::cerr<<"c12\n";
                    l=r=mid;
                    ra=0;
                }
                break;
            }
            if(ra<mid)
            {
                // std::cerr<<"c2\n";
                r=mid-1;
            }
            else
            {
                // std::cerr<<"c3\n";
                l=mid+1;
            }
            ra=0;
        }
        ra=sgn*ra;
        return ra;
    }

    template <typename I>
    I sqt(I n)
    {
        return roots::inroot<I>(n,(I)2);
    }

    template <typename R>
    std::vector<R> quadratic_roots(R a0, R a1, R a2)
    {
        a1 /= a2;
        a0 /= a2;
        R det = a1 * a1 - (R)4.0 * a0;
        std::vector<R> ans(4,(R)0);
        if (det < 0)
        {
            det = std::sqrt(std::abs(det));
            ans[0] = (-a1) / (2.0);
            ans[1] = (det) / (2.0);
            ans[2] = ans[0];
            ans[3] = -ans[1];
        }
        else
        {
            det = std::sqrt(det);
            ans[0] = (-a1 + det) / (2.0);
            ans[2] = (-a1 - det) / (2.0);
        }

        return ans;
    }

    template <typename R>
    std::vector<R> cubic_roots(R a0, R a1, R a2, R a3,R EPS = 1e-6)
    {
        a2 /= (3.0*a3);
        a1 /= a3;
        a0 /= a3;
        std::vector<R> ans;
        R b1 = (a1 - 3.0 * a2 * a2) / (3.0);
        R b0 = (2.0 * a2 * a2 * a2 - a1 * a2 + a0) / (2.0);
        R det = b1 * b1 * b1 + b0 * b0;
        std::vector<std::complex<R>> cans(3);
        std::complex<R> cb0(b0, 0), cb1(b1, 0), cb;
        std::complex<R> w(-0.5, 0.5 * std::sqrt(3));
        if (det < 0)
        {
            cb = std::complex<R>(b0, std::sqrt(std::abs(det)));
        }
        else
        {
            cb = std::complex<R>(b0 + std::sqrt(std::abs(det)), 0);
        }
        std::complex<R> beta = pow(cb, std::complex<R>((R)1.0 / 3.0, 0)), alpha(0,0);
        if(std::abs(beta)>EPS) alpha = std::complex<R>(b1, (R)0) / beta;
        cans[0] = alpha - beta;
        cans[1] = alpha * w - beta * w * w;
        cans[2] = alpha * w * w - beta * w;

        for (int i = 0; i < 6; i++)
        {
            if (i % 2 == 0)
                ans.push_back(cans[(i / 2)].real()-a2);
            else
                ans.push_back(cans[(i / 2)].imag());

        }

        return ans;
    }

    template <typename R>
    std::vector<R> quartic_roots(R a0, R a1, R a2, R a3, R a4)
    {
        // x^4+2ax^3+bx^2+2cx+d = (x^2+ax+A)^2-(Bx+C)^2
        // expand and equal coeff sole for A , then uisng cubic get A
        // (A-a1)^2 = (2A+a3^2-a2)(A^2-a0)
        // 0=2A^3+(a3^2-a2-1)A^2+2(a1-a0)A-(a3^2-a2)a0-a1^2
        a3 /= (2.0*a4);
        a2 /= a4;
        a1 /= (2.0*a4);
        a0 /= a4;
        R a3r2ma2 = a3*a3-a2;
        std::vector<R> cbans = cubic_roots(-a1*a1-a0*(a3r2ma2),2.0*(a1-a0),a3r2ma2-1,2.0);
        std::complex<R> A(cbans[0],cbans[1]);
        std::complex<R> B=std::sqrt(2.0*A+a3r2ma2);
        std::complex<R> C=std::sqrt(A*A-a0);
        debug(A); 

        std::complex<R> qc=A+C,qb=B+a3,qa=1;
        std::vector<std::complex<R>> cans;
        cans.push_back((-qb-std::sqrt(qb*qb-4.0*qa*qc))/(2.0*qa));
        cans.push_back((-qb+std::sqrt(qb*qb-4.0*qa*qc))/(2.0*qa));
        qc=A-C;
        qb=a3-B;
        qa=1;
        cans.push_back((-qb-std::sqrt(qb*qb-4.0*qa*qc))/(2.0*qa));
        cans.push_back((-qb+std::sqrt(qb*qb-4.0*qa*qc))/(2.0*qa));

        std::vector<R> ans;
        for (int i = 0; i < 8; i++)
        {
            if (i % 2 == 0)
                ans.push_back(cans[(i / 2)].real());
            else
                ans.push_back(cans[(i / 2)].imag());

        }

        return ans;
    }

};


/*
(a0,....,an) = (c0,c1,1)*(b0,...,bn-2) + (k0,k1)

a(i) = b(i)*c(0)+b(i-1)*c(1)+b(i-2)
k(0),k(1)=0
c(0)*b(0)=a(0)
c(1)*b(0)+b(1)*c(0)=a(1)
*/