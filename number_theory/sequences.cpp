#include <bits/stdc++.h>

using namespace std;

class general_matrix_sequence
{
public:
    vector<int> a;
    int n;
    int m;
    int inMOD = 1e9 + 7;
    vector<vector<int>> matrix;
    vector<int> base;

    general_matrix_sequence(int n, vector<vector<int>> matrix, int m, vector<int> base)
    {
        this->n = n;
        this->a = vector<int>(this->n, 0);
        this->matrix = matrix;
        this->m = m;
        this->base = base;
    }

    void mm_mult(vector<vector<int>> &a, vector<vector<int>> &b, vector<vector<int>> &prod, int r, int c)
    {
        for (int j = 0; j < r; j++)
        {
            for (int k = 0; k < c; k++)
            {
                prod[j][k] = 0;
                for (int l = 0; l < c; l++)
                {
                    prod[j][k] = (prod[j][k] + this->inMOD + (a[j][l] * b[l][k]) % this->inMOD) % this->inMOD;
                }
            }
        }
    }

    // O(log(i)*m^3) time
    int get_ith(int i)
    {
        if (i < this->m)
            return this->base[i];

        vector<vector<int>> power_matrix = this->matrix;

        // ans matrix is identity matrix at start
        vector<vector<int>> ans_matrix(this->m, vector<int>(this->m, 0));
        for (int j = 0; j < m; j++)
        {
            ans_matrix[j][j] = 1;
        }

        i = i - this->m + 1;

        vector<vector<int>> temp(this->m, vector<int>(this->m));
        while (i > 0)
        {
            if (i % 2 == 1)
            {
                // multiplty the matrix
                this->mm_mult(ans_matrix, power_matrix, temp, this->m, this->m);
                ans_matrix = temp;
            }

            this->mm_mult(power_matrix, power_matrix, temp, this->m, this->m);
            power_matrix = temp;

            i >>= 1;
        }

        int ans = 0;
        for (int j = 0; j < this->m; j++)
        {
            ans = (ans + this->inMOD + (this->base[this->m - 1 - j] * ans_matrix[0][j]) % this->inMOD) % this->inMOD;
        }

        return ans;
    }

    // computes till kth
    void compute(int k)
    {
        return;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> base(m);
    vector<vector<int>> recmatrix(m, vector<int>(m));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> recmatrix[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        cin >> base[i];
    }

    general_matrix_sequence gs = general_matrix_sequence(n, recmatrix, m, base);

    for (int i = 0; i < n; i++)
    {
        cout << i << " : " << gs.get_ith(i) << endl;
    }

    return 0;
}