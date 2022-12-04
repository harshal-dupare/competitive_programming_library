#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "linear_programming_problem.hpp"

template <typename I, typename R>
struct big_M
{
    std::vector<std::vector<R>> a;
    std::vector<R> sol;
    std::vector<int> xids;
    std::vector<string> varname;

    int n_var, n_eq;
    int n_slc, n_srp, n_arf, n_bsc, n_nbsc, n_tot;
    int n_neg;
    int min_or_max;
    R M=(R)100;
    R EPS = 1e-9;
    R _pEPS = 1e-9;
    R ninf = -1e20;
    R inf = 1e20;

    int wd = 10;
    bool printtbl = true;

    big_M(const linear_programming_problem<I, R> &lpp, const R& _M=(R)100)
    {
        this->min_or_max = lpp.min_or_max;
        this->n_var = lpp.n_var;
        this->n_eq = lpp.n_eq;
        this->n_slc = lpp.n_slc;
        this->n_arf = lpp.n_arf;
        this->n_srp = lpp.n_srp;
        this->n_bsc = lpp.n_bsc;
        this->M = _M;

        std::vector<std::vector<int>> vtypes(3);
        for (int i = 0; i < lpp.n_var; i++)
        {
            vtypes[lpp.var_sign[i] + 1].push_back(i);
        }
        this->n_neg = (int)vtypes[1].size();
        this->n_tot = lpp.n_tot + this->n_neg;
        this->n_nbsc = lpp.n_nbsc + this->n_neg;

        assert(this->n_bsc == this->n_eq);

        this->sol.assign((int)this->n_bsc + 1, (R)0);
        for (int i = 1; i <= lpp.n_bsc; i++)
        {
            this->sol[i] = lpp.b[i - 1];
        }

        this->a.assign((int)this->n_bsc + 1, std::vector<R>((int)this->n_tot + 1, (R)0));

        this->a[0][0] = (R)1;
        for (int i = 0; i < (int)lpp.z.size(); i++)
        {
            this->a[0][i + 1] = -lpp.z[i];
        }
        for (int i = this->n_var+this->n_neg+this->n_srp+1; i <= this->n_tot-this->n_slc; i++)
        {
            this->a[0][i] = this->M;
            if(this->min_or_max==-1)
            {
                this->a[0][i] = -this->M;
            }
        }
        for (int i = 0; i < (int)lpp.a.size(); i++)
        {
            for (int j = 0; j < lpp.n_var; j++)
            {
                this->a[i + 1][j + 1] = lpp.a[i][j];
            }
        }

        this->varname.assign((int)this->n_tot + 1, string());
        this->varname[0] = "z";
        this->xids.assign((int)this->n_bsc + 1, 0);

        for (auto i : vtypes[0])
        {
            for (I j = 0; j <= this->n_eq; j++)
            {
                this->a[j][i + 1] = -this->a[j][i + 1];
            }
            this->varname[i + 1] = "-x_";
            this->varname[i + 1].append(to_string(i + 1));
        }

        for (auto i : vtypes[2])
        {
            this->varname[i + 1] = "x_";
            this->varname[i + 1].append(to_string(i + 1));
        }

        int k = this->n_var + 1;
        for (auto i : vtypes[1])
        {
            for (I j = 0; j <= this->n_eq; j++)
            {
                this->a[j][k] = -this->a[j][i + 1];
            }
            this->varname[i + 1] = "xp_";
            this->varname[i + 1].append(to_string(i + 1));
            this->varname[k] = "xn_";
            this->varname[k].append(to_string(i + 1));
            k++;
        }

        std::vector<I> v_slc, v_srp, v_arf;
        for (I i = 0; i < lpp.n_eq; i++)
        {
            if (lpp.eq_types[i] == (I)1)
            {
                // >=
                v_arf.push_back(i);
                v_srp.push_back(i);
            }
            else if (lpp.eq_types[i] == (I)0)
            {
                // ==
                v_arf.push_back(i);
            }
            else
            {
                // <=
                v_slc.push_back(i);
            }
        }
        int k0 = k;
        for (auto i : v_srp)
        {
            this->a[i + 1][k] = -((R)1);
            this->varname[k] = "srp_";
            this->varname[k].append(to_string(k - k0 + 1));
            k++;
        }
        k0 = k;
        int bscct = 1;
        for (auto i : v_arf)
        {
            this->a[i + 1][k] = (R)1;
            this->varname[k] = "arf_";
            this->varname[k].append(to_string(k - k0 + 1));
            this->xids[bscct] = k;
            k++;
            bscct++;
        }
        k0 = k;
        for (auto i : v_slc)
        {
            this->a[i + 1][k] = (R)1;
            this->varname[k] = "slc_";
            this->varname[k].append(to_string(k - k0 + 1));
            this->xids[bscct] = k;
            k++;
            bscct++;
        }
    }

