#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <typename I, typename R>
struct linear_programming_problem
{
    bool is_input_taken;
    I n_var, n_eq;
    I n_slc, n_srp, n_arf, n_bsc, n_nbsc, n_tot;

    I min_or_max;
    vector<R> z;
    vector<I> var_sign;
    vector<I> eq_types;
    vector<vector<R>> a;
    vector<R> b;

    linear_programming_problem()
    {
        this->is_input_taken = false;
    }

    void calculate_auxilary_counts()
    {
        this->n_slc = 0, this->n_srp = 0, this->n_arf = 0;
        for (I i = 0; i < this->n_eq; i++)
        {
            if (this->eq_types[i] == (R)-1)
            {
                this->n_slc++;
            }
            else if (this->eq_types[i] == 0)
            {
                this->n_arf++;
            }
            else
            {
                this->n_arf++;
                this->n_srp++;
            }
        }
        this->n_nbsc = this->n_var + this->n_srp;
        this->n_bsc = this->n_arf + this->n_slc;
        this->n_tot = this->n_bsc + this->n_nbsc;
    }

    void input(const bool &to_standardized = false)
    {
        cout << " maximization = 1 / minimization = -1:";
        cin >> this->min_or_max;
        cout << "# Decision variables:";
        cin >> this->n_var;

        this->z.assign(this->n_var, (R)0);
        this->var_sign.assign(this->n_var, (R)1);

        cout << "Enter the coefficients of variables in objective\nif cx[i] and its sign +-1 or 0 for both is coefficient of x_i then give input in format\ncx[1] cx[2] ... cx[n]\n";
        for (I i = 0; i < this->n_var; i++)
        {
            cin >> this->z[i] >> this->var_sign[i];
        }

        cout << "Enter number of conditions: ";
        cin >> this->n_eq;
        this->a.assign(this->n_eq, vector<R>(this->n_var));
        this->b.assign(this->n_eq, (R)0);
        this->eq_types.assign(this->n_eq, (R)0);

        cout << "For each condition give input of the coefficient of the variables in condition\n "
             << "for greater than equal to condition: coeff[i][0] .... coeff[i][number_variable] > val[i]\n "
             << "for              equal to condition: coeff[i][0] .... coeff[i][number_variable] = val[i]\n "
             << "for    less than equal to condition: coeff[i][0] .... coeff[i][number_variable] < val[i]\n";

        this->n_slc = 0, this->n_srp = 0, this->n_arf = 0;
        for (I i = 0; i < this->n_eq; i++)
        {
            for (I j = 0; j < this->n_var; j++)
            {
                cin >> this->a[i][j];
            }
            char et;
            cin >> et;
            cin >> this->b[i];
            if (et == '<')
            {
                this->eq_types[i] = -1;
                this->n_slc++;
            }
            else if (et == '=')
            {
                this->eq_types[i] = 0;
                this->n_arf++;
            }
            else if (et == '>')
            {
                this->eq_types[i] = 1;
                this->n_arf++;
                this->n_srp++;
            }
        }

        this->n_nbsc = this->n_var + this->n_srp;
        this->n_bsc = this->n_arf + this->n_slc;
        this->n_tot = this->n_bsc + this->n_nbsc;

        this->is_input_taken = true;
    }

    bool is_valid_solution(const vector<R>& sol)
    {
        for(I i=0;i<this->n_var;i++)
        {
            if(this->var_sign[i]==-1)
            {
                if(sol[i]>(R)0)
                {
                    return false;
                }
            } 
            else if (this->var_sign[i]==1)
            {
                if(sol[i]<(R)0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    friend ostream &operator<<(ostream &os, const linear_programming_problem<I, R> &lpp)
    {
        if (!lpp.is_input_taken)
        {
            os << "Input not taken for the lpp\n";
            return os;
        }

        if (lpp.min_or_max == 1)
        {
            os << "Maximize\t ";
        }
        else
        {
            os << "Minimize\t ";
        }
        os << "Z = ";
        for (I i = 0; i < lpp.n_var; i++)
        {
            if (lpp.z[i] != 0)
            {
                os << std::showpos << lpp.z[i] << std::noshowpos;
                os << "x_" << (i + 1) << " ";
            }
        }
        os << "\nSubject to:\n";
        for (I i = 0; i < lpp.n_var; i++)
        {
            if (lpp.var_sign[i] == 1)
            {
                os << "x_" << (i + 1) << " >= 0,";
            }
            else if (lpp.var_sign[i] == 0)
            {
                os << "x_" << (i + 1) << " is unristrected, ";
            }
            else
            {
                os << "x_" << (i + 1) << " <= 0,";
            }
        }
        os << "\n";

        for (I i = 0; i < lpp.n_eq; i++)
        {
            os << "\t";
            for (I j = 0; j < lpp.n_var; j++)
            {
                os << std::showpos << lpp.a[i][j] << std::noshowpos;
                os << "x_" << (j + 1) << " ";
            }
            os << " ";
            if (lpp.eq_types[i] == (I)1)
            {
                os << ">";
            }
            else if (lpp.eq_types[i] == (I)-1)
            {
                os << "<";
            }
            os << "= " << lpp.b[i] << "\n";
        }

        return os;
    }

    // function to compute the objective value
    R objective(const vector<R> &xs)
    {
        R val = 0;
        for (int i = 0; i < z.size(); i++)
        {
            val += z[i] * xs[i];
        }
        return val;
    }
};

template <typename I, typename R>
linear_programming_problem<I, R> dual_problem(const linear_programming_problem<I, R> &lpp)
{
    linear_programming_problem<I, R> dual;
    dual.min_or_max = -lpp.min_or_max;
    dual.z = lpp.b;
    dual.b = lpp.z;
    dual.n_eq = lpp.n_var;
    dual.n_var = lpp.n_eq;
    dual.var_sign.assign(dual.n_var, (R)0);
    dual.eq_types.assign(dual.n_eq, (R)0);
    dual.a.assign(dual.n_eq, vector<R>(dual.n_var, (R)0));

    for (I i = 0; i < dual.a.size(); i++)
    {
        for (I j = 0; j < dual.a[i].size(); j++)
        {
            dual.a[i][j] = lpp.a[j][i];
        }
    }

    // easier way to do this is multiply by lpp.min_or_max before asigning
    // but this needs multiplication to computing is expensive
    if (lpp.min_or_max == (R)1)
    {
        // lpp :: max problem
        for (I i = 0; i < dual.z.size(); i++)
        {
            dual.var_sign[i] = -lpp.eq_types[i];
            // dual.var_sign[i]=-lpp.min_or_max*lpp.eq_types[i];
        }

        for (I i = 0; i < dual.b.size(); i++)
        {
            dual.eq_types[i] = lpp.var_sign[i];
            // dual.eq_types[i]=lpp.min_or_max*lpp.var_sign[i];
        }
    }
    else
    {
        // lpp :: min problem
        for (I i = 0; i < dual.z.size(); i++)
        {
            dual.var_sign[i] = lpp.eq_types[i];
        }

        for (I i = 0; i < dual.b.size(); i++)
        {
            dual.eq_types[i] = -lpp.var_sign[i];
        }
    }

    dual.calculate_auxilary_counts();

    dual.is_input_taken = true;
    return dual;
}
