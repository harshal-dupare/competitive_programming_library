#include <iostream>
#include <vector>
#include "linear_eq.hpp"

using namespace std;

template <typename I, typename R>
struct linear_programming_problem
{
    I n_var,n_eq;
    I min_or_max;
    vector<R> z;
    vector<I> var_sign;
    vector<I> eq_types;
    vector<vector<R>> a;
    vector<R> b;

    linear_programming_problem()
    {
    }

    void input()
    {
        cout << "Enter 1 is its maximization problem if minimization problem then -1:";
        cin >> this->min_or_max;
        cout << "number of variables:";
        cin >> this->n_var;

        this->z.assign(this->n_var, (R)0);
        this->var_sign.assign(this->n_var);

        cout << "Enter the coefficients of variables in objective\nif cx[i] and its sign +-1 or 0 for both is coefficient of x_i then give input in format\ncx[1] cx[2] ... cx[n]\n";
        for (I i = 0; i < this->n_var; i++)
        {
            cin >> this->z[i] >> this->var_sign[i];
        }

        cout << "Enter number of conditions: ";
        cin >> this->n_eq;
        this->a.assign(this->n_eq, vector<R>(this->n_var));
        this->b.assign(this->n_eq);
        this->eq_types.assign(this->n_eq);

        cout << "For each condition give input of the coefficient of the variables in condition\n "
             << "for greater than equal to condition: coeff[i][0] .... coeff[i][number_variable] > val[i]\n "
             << "for              equal to condition: coeff[i][0] .... coeff[i][number_variable] = val[i]\n "
             << "for    less than equal to condition: coeff[i][0] .... coeff[i][number_variable] < val[i]\n";

        for (I i = 0; i < this->n_eq; i++)
        {
            for (I j = 0; j < this->n_var; j++)
            {
                cin >>  this->a[i][j];
            }
            char et;
            cin >> et;
            cin >> this->b[i];
            if (et == '<')
            {
                this->eq_types[i] = -1;
            }
            else if (et == '=')
            {
                this->eq_types[i] = 0;
            }
            else if (et== '>')
            {
                this->eq_types[i] = 1;
            }
        }

        
    }

