#include <bits/stdc++.h>

using namespace std;

#define ok(vari) cerr << #vari << " = " << (vari) << endl;

template <typename I>
class binary_indexed_tree_purq
{
public:
    I n;
    vector<I> a, t;
    I nullvalue = 0;

    binary_indexed_tree_purq(I n)
    {
        this->n = n;
        this->a.assign(n, this->nullvalue);
        this->t.assign(n, this->nullvalue);
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
    // query specific

    // bit structure specific
    I g(I i)
    {
        // must satisfy
        // 0 <= g(i) <= i
        // g(i) = 0 , is prefix sum
        // g(i) = i&(i+1) is saying as removing all the last traialing 1s

        return i & (i + 1);
    }

    I h(I i)
    {
        // h(i) must help us itterate over the values j,  g(j) <= i <= j in increasing order
        // for g(i) = i&(i+1), h(i) = i|(i+1) ( i.e. making the last zero bit to 1)

        return i | (i + 1);
    }
    // bit structure specific

    I get(I i)
    {
        I ans = this->t[i];
        i = this->g(i) - 1;
        while (i >= 0)
        {
            ans = this->f(ans, this->t[i]);
            i = this->g(i) - 1;
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
        this->a[i] = value;
        // itteration starts with i itself
        while (i < this->n)
        {
            this->t[i] = this->new_value(old_value, value, this->t[i]);
            i = this->h(i);
        }
    }

    void print()
    {
        for (I i = 0; i < this->n; i++)
        {
            cout << "(" << this->a[i] << "," << this->get(i) << "), ";
        }
        cout << endl;
    }
};

template <typename I>
class binary_indexed_tree_rupq
{
public:
    vector<I> a, t;
    I null_value = 0;
    I n;

    binary_indexed_tree_rupq(I n)
    {
        this->n = n;
        this->a = vector<I>(n, this->null_value);
        this->t = vector<I>(n, this->null_value);
    }

    void construct(vector<I> arr)
    {

        for (I i = 0; i < this->n; i++)
        {
            this->update(i, i, arr[i]);
        }
    }

    // query specific
    I f(I x, I y)
    {
        return x + y;
    }

    I get_new_value(I val, I update_val)
    {
        return val + update_val;
    }
    // query specific

    // bit structure specific
    I g(I i)
    {
        return (i & (i + 1));
    }

    I h(I i)
    {
        return (i | (i + 1));
    }
    // bit structure specific

    I get(I i)
    {
        I ans = this->null_value;
        while (i >= 0)
        {
            ans = this->f(ans, this->t[i]);
            i = this->g(i) - 1;
        }

        return ans;
    }

    I range_value(I i, I j)
    {
        if (i == 0)
            return this->get(j);

        return this->get(j) - this->get(i - 1);
    }

    void update(I i, I j, I update_value)
    {
        this->a[i] = f(this->a[i], update_value);

        while (i < n)
        {
            this->t[i] = this->get_new_value(this->t[i], update_value);
            i = this->h(i);
        }

        if (j != n - 1)
        {
            j++;
            this->a[j] = f(this->a[j], (-1) * update_value);

            while (j < n)
            {
                this->t[j] = this->get_new_value(this->t[j], (-1) * update_value);
                j = this->h(j);
            }
        }
    }

    void print()
    {
        for (I i = 0; i < this->n; i++)
        {
            cout << "(" << this->a[i] << "," << this->get(i) << "), ";
        }
        cout << endl;
    }
};

template <typename I>
class binary_indexed_tree_rurq
{
public:
    vector<I> a, t1, t2;
    I null_value = 0;
    I n;

    binary_indexed_tree_rurq(I n)
    {
        this->n = n;
        this->a = vector<I>(n, this->null_value);
        this->t1 = vector<I>(n, this->null_value);
        this->t2 = vector<I>(n, this->null_value);
    }

    void construct(vector<I> arr)
    {
        for (I i = 0; i < this->n; i++)
        {
            this->update(i, i, arr[i]);
        }
    }

    // query specific
    I f(I x, I y)
    {
        return x + y;
    }

    I get_new_value(I val, I update_val)
    {
        return val + update_val;
    }
    // query specific

    // bit structure specific
    I g(I i)
    {
        return (i & (i + 1));
    }

    I h(I i)
    {
        return (i | (i + 1));
    }
    // bit structure specific

    I get(I i)
    {
        I ans1 = this->null_value;
        I ans2 = this->null_value;
        while (i >= 0)
        {
            ans1 = this->f(ans1, this->t1[i]);
            ans2 = this->f(ans2, this->t2[i]);
            i = this->g(i) - 1;
        }

        return ans1 * (i + 1) - ans2;
    }

    void update(I i, I j, I update_value)
    {
        I update_value_ii = update_value * (i);

        this->a[i] = f(this->a[i], update_value);
        this->a[i] = f(this->a[i], update_value_ii);

        while (i < n)
        {
            this->t1[i] = this->get_new_value(this->t1[i], update_value);
            this->t2[i] = this->get_new_value(this->t2[i], update_value_ii);
            i = this->h(i);
        }

        if (j != n - 1)
        {
            j++;
            I update_value_jj = (-1) * update_value * (j - 1);

            this->a[j] = f(this->a[j], (-1) * update_value);
            this->a[j] = f(this->a[j], update_value_jj);

            while (j < n)
            {
                this->t1[j] = this->get_new_value(this->t1[j], (-1) * update_value);
                this->t2[j] = this->get_new_value(this->t2[j], update_value_jj);
                j = this->h(j);
            }
        }
    }

    I range_value(I i, I j)
    {
        if (i == 0)
            return this->get(j);

        return this->get(j) - this->get(i - 1);
    }

    void print()
    {
        cerr<<"t:";
        for (I i = 0; i < this->n; i++)
        {
            cerr << "(" << this->t1[i] << "," << this->t2[i] << "), ";
        }
        cerr << endl;

        cerr<<"a:";
        for (I i = 0; i < this->n; i++)
        {
            cerr << "(" << this->a[i] << "," << this->get(i) << "), ";
        }
        cerr << endl;
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

    // // point update and range query
    // binary_indexed_tree_purq<int> bit(n);
    // bit.construct(a);
    // bit.print();

    // for (int i = 0; i < n; i++)
    // {
    //     cout << bit.get(i) << ", ";
    // }
    // cout << endl;

    // bit.update(3, 100, bit.a[3]);
    // bit.print();

    // // range update and point query
    // binary_indexed_tree_rupq<int> bit1(n);
    // bit1.construct(a);
    // bit1.print();

    // for (int i = 0; i < n; i++)
    // {
    //     cout << bit1.get(i) << ", ";
    // }
    // cout << endl;

    // bit1.update(3,3,4);
    // bit1.print();

    // range update and range query
    binary_indexed_tree_rurq<int> bit2(n);
    bit2.construct(a);
    bit2.print();

    for (int i = 0; i < n; i++)
    {
        cout << bit2.get(i) << ", ";
    }
    cout << endl;

    bit2.update(3, 4, 4);
    bit2.print();

    return 0;
}