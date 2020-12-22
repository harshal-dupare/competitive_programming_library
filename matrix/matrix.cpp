#include <bits/stdc++.h>

// namespaces starts
using namespace std;

template <typename I>
class matrix
{
public:
    I **a;
    I n;
    matrix(I n)
    {
        this->n = n;
        a = new I *[n];
        for (I i = 0; i < n; i++)
        {
            a[i] = new I[n];
        }

        for (I i = 0; i < n; i++)
        {
            for (I j = 0; j < n; j++)
            {
                a[i][j] = 0;
            }
            a[i][i] = 1;
        }
    }

    matrix operator*(matrix &b)
    {
        matrix temp(n);
        for (I i = 0; i < n; i++)
        {
            for (I j = 0; j < n; j++)
            {
                temp.a[i][j] = 0;
                for (I k = 0; k < n; k++)
                {
                    temp.a[i][j] += a[i][k] * b.a[k][j];
                }
            }
        }

        return temp;
    }

    void operator*=(matrix &b)
    {
        I **ta = new I *[n];
        for (I i = 0; i < n; i++)
        {
            ta[i] = new I[n];
        }
        for (I i = 0; i < n; i++)
        {
            for (I j = 0; j < n; j++)
            {
                ta[i][j] = 0;
                for (I k = 0; k < n; k++)
                {
                    ta[i][j] += a[i][k] * b.a[k][j];
                }
            }
        }
        a = ta;
    }

    matrix power(matrix a, I k)
    {
        if (k == 1)
            return a;
        matrix tp = this->per(a, k / 2);
        tp = tp * tp;
        if (k % 2 == 1)
        {
            tp = tp * a;
        }

        return tp;
    }

    void print()
    {
        for (I i = 0; i < n; i++)
        {
            for (I j = 0; j < n; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int n;
    cin >> n;
    matrix<int> c(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> c.a[i][j];
        }
    c.print();
    matrix tc = c.per(c, 10);
    tc.print();

    return 0;
}
