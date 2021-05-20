

template <typename I>
class lmodop
{
public:
    I MOD;
    lmodop(I MOD)
    {
        this->MOD = MOD;
    }

    I add(I n, I m)
    {
        return (this->MOD + (n + m) % this->MOD) % this->MOD;
    }

    I sub(I n, I m)
    {
        return (this->MOD + (n - m) % this->MOD) % this->MOD;
    }

    I mult(I n, I m)
    {
        return (this->MOD + (n * m) % this->MOD) % this->MOD;
    }

    I powm(I n, I k)
    {
        I ans = 1;
        I po = n;
        while (k > 0)
        {
            if (k & 1)
            {
                ans = this->mult(ans, n);
            }
            po = this->mult(po, po);
            k >>= 1;
        }

        return ans;
    }

    I div(I n, I m)
    {
        return this->mult(n, this->powm(m, this->MOD - 2));
    }
};

template <typename I>
class modop
{
public:
    I MOD;
    modop(I MOD)
    {
        this->MOD = MOD;
    }

    I add(I n, I m)
    {
        I ans = (n + m) % this->MOD;
        if (ans < 0)
            ans += this->MOD;

        return ans;
    }

    I sub(I n, I m)
    {
        I ans = (n - m) % this->MOD;
        if (ans < 0)
            ans += this->MOD;
        return ans;
    }

    I mult(I n, I m)
    {
        I ans = (n * m) % this->MOD;
        if (ans < 0)
            ans += this->MOD;

        return ans;
    }

    I powm(I n, I k)
    {
        I ans = 1;
        I po = n;
        while (k > 0)
        {
            if (k & 1)
            {
                ans = this->mult(ans, n);
            }
            po = this->mult(po, po);
            k >>= 1;
        }

        return ans;
    }

    I div(I n, I m)
    {
        return this->mult(n, this->powm(m, this->MOD - 2));
    }
};
