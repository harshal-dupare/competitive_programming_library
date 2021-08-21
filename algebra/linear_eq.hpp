#pragma once
#include <vector>
#include <complex>
#include <iostream>

template<typename R>
struct linear_eq
{
    std::vector<std::vector<R>> A;
    std::vector<R> B;
    std::vector<long long> xids;
    long long n_eq;
    long long n_var;
    R EPS = 1e-6;
    R _pEPS = 1e-9;
    R ninf = -1e20;

    linear_eq(long long _n_eq, long long _n_var)
    {
        this->n_eq = _n_eq;
        this->n_var = _n_var;
        this->A.assign(_n_eq, std::vector<R>(_n_var, (R)0));
        this->B.assign(_n_var, 0);
        this->xids.assign(_n_var, 0);
    }

    void rswap(long long i, long long j)
    {
        std::vector<R> tp = this->A[j];
        this->A[j] = this->A[i];
        this->A[i] = tp;

        R btp = this->B[j];
        this->B[j] = this->B[i];
        this->B[i] = btp;
    }

    // R[i]<-R[i]-C*R[j]
    void r_reduce(long long i, long long j, R C)
    {
        for (long long k = 0; k < this->n_var; k++)
        {
            this->A[i][k] -= this->A[j][k] * C;
        }
        this->B[i] -= this->B[j] * C;
    }

    void scale(long long j, R C)
    {
        for (long long i = 0; i < n_var; i++)
        {
            this->A[j][i] /= C;
        }
        this->B[j] /= C;
    }

    void input()
    {
        std::cout << "for each next " << this->n_eq << " rows input " << this->n_var + 1 << " space separtaed numbers in the format :\na[i][1] a[i][2] .. a[i][n] b[i]\n";
        for (long long i = 0; i < n_eq; i++)
        {
            for (long long j = 0; j < n_var; j++)
            {
                std::cin >> this->A[i][j];
            }
            std::cin >> this->B[i];
        }
    }

    void gauss_seidel_itr(long long n, std::vector<std::vector<R>> &A, std::vector<R> &B, std::vector<R> &x)
    {
        for (long long i = 0; i < n; i++)
        {
            x[i] = B[i];
            for (long long j = 0; j < n; j++)
            {
                if (i != j)
                {
                    x[i] -= A[i][j] * x[j];
                }
            }
            x[i] /= A[i][i];
        }
    }

    bool gauss_seidel(long long k, std::vector<R> &x)
    {
        x.resize(this->n_eq, 0);
        for (long long i = 0; i < this->n_eq; i++)
            x[i] = 0;

        double err = 1;
        std::vector<R> xl = x;

        while (k > 0 && err > EPS)
        {
            gauss_seidel_itr(this->n_eq, A, B, x);
            err = 0;
            for (long long j = 0; j < this->n_eq; j++)
            {
                err += std::abs(xl[j] - x[j]);
            }
            xl = x;
            k--;
        }

        double errlim = (double)this->n_var * 10.0;
        if (err > errlim)
        {
            return false;
        }
        return true;
    }

    bool row_echilon_form(bool reduced = false)
    {
        bool full_rank = true;
        for (long long i = 0; i < std::min(n_eq, n_var); i++)
        {
            long long mxid = -1;
            R mxv = 0;
            for (long long j = i; j < n_eq; j++)
            {
                if (std::abs(this->A[j][i]) >= mxv)
                {
                    mxid = j;
                    mxv = std::abs(this->A[j][i]);
                }
            }

            if (mxv < EPS)
            {
                full_rank = false;
                continue;
            }

            if (mxid != i)
                this->rswap(mxid, i);

            for (long long j = i + 1; j < n_eq; j++)
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
        for (long long i = 0; i < std::min(n_eq, n_var); i++)
        {
            long long mxid = -1;
            R mxv = 0;
            for (long long j = i; j < n_eq; j++)
            {
                if (std::abs(this->A[j][i]) >= mxv)
                {
                    mxid = j;
                    mxv = std::abs(this->A[j][i]);
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

            for (long long j = 0; j < n_eq; j++)
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

    std::pair<bool,bool> static_gauss_elemination(std::vector<R> &x , long long k,bool reduce = false)
    {
        std::pair<bool,bool> full_rank_convergence = {true,true};
        std::vector<std::vector<R>> tA=this->A;
        std::vector<R> tB=this->B;
        for (long long i = 0; i < std::min(n_eq, n_var); i++)
        {
            long long mxid = -1;
            R mxv = 0;
            for (long long j = i; j < n_eq; j++)
            {
                if (std::abs(this->A[j][i]) >= mxv)
                {
                    mxid = j;
                    mxv = std::abs(this->A[j][i]);
                }
            }

            if (mxv < EPS)
            {
                full_rank_convergence.first = false;
                continue;
            }

            if (mxid != i)
                this->rswap(mxid, i);

            for (long long j = 0; j < n_eq; j++)
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

        x = this->B;
        if(full_rank_convergence.first)
        {
            R err = 1;
            std::vector<R> xl = x;

            while (k > 0 && err > EPS)
            {
                gauss_seidel_itr(this->n_eq, tA, tB, x);
                err = 0;
                for (long long j = 0; j < this->n_eq; j++)
                {
                    err += std::abs(xl[j] - x[j]);
                }
                xl = x;
                k--;
            }

            R errlim = (R)this->n_var * 10.0;
            if (err > errlim)
            {
                full_rank_convergence.second=false;
            }
            else
            {
                full_rank_convergence.second=true;
            }
    
        }

        this->A = tA;
        this->B = tB;

        return full_rank_convergence;
    }

    friend std::ostream &operator<<(std::ostream &os, linear_eq &le)
    {
        for (long long i = 0; i < le.n_eq; i++)
        {
            os << "[ ";
            for (long long j = 0; j < le.n_var; j++)
            {
                os << le.A[i][j] << " ";
            }
            os << " | " << le.B[i];
            os << " ]\n";
        }

        return os;
    }

};

