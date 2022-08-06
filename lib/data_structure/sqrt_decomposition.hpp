#pragma once

#include <vector>
#include <iostream>
// FIXME improve the roubstness 
// FIXME try to add template to make it all in 1 only if possible

// properties: (updatable array, range_value:{add*,min*})
template <typename I>
class sqrt_dec_purq
{
public:
    I n;
    I sqrt_n = (I)3;
    std::vector<I> a, b;
    I nullvalue = 0;

    sqrt_dec_purq(I n)
    {
        this->n = n;
        this->a.assign(n, this->nullvalue);
        this->b.assign((n / sqrt_n) + 1, this->nullvalue);
    }

    void construct(std::vector<I> &arr)
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
        return x + y;          // sum query
        return std::min(x, y); // min query
    }

    I new_value(I x, I newx, I t_old)
    {
        // returns the new value of the t when x is changed by newx and old value is told
        return t_old + (newx - x); // for x+y function
    }
    // query specific

    I range_value(I i, I j)
    {
        I sqrt_i = i/this->sqrt_n;
        I sqrt_j = j/this->sqrt_n;
        I ans = this->nullvalue;
    
        for (I k = sqrt_i+1; k < sqrt_j; k++)
        {
            ans = this->f(ans, this->b[k]);
        }

        for (I k = i; k < (sqrt_i+1) * sqrt_n; k++)
        {
            ans = this->f(ans, this->a[k]);
        }

        for (I k = sqrt_j * sqrt_n; k <= j; k++)
        {
            ans = this->f(ans, this->a[k]);
        }

        return ans;
    }

    void update(I i, I value, I old_value)
    {
        I sqrt_i = (i / sqrt_n);
        this->b[sqrt_i] = this->new_value(old_value, value, this->b[sqrt_i]);
        this->a[i] = this->new_value(old_value, value, old_value);
    }

    void print()
    {
        for (I i = 0; i <= this->n / this->sqrt_n; i++)
        {
            std::cout << this->b[i] << ", ";
        }
        std::cout << std::endl;

        for (I i = 0; i < this->n; i++)
        {
            I temp = this->get(i);
            std::cout << "(" << this->a[i] << ", " << temp << "), ";
        }
        std::cout << std::endl;
    }
};

// properties: (updatable array, update:{incriment*}, get:{access})
template <typename I>
class sqrt_dec_rupq
{
public:
    I n;
    I sqrt_n = (I)3;
    std::vector<I> a, b;
    I nullvalue = 0;

    sqrt_dec_rupq(I n)
    {
        this->n = n;
        this->a.assign(n, this->nullvalue);
        this->b.assign((n / sqrt_n) + 1, this->nullvalue);
    }

    void construct(const std::vector<I> &arr)
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
        return x + y;          // sum query
    }

    I new_value(I x, I newx, I t_old)
    {
        // returns the new value of the t when x is changed by newx and old value is told
        return t_old + (newx - x); // for x+y function
    }
    // query specific

    I get(I i)
    {
        I sqrt_i = i / this->sqrt_n;
        I ans = this->b[sqrt_i];
        ans = this->f(this->a[i], ans);
        return ans;
    }

    void update(I i, I j, I incriment_value)
    {
        I sqrt_i = (i / this->sqrt_n);
        I sqrt_j = (j / this->sqrt_n);

        for (I k = sqrt_i+1; k < sqrt_j; k++)
        {
            this->b[k] = this->f(this->b[k], incriment_value);
        }

        for (I k = i; k < (sqrt_i+1) * sqrt_n; k++)
        {
            this->a[k] = this->f(this->a[k], incriment_value);
        }

        for (I k = sqrt_j * sqrt_n; k <= j; k++)
        {
            this->a[k] = this->f(this->a[k], incriment_value);
        }
    }

    void print()
    {
        for (I i = 0; i <= this->n / this->sqrt_n; i++)
        {
            std::cout << this->b[i] << ", ";
        }
        std::cout << std::endl;

        for (I i = 0; i < this->n; i++)
        {
            I temp = this->get(i);
            std::cout << "(" << this->a[i] << ", " << temp << "), ";
        }
        std::cout << std::endl;
    }
};

// properties: (updateable array, range_update:{incriment*}, point_query:{access}, range_query:{add*})
template <typename I>
class sqrt_dec_gen
{
public:
    I n;
    I sqrt_n = (I)3;
    std::vector<I> a, b, c;
    I nullvalue = 0;

    sqrt_dec_gen(I n)
    {
        this->n = n;
        this->a.assign(n, this->nullvalue);
        this->b.assign((n / sqrt_n) + 1, this->nullvalue);
        this->c.assign((n / sqrt_n) + 1, this->nullvalue);
    }

    void construct(const std::vector<I> &arr)
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
        return x + y; // sum query
    }

    I new_value(I x, I newx, I t_old)
    {
        // returns the new value of the t when x is changed by newx and old value is t_old
        return t_old + (newx - x); // for x+y function
    }
    // query specific

    I point_query(I i)
    {
        I ans = this->b[(i / this->sqrt_n)];
        ans = this->f(this->a[i], ans);
        return ans;
    }

    I range_query(I i, I j)
    {
        I sqrt_i = i / this->sqrt_n;
        I sqrt_j = j / this->sqrt_n;
        I ans = this->nullvalue;

        for (I k = sqrt_i + 1; k < sqrt_j; k++)
        {
            ans = this->f(ans, this->f(this->b[k] * this->sqrt_n, this->c[k]));
        }

        for (I k = i; k < max((sqrt_i + 1) * this->sqrt_n, this->n); k++)
        {
            ans = this->f(ans, this->f(this->a[k], this->b[sqrt_i]));
        }

        for (I k = (sqrt_j) * this->sqrt_n; k <= j; k++)
        {
            ans = this->f(ans, this->f(this->a[k], this->b[sqrt_j]));
        }
        return ans;
    }

    void point_update(I i, I update_value)
    {
        I sqrt_i = i / this->sqrt_n;
        this->a[i] = this->f(this->a[i], update_value);
        this->c[sqrt_i] = this->f(this->c[sqrt_i], update_value);
    }

    void range_update(I i, I j, I incriment_value)
    {
        I sqrt_i = (i / this->sqrt_n);
        I sqrt_j = (j / this->sqrt_n);

        for (I k = sqrt_i+1; k < sqrt_j; k++)
        {
            this->b[k] = this->f(this->b[k], incriment_value);
        }

        for (I k = i; k < (sqrt_i+1) * sqrt_n; k++)
        {
            this->a[k] = this->f(this->a[k], incriment_value);
            this->c[sqrt_i] = this->f(this->c[sqrt_i], incriment_value);
        }

        for (I k = sqrt_j * sqrt_n; k <= j; k++)
        {
            this->a[k] = this->f(this->a[k], incriment_value);
            this->c[sqrt_i] = this->f(this->c[sqrt_i], incriment_value);
        }
    }

    void print()
    {
        for (I i = 0; i <= this->n / this->sqrt_n; i++)
        {
            std::cout << "(" << this->b[i] << "," << this->c[i] << "), ";
        }
        std::cout << std::endl;

        for (I i = 0; i < this->n; i++)
        {
            I temp = this->point_query(i);
            std::cout << "(" << this->a[i] << ", " << temp << "), ";
        }
        std::cout << std::endl;
    }
};
