#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double R;

// FIXME compare with other implementation
// properties : (static array, {add,min,max}:other similar)
template <typename I>
class sparse_table
{
public:
    vector<vector<I>> table;
    I n;
    I k;
    I(*f)(I, I);
    vector<I> a;
    I null_value=1e9;

    sparse_table(I n, I (*f)(I, I), vector<I> a)
    {
        I k = 0;
        I tn = n;
        this->n = n;
        while (tn > 0)
        {
            k++;
            tn >>= 1;
        }
        this->k = k;
        this->a = a;
        this->table = vector<vector<I>>(n, vector<I>(k + 2, 0));
        this->f = f;
    }

    void compute()
    {
        for (int i = 0; i < this->n; i++)
        {
            this->table[i][0] = this->f(this->a[i], this->null_value);
        }

        for (int i = 1; i < this->k; i++)
        {
            for (int j = 0; (j + (1 << (i - 1))) < this->n; j++)
            {
                this->table[j][i] = this->f(this->table[j + (1 << (i - 1))][i - 1], this->table[j][i - 1]);
            }
        }
    }

    I query(int l, int r)
    {
        int d = r - l + 1;
        int p = 0;
        I ans = this->a[l];

        while (d > 0)
        {
            if ((d & 1) == 1)
            {
                ans = f(ans, this->table[l][p]);
                l += (1 << p);
            }
            d >>= 1;
            p++;
        }

        return ans;
    }
};
