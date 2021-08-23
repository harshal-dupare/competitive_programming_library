#include <iostream>
#include <vector>
#include "linear_eq.hpp"

using namespace std;
typedef double R;

struct basic_feasible_solutions
{
    // goes through all subset of size m and applies GE and saves soln
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

template<typename I, typename R>
struct linear_programming_problem
{
    I mxormn;
    vector<R> zcoeff;

    // function to compute the objective value
    R objective(vector<R> &xs)
    {
        R val = 0;
        for (int i = 0; i < zcoeff.size(); i++)
        {
            val += zcoeff[i] * xs[i];
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

void lab_2()
{
    int N = 1;
    for (int k = 0; k < N; k++)
    {
        zcoeff.clear();
        int ne, nv, ndv;
        cout << "Give the inputs for " << k + 1 << "'th problem\n";
        cout << "number of equations:";
        cin >> ne;
        cout << "number of variables:";
        cin >> nv;
        cout << "number of decision variables:";
        cin >> ndv;
        zcoeff.assign(ndv, (R)0);
        cout << "Enter the number of coefficients of decision variables in problem\n if cx[i] is coefficient of x_i then give input in format, n= number of decision variable:\ncx[1] cx[2] ... cxn[0]\n";
        for (int i = 0; i < ndv; i++)
        {
            cin >> zcoeff[i];
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

int main()
{
    return 0;
}