    friend ostream& operator<<(ostream& os, const linear_programming_problem<I,R>& lpp)
    {
        if (lpp.min_or_max == 1)
        {
            os << "Maximize\t ";
        }
        else
        {
            os << "Minimize\t ";
        }
        os << "Z = ";
        for (ll i = 0; i < lpp.n_var; i++)
        {
            if (lpp.z[i] != 0)
            {
                os << std::showpos << lpp.z[i] << std::noshowpos;
                os << "x_" << (i + 1) << " ";
            }
        }
        os << "\nSubject to:\n";
        for (ll i = 0; i < n; i++)
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

        for (ll i = 0; i < lpp.n_eq; i++)
        {
            os << "\t";
            for (ll j = 0; j < lpp.n_var; j++)
            {
                os << std::showpos << lpp.a[i][j] << std::noshowpos;
                os << "x_" << (j + 1) << " ";
            }
            os << (lpp.eq_types[i]==(I)0?'=':(lpp.eq_types[i]==(I)1?'>=':'<=')) << " " << lpp.b[i] << "\n";
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

    // printing solutions of max problems
    void print_solutions(vector<vector<R>> &bfs)
    {
        int oid = 0;
        int id = 0;
        R mxv = -1.0;

        for (int i = 0; i < bfs[0].size() - 1; i++)
        {
            string s = "x_";
            s += to_string(i + 1);
            cout.width(12);
            cout << s;
        }
        cout.width(12);
        cout << "Converges?";
        cout.width(12);
        cout << "Feasible?";
        cout.width(12);
        cout << "Z";
        cout << "\n";
        for (auto s : bfs)
        {
            bool feasible = true;
            for (int i = 0; i < s.size(); i++)
            {
                if (i == s.size() - 1)
                {
                    cout.width(12);
                    cout << ((s[i]) ? "Yes" : "No");
                    continue;
                }
                if (s[i] < 0)
                    feasible = false;
                cout.width(12);
                cout << s[i];
            }
            cout.width(12);
            cout << ((feasible) ? "YES" : "NO");
            R z_val = objective(s);
            cout.width(12);
            cout << z_val;
            cout << "\n";

            if (feasible && z_val > mxv)
            {
                mxv = z_val;
                oid = id;
            }
            id++;
        }

        cout << "\n Among them the optimal solution is \n";
        for (int i = 0; i < bfs[0].size() - 1; i++)
        {
            string s = "x_";
            s += to_string(i + 1);
            cout.width(12);
            cout << s;
        }
        cout.width(12);
        cout << "Converges?";
        cout.width(12);
        cout << "Feasible?";
        cout.width(12);
        cout << "Z";
        cout << "\n";
        bool feasible = true;
        for (int i = 0; i < bfs[oid].size(); i++)
        {
            if (i == bfs[oid].size() - 1)
            {
                cout.width(12);
                cout << ((bfs[oid][i]) ? "Yes" : "No");
                continue;
            }
            if (bfs[oid][i] < 0)
                feasible = false;
            cout.width(12);
            cout << bfs[oid][i];
        }

        cout.width(12);
        cout << (feasible ? "Yes" : "No");
        cout.width(12);
        cout << mxv;
        cout << "\n";
    }

    // printing solutions of min problems
    void print_min_solutions(vector<vector<R>> &bfs)
    {
        int oid = 0;
        int id = 0;
        R mxv = -1.0;

        for (int i = 0; i < bfs[0].size() - 1; i++)
        {
            string s = "x_";
            s += to_string(i + 1);
            cout.width(12);
            cout << s;
        }
        cout.width(12);
        cout << "Converges?";
        cout.width(12);
        cout << "Feasible?";
        cout.width(12);
        cout << "Z";
        cout << "\n";
        for (auto s : bfs)
        {
            bool feasible = true;
            for (int i = 0; i < s.size(); i++)
            {
                if (i == s.size() - 1)
                {
                    cout.width(12);
                    cout << ((s[i]) ? "Yes" : "No");
                    continue;
                }
                if (s[i] < 0)
                    feasible = false;
                cout.width(12);
                cout << s[i];
            }
            cout.width(12);
            cout << ((feasible) ? "YES" : "NO");
            R z_val = objective(s);
            cout.width(12);
            cout << z_val;
            cout << "\n";

            if (feasible && z_val < mxv)
            {
                mxv = z_val;
                oid = id;
            }
            id++;
        }

        cout << "\n Among them the optimal solution is \n";
        for (int i = 0; i < bfs[0].size() - 1; i++)
        {
            string s = "x_";
            s += to_string(i + 1);
            cout.width(12);
            cout << s;
        }
        cout.width(12);
        cout << "Converges?";
        cout.width(12);
        cout << "Feasible?";
        cout.width(12);
        cout << "Z";
        cout << "\n";
        bool feasible = true;
        for (int i = 0; i < bfs[oid].size(); i++)
        {
            if (i == bfs[oid].size() - 1)
            {
                cout.width(12);
                cout << ((bfs[oid][i]) ? "Yes" : "No");
                continue;
            }
            if (bfs[oid][i] < 0)
                feasible = false;
            cout.width(12);
            cout << bfs[oid][i];
        }

        cout.width(12);
        cout << (feasible ? "Yes" : "No");
        cout.width(12);
        cout << mxv;
        cout << "\n";
    }
};

struct basic_feasible_solutions
{
    // goes through aI subset of size m and applies GE and saves soln
    void compute_bfs(linear_eq<R> &le, vector<int> &subset, int lst, int k, vector<vector<R>> &bfs)
    {
        if (subset.size() < le.n_eq)
        {
            for (int i = lst; i < le.n_var; i++)
            {
                subset.push_back(i);
                compute_bfs(le, subset, i + 1, k, bfs);
                subset.pop_back();
            }
            return;
        }

        linear_eq<R> le_new(le.n_eq, le.n_eq);
        for (int i = 0; i < le.n_eq; i++)
        {
            for (int j = 0; j < subset.size(); j++)
            {
                le_new.A[i][j] = le.A[i][subset[j]];
            }
            le_new.B[i] = le.B[i];
        }
        vector<R> x;

        bool converge = le_new.gauss_elemination(true);
        x.assign(le_new.n_eq, 0);
        for (int i = 0; i < le.n_eq; i++)
        {
            if (le_new.A[i][i] < le._pEPS)
            {
                if (le_new.B[i] >= le._pEPS)
                {
                    x[i] = -1;
                }
            }
            else
            {
                x[i] = le_new.B[i];
            }
        }

        vector<R> xx(le.n_var, 0);
        for (int i = 0; i < subset.size(); i++)
        {
            xx[subset[i]] = x[i];
        }

        // save soln
        if (converge)
            xx.push_back(1);
        else
            xx.push_back(0);

        bfs.push_back(xx);
    }

    void basic_feasible_soln(vector<vector<R>> &bfs, linear_eq<R> &le, int k = 100)
    {
        vector<int> subset;
        compute_bfs(le, subset, 0, 1, bfs);
    }
};

void lab_2()
{
    int N = 1;
    for (int k = 0; k < N; k++)
    {
        z.clear();
        int ne, nv, ndv;
        cout << "Give the inputs for " << k + 1 << "'th problem\n";
        cout << "number of equations:";
        cin >> ne;
        cout << "number of variables:";
        cin >> nv;
        cout << "number of decision variables:";
        cin >> ndv;
        z.assign(ndv, (R)0);
        cout << "Enter the number of coefficients of decision variables in problem\n if cx[i] is coefficient of x_i then give input in format, n= number of decision variable:\ncx[1] cx[2] ... cxn[0]\n";
        for (int i = 0; i < ndv; i++)
        {
            cin >> z[i];
        }

        int morm = 1;
        cout << "Enter 1 is its maximization problem if minimization problem then 0:";
        cin >> morm;

        linear_eq<R> le(ne, nv);
        le.input();

        basic_feasible_solutions orl;
        vector<vector<R>> bfs;
        orl.basic_feasible_soln(bfs, le);

        cout << "BFS's are:\n";

        // for maximization problems
        // in 2nd input just give the problem number
        if (morm == 1)
            print_solutions(bfs);

        // for minimization problems
        if (morm == 0)
            print_min_solutions(bfs);
    }
}
