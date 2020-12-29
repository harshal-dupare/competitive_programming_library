#include <bits/stdc++.h>

using namespace std;

#define ok(vari) cerr << #vari << " = " << (vari) << endl;

template <typename I>
class sqrt_dec
{
public:
    I n;
    I sqrt_n = (I)3;
    vector<I> a, b;
    I nullvalue = 0;

    sqrt_dec(I n)
    {
        this->n = n;
        this->a.assign(n, this->nullvalue);
        this->b.assign((n / sqrt_n) + 1, this->nullvalue);
    }

    void construct(vector<I> arr)
    {
        for (I i = 0; i < this->n; i++)
        {
            this->update(i, arr[i], this->nullvalue);
        }
    }

    // query specific
    I f(I x, I y)
    {
        // we need the value f(x,y,z,..w)
        // and there must be some way to combine two adjacent t[i] & t[j] into 1
        // f must saisfy this property  f(x,y,z,..w) = f(f(x,y),f(z,..w))
        // implies f(0,,0) = 0
        return x + y;     // sum query
        return min(x, y); // min query
    }

    I new_value(I x, I newx, I t_old)
    {
        // returns the new value of the t when x is changed by newx and old value is told
        return t_old + (newx - x); // for x+y function
    }

    I get(I i)
    {
        I ans = this->nullvalue;
        // ok(ans);
        I sqrt_i = i / this->sqrt_n;
        for (I j = 0; j < sqrt_i; j++)
        {
            ans = this->f(ans, this->b[j]);
            // ok(j)
            //     ok(ans)
        }
        I low = max(sqrt_i, 0) * sqrt_n;
        for (I j = low; j <= i; j++)
        {
            ans = this->f(ans, this->a[j]);
            // ok(j)
            //     ok(ans)
        }
        return ans;
    }

    I range_value(I i, I j)
    {
        if (i == 0)
            return this->get(j);

        return this->get(j) - this->get(i - 1);
    }

    void update(I i, I value, I old_value)
    {
        I sqrt_i = (i / sqrt_n);
        this->b[sqrt_i] = this->new_value(old_value, value, this->b[sqrt_i]);
        this->a[i] = this->new_value(old_value, value, old_value);
    }
    // query specific

    void print()
    {
        for (I i = 0; i <= this->n / this->sqrt_n; i++)
        {
            cout << this->b[i] << ", ";
        }
        cout << endl;

        for (I i = 0; i < this->n; i++)
        {
            I temp = this->get(i);
            cout << "(" << this->a[i] << ", " << temp << "), ";
        }
        cout << endl;
    }
};

template <typename I>
class sqrt_dec_rupq
{
public:
    I n;
    I sqrt_n = (I)3;
    vector<I> a, b;
    I nullvalue = 0;

    sqrt_dec_rupq(I n)
    {
        this->n = n;
        this->a.assign(n, this->nullvalue);
        this->b.assign((n / sqrt_n) + 1, this->nullvalue);
    }

    void construct(const vector<I> &arr)
    {
        for (I i = 0; i < this->n; i++)
        {
            this->a[i] = arr[i];
        }
    }

    // query specific
    I f(I x, I y)
    {
        // we need the value f(x,y,z,..w)
        // and there must be some way to combine two adjacent t[i] & t[j] into 1
        // f must saisfy this property  f(x,y,z,..w) = f(f(x,y),f(z,..w))
        // implies f(0,,0) = 0
        return x + y;     // sum query
        return min(x, y); // min query
    }

    I new_value(I x, I newx, I t_old)
    {
        // returns the new value of the t when x is changed by newx and old value is told
        return t_old + (newx - x); // for x+y function
    }

    I get(I i)
    {
        I sqrt_i = i / this->sqrt_n;
        I ans = this->b[sqrt_i] / this->sqrt_n;
        ans = this->f(this->a[i], ans);
        return ans;
    }

    void update(I j, I i, I update_value)
    {
        I sqrt_i = (i / this->sqrt_n);
        I sqrt_j = (j / this->sqrt_n);

        for (I k = sqrt_j; k < sqrt_i; k++)
        {
            this->b[k] = this->f(this->b[k], this->sqrt_n * update_value);
        }

        for (I k = sqrt_i * this->sqrt_n ; k <= i; k++)
        {
            this->a[k] = this->f(this->a[k], update_value);
        }

        for (I k = sqrt_j * this->sqrt_n; k < j; k++)
        {
            this->a[k] = this->f(this->a[k], (-1)*update_value);
        }
    }
    // query specific

    void print()
    {
        for (I i = 0; i <= this->n / this->sqrt_n; i++)
        {
            cout << this->b[i] << ", ";
        }
        cout << endl;

        for (I i = 0; i < this->n; i++)
        {
            I temp = this->get(i);
            cout << "(" << this->a[i] << ", " << temp << "), ";
        }
        cout << endl;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sqrt_dec_rupq<int> sqd(n);
    sqd.construct(a);
    sqd.print();

    for (int i = 0; i < n; i++)
    {
        cout << sqd.get(i) << ", ";
    }
    cout << endl;

    // sqd.update(3, 4, sqd.a[3]);
    sqd.update(1, 4, 7);
    ok("ok")
    sqd.print();

    return 0;
}