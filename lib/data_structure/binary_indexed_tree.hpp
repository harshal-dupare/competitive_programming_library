#pragma once
#include <vector>
// FIXME restructure

template <typename I>
class binary_indexed_tree_purq
{
public:
    I n;
    std::vector<I> a, t;
    I nullvalue = 0;
    binary_indexed_tree_purq(I n)
    {
        this->n = n;
        this->a.assign(n, this->nullvalue);
        this->t.assign(n, this->nullvalue);
    }
    void construct(std::vector<I> &arr)
    {
        for (I i = 0; i < this->n; i++)
        {
            this->update(i, arr[i], this->nullvalue);
        }
    }
    // query specific
    // f must saisfy this property  f(x,y,z,..w) = f(f(x,y),f(z,..w))
    I f(I x, I y) const
    {
        // we need the value f(x,y,z,..w)
        // and there must be some way to combine two adjacent t[i] & t[j] into 1
        // implies f(0,0) = 0
        return x + y;          // sum query
        return std::min(x, y); // min query // and there does not exist g() such that f(x,y)=g(f(x,y,z...w),f(z,..w))
    }
    // @param `x` old value at index
    // @param `newx` new value at index
    // @param `t_old` old value in the tree
    // @return the new value in tree `$t$` when x is changed by newx and old value is told
    I new_value(I x, I newx, I t_old) const
    {
        return t_old + (newx - x); // for x+y function
        // for min function
        if (t_old < x || newx < t_old)
        {
            return std::min(t_old, newx);
        }
        else
        {
            return I(-1);
        }
    }
    // query specific
    // bit structure specific
    // g(i) = i&(i+1) is saying as removing all the last traialing 1s
    I g(I i) const
    {
        // must satisfy
        // 0 <= g(i) <= i
        // g(0) = 0 , is prefix sum

        return i & (i + 1);
    }
    // h(i) must help us itterate over the values j,  g(j) <= i <= j in increasing order
    I h(I i) const
    {
        // for g(i) = i&(i+1), h(i) = i|(i+1) ( i.e. making the last zero bit to 1)
        return i | (i + 1);
    }
    // bit structure specific
    I get(I i) const
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
    I range_value(I i, I j) const
    {
        return this->get(j) - (i > 0 ? this->get(i - 1) : 0);
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
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const binary_indexed_tree_purq<U> &bit)
    {
        for (U i = 0; i < bit.n; i++)
        {
            os << "(" << bit.a[i] << "," << bit.get(i) << "), ";
        }
        os << "\n";
        return os;
    }
};

template <typename I>
class binary_indexed_tree_rupq
{
public:
    std::vector<I> a, t;
    I null_value = 0;
    I n;

    binary_indexed_tree_rupq(I n)
    {
        this->n = n;
        this->a = std::vector<I>(n, this->null_value);
        this->t = std::vector<I>(n, this->null_value);
    }

    void construct(std::vector<I> arr)
    {

        for (I i = 0; i < this->n; i++)
        {
            this->update(i, i, arr[i]);
        }
    }

    // query specific
    I f(I x, I y) const 
    {
        return x + y;
    }

    I get_new_value(I val, I update_val) const
    {
        return val + update_val;
    }
    // query specific

    // bit structure specific
    I g(I i) const 
    {
        return (i & (i + 1));
    }

    I h(I i) const 
    {
        return (i | (i + 1));
    }
    // bit structure specific

    I get(I i) const
    {
        I ans = this->null_value;
        while (i >= 0)
        {
            ans = this->f(ans, this->t[i]);
            i = this->g(i) - 1;
        }

        return ans;
    }

    I range_value(I i, I j) const
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

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const binary_indexed_tree_rupq<U> &bit)
    {
        for (U i = 0; i < bit.n; i++)
        {
            os << "(" << bit.a[i] << "," << bit.get(i) << "), ";
        }
        os << "\n";
        return os;
    }
};

template <typename I>
class binary_indexed_tree_rurq
{
public:
    std::vector<I> a, t1, t2;
    I null_value = 0;
    I n;
    binary_indexed_tree_rurq(I n)
    {
        this->n = n;
        this->a = std::vector<I>(n, this->null_value);
        this->t1 = std::vector<I>(n, this->null_value);
        this->t2 = std::vector<I>(n, this->null_value);
    }
    void construct(std::vector<I> arr)
    {
        for (I i = 0; i < this->n; i++)
        {
            this->update(i, i, arr[i]);
        }
    }
    // query specific
    I f(I x, I y) const
    {
        return x + y;
    }
    I get_new_value(I val, I update_val) const
    {
        return val + update_val;
    }
    // query specific
    // bit structure specific
    I g(I i) const
    {
        return (i & (i + 1));
    }
    I h(I i) const
    {
        return (i | (i + 1));
    }
    // bit structure specific
    I get(I i) const
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
    I range_value(I i, I j) const
    {
        if (i == 0)
            return this->get(j);

        return this->get(j) - this->get(i - 1);
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const binary_indexed_tree_rurq<U> &bit)
    {
        os << "t:";
        for (U i = 0; i < bit.n; i++)
        {
            os << "(" << bit.t1[i] << "," << bit.t2[i] << "), ";
        }
        os << "\n";

        os << "a:";
        for (U i = 0; i < bit.n; i++)
        {
            os << "(" << bit.a[i] << "," << bit.get(i) << "), ";
        }
        os << "\n";
        return os;
    }
};
