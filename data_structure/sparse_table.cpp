
#include <bits/stdc++.h>

using namespace std;

#define OK(vari) cerr << #vari << " = " << (vari) << endl;

template <typename I>
class sparse_table
{
public:
    vector<vector<I>> table;
    I n;
    I k;
    I(*f)(I, I);
    vector<I> a;
    I null_value=HUGE_VALL;

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
            // OK(i);
            this->table[i][0] = this->f(this->a[i], this->a[i]);
        }
        // OK("OK");

        for (int i = 1; i < this->k; i++)
        {
            for (int j = 0; (j + (1 << (i - 1))) < this->n; j++)
            {
                // OK(i);OK(j);
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

int fc(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{

    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    sparse_table<int> tb(n,*fc,a);
    tb.compute();
    int k;
    cin>>k;
    int i,j;
    while (k--)
    {
        cin>>i>>j;
        int h= tb.query(i,j);
        cout<<h<<endl;
    }

    return 0;
}