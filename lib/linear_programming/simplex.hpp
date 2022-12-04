#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "linear_programming_problem.hpp"

template <typename I, typename R>
class simplex
{
public:
    std::vector<std::vector<R>> a;
    std::vector<R> sol;
    std::vector<I> xids;
    std::vector<string> varname;

    I n_var, n_eq;
    I n_slc, n_srp, n_arf, n_bsc, n_nbsc, n_tot;
    I n_neg;
    I min_or_max;
    R inf = 1e20;

    I wd = 10;
    bool printtbl = true;

    simplex(const linear_programming_problem<I, R> &lpp)
    {
        this->min_or_max = lpp.min_or_max;
        this->n_var = lpp.n_var;
        this->n_eq = lpp.n_eq;
        this->n_slc = lpp.n_slc;
        this->n_arf = lpp.n_arf;
        this->n_srp = lpp.n_srp;
        this->n_bsc = lpp.n_bsc;

        std::vector<std::vector<I>> vtypes(3);
        for (I i = 0; i < lpp.n_var; i++)
        {
            vtypes[lpp.var_sign[i] + 1].push_back(i);
        }
        this->n_neg = (I)vtypes[1].size();
        this->n_tot = lpp.n_tot + this->n_neg;
        this->n_nbsc = lpp.n_nbsc + this->n_neg;

        assert(this->n_bsc == this->n_eq);

        this->sol.assign((I)this->n_bsc + 1, (R)0);
        for (I i = 1; i <= lpp.n_bsc; i++)
        {
            this->sol[i] = lpp.b[i - 1];
        }

        this->a.assign((I)this->n_bsc + 1, std::vector<R>((I)this->n_tot + 1, (R)0));

        this->a[0][0] = (R)1;
        for (I i = 0; i < (I)lpp.z.size(); i++)
        {
            this->a[0][i + 1] = -lpp.z[i];
        }
        for (I i = 0; i < (I)lpp.a.size(); i++)
        {
            for (I j = 0; j < lpp.n_var; j++)
            {
                this->a[i + 1][j + 1] = lpp.a[i][j];
            }
        }

        this->varname.assign((I)this->n_tot + 1, string());
        this->varname[0] = "z";
        this->xids.assign((I)this->n_bsc + 1, 0);

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

        I k = this->n_var + 1;
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
        I k0 = k;
        for (auto i : v_srp)
        {
            this->a[i + 1][k] = -((R)1);
            this->varname[k] = "srp_";
            this->varname[k].append(to_string(k - k0 + 1));
            k++;
        }
        k0 = k;
        I bscct = 1;
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

    void rswap(const I& i,const I& j)
    {
        std::vector<R> tp = this->a[j];
        this->a[j] = this->a[i];
        this->a[i] = tp;

        R btp = this->sol[j];
        this->sol[j] = this->sol[i];
        this->sol[i] = btp;
    }

    // R[i]<-R[i]-C*R[j]
    void r_reduce(const I& i,const I& j,const R C)
    {
        for (I k = 0; k <= this->n_tot; k++)
        {
            this->a[i][k] -= this->a[j][k] * C;
        }
        this->sol[i] -= this->sol[j] * C;
    }

    void scale(const I& j, const R C)
    {
        for (I i = 0; i <= n_tot; i++)
        {
            this->a[j][i] /= C;
        }
        this->sol[j] /= C;
    }

    // optamilaity condition
    I new_entering_variable()
    {
        R mxnv = (R)0;
        I mxid = -1;
        for (I i = 1; i <= n_tot; i++)
        {
            if ((this->a[0][i] * ((R)this->min_or_max)) < (R)0 && abs(this->a[0][i]) > mxnv)
            {
                mxnv = abs(this->a[0][i]);
                mxid = i;
            }
        }

        return mxid;
    }

    // feasibility condiion
    I new_leaving_variable(const I &k)
    {
        I mnid = -1;
        R mnv = inf;
        for (I i = 1; i <= this->n_bsc; i++)
        {
            if (this->a[i][k] > (R)0 && ((this->sol[i] / this->a[i][k]) < mnv))
            {
                mnv = (this->sol[i] / this->a[i][k]);
                mnid = i;
            }
        }

        return mnid;
    }

    void compute_table(const I max_iter = 100)
    {
        I itrrcount = (I)1;
        while (max_iter > itrrcount)
        {
            I new_etr = this->new_entering_variable();
            if (new_etr == (I)-1)
            {
                // cout << "Coudn't find entering variable, Simplex iteration completed\n\n";
                break;
            }

            cout << "Entering Variable at " << itrrcount << " iteration is " << this->varname[new_etr] << "\n";

            I new_lev = this->new_leaving_variable(new_etr);
            if (new_lev == (I)-1)
            {
                cout << "Coudn't find leaving variable\n\n";
                break;
            }

            I new_levid = this->xids[new_lev];
            cout << "Leaving Variable at " << itrrcount << " iteration is " << this->varname[new_levid] << "\n\n";
            this->scale(new_lev, this->a[new_lev][new_etr]);

            for (I i = 0; i <= n_bsc; i++)
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

    friend ostream &operator<<(ostream &os,const simplex &si)
    {
        string s = "Basic";
        os.width(si.wd);
        os << s;

        for (I i = 0; i <= si.n_tot; i++)
        {
            os.width(si.wd);
            os << si.varname[i];
        }
        os.width(si.wd);
        os << "Solution\n";

        for (I i = 0; i <= si.n_bsc ; i++)
        {
            os.width(si.wd);
            os << si.varname[si.xids[i]];

            for (I j = 0; j <= si.n_tot; j++)
            {
                os.width(si.wd);
                os << si.a[i][j];
            }

            os.width(si.wd);
            os << si.sol[i];
            os << "\n";
        }

        return os;
    }
};