    void make_consistent()
    {
        for (int i = 1; i <= this->n_eq; i++)
        {
            if(this->varname[this->xids[i]][0]=='a')
            {
                R scl = this->a[0][this->xids[i]];
                this->r_reduce(0,i,scl);
            }
        }
    }

    void rswap(const int& i,const int& j)
    {
        std::vector<R> tp = this->a[j];
        this->a[j] = this->a[i];
        this->a[i] = tp;

        R btp = this->sol[j];
        this->sol[j] = this->sol[i];
        this->sol[i] = btp;
    }

    // R[i]<-R[i]-C*R[j]
    void r_reduce(const int& i,const int& j,const R C)
    {
        for (int k = 0; k <= this->n_tot; k++)
        {
            this->a[i][k] -= this->a[j][k] * C;
        }
        this->sol[i] -= this->sol[j] * C;
    }

    void scale(const int& j, const R C)
    {
        for (int i = 0; i <= n_tot; i++)
        {
            this->a[j][i] /= C;
        }
        this->sol[j] /= C;
    }

    // optamilaity condition
    int new_entering_variable()
    {
        R mxnv = (R)0;
        int mxid = -1;
        for (int i = 1; i <= n_tot; i++)
        {
            if ((this->a[0][i] * ((R)this->min_or_max)) < 0.0 && abs(this->a[0][i]) > mxnv)
            {
                mxnv = abs(this->a[0][i]);
                mxid = i;
            }
        }

        return mxid;
    }

    // feasibility condiion
    int new_leaving_variable(const int &k)
    {
        int mnid = -1;
        R mnv = inf;
        for (int i = 1; i <= this->n_bsc; i++)
        {
            if (this->a[i][k] > 0 && ((this->sol[i] / this->a[i][k]) < mnv))
            {
                mnv = (this->sol[i] / this->a[i][k]);
                mnid = i;
            }
        }

        return mnid;
    }

    void compute_table(const int max_iter = 100)
    {
        int itrrcount = 1;
        while (max_iter > itrrcount)
        {
            int new_etr = this->new_entering_variable();
            if (new_etr == -1)
            {
                // cout << "Coudn't find entering variable, Simplex iteration completed\n\n";
                break;
            }

            cout << "Entering Variable at " << itrrcount << " iteration is " << this->varname[new_etr] << "\n";

            int new_lev = this->new_leaving_variable(new_etr);
            if (new_lev == -1)
            {
                cout << "Coudn't find leaving variable\n\n";
                break;
            }

            int new_levid = this->xids[new_lev];
            cout << "Leaving Variable at " << itrrcount << " iteration is " << this->varname[new_levid] << "\n\n";
            this->scale(new_lev, this->a[new_lev][new_etr]);

            for (int i = 0; i < n_bsc + 1; i++)
            {
                if (i != new_lev)
                {
                    this->r_reduce(i, new_lev, this->a[i][new_etr]);
                }
            }

            this->xids[new_lev] = new_etr;
            if (this->printtbl)
            {
                cout << "After " << itrrcount << "th interation the table is:\n";
                cout << (*this);
            }
            itrrcount++;
        }
    }

    friend ostream &operator<<(ostream &os,const big_M &bm)
    {
        string s = "Basic";
        os.width(bm.wd);
        os << s;

        for (int i = 0; i <= bm.n_tot; i++)
        {
            os.width(bm.wd);
            os << bm.varname[i];
        }
        os.width(bm.wd);
        os << "Solution\n";

        for (int i = 0; i < bm.n_bsc + 1; i++)
        {
            os.width(bm.wd);
            os << bm.varname[bm.xids[i]];

            for (int j = 0; j <= bm.n_tot; j++)
            {
                os.width(bm.wd);
                os << bm.a[i][j];
            }

            os.width(bm.wd);
            os << bm.sol[i];
            os << "\n";
        }

        return os;
    }
};
