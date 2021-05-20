#pragma once

#include <bits/stdc++.h>

std::vector<long long> rev, roots{0, 1};

template <typename I, I mod>
I power(I a, I b)
{
    a = (a) % mod;
    if (a < 0)
        a += mod;
    I p = a;
    a = (I)1;
    while (b > 0)
    {
        if (b & 1)
        {
            a = (a * p) % mod;
        }
        p = (p * p) % mod;
        b >>= 1;
    }
    return a;
}

template <typename I, I mod>
void dft(std::vector<I> &a)
{
    I n = a.size();
    if (I(rev.size()) != n)
    {
        I k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (I i = 0; i < n; ++i)
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
    for (I i = 0; i < n; ++i)
        if (rev[i] < i)
            std::swap(a[i], a[rev[i]]);
    if (I(roots.size()) < n)
    {
        I k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n)
        {
            I e = power<I, mod>(3, (mod - 1) >> (k + 1));
            for (I i = 1 << (k - 1); i < (1 << k); ++i)
            {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = 1ll * roots[i] * e % mod;
            }
            ++k;
        }
    }
    for (I k = 1; k < n; k *= 2)
    {
        for (I i = 0; i < n; i += 2 * k)
        {
            for (I j = 0; j < k; ++j)
            {
                I u = a[i + j];
                I v = 1ll * a[i + j + k] * roots[k + j] % mod;
                I x = u + v;
                if (x >= mod)
                    x -= mod;
                a[i + j] = x;
                x = u - v;
                if (x < 0)
                    x += mod;
                a[i + j + k] = x;
            }
        }
    }
}

template <typename I, I mod>
void idft(std::vector<I> &a)
{
    I n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft<I, mod>(a);
    I inv = power<I, mod>(n, mod - 2);
    for (I i = 0; i < n; ++i)
        a[i] = 1ll * a[i] * inv % mod;
}

template <typename I, I mod>
class polynomial
{
public:
    I n = -1;
    std::vector<I> a;
    polynomial() {}
    polynomial(I a0)
    {
        this->n = 0;
        a = {a0};
    }
    polynomial(std::vector<I> &a)
    {
        this->n = a.size() - 1;
        this->a = a;
    }
    void input()
    {
        for (I i = 0; i <= n; i++)
        {
            std::cin >> a[i];

            a[i] = (a[i] % mod);
            if (a[i] < 0)
                a[i] += mod;
        }
    }
    bool empty()
    {
        return n == -1;
    }
    I size()
    {
        return this->n + 1;
    }
    friend polynomial<I, mod> operator+(polynomial<I, mod> &o, polynomial<I, mod> &self)
    {
        polynomial<I, mod> ans(std::max(self.n, o.n));
        I i, msz = std::min(self.n, o.n);
        for (i = 0; i <= msz; i++)
        {
            ans.a[i] = (self.a[i] + o.a[i]) % mod;
        }
        for (; i <= self.n; i++)
        {
            ans.a[i] = self.a[i];
        }
        for (; i <= o.n; i++)
        {
            ans.a[i] = o.a[i];
        }
        return ans;
    }
    friend polynomial<I, mod> operator-(polynomial<I, mod> &self, polynomial<I, mod> &o)
    {
        polynomial<I, mod> ans(std::max(self.n, o.n));
        I i, msz = std::min(self.n, o.n);
        for (i = 0; i <= msz; i++)
        {
            ans.a[i] = (self.a[i] + (mod - o.a[i])) % mod;
        }
        for (; i <= self.n; i++)
        {
            ans.a[i] = self.a[i];
        }
        for (; i <= o.n; i++)
        {
            ans.a[i] = mod-o.a[i];
        }
        return ans;
    }
    friend polynomial<I, mod> operator+(std::pair<I, I> pr, polynomial<I, mod> p)
    {
        polynomial<I, mod> ans(std::max(p.n, pr.second));

        ans.a = p.a;
        pr.first = pr.first % mod;
        if (pr.first < 0)
            pr.first += mod;
        ans.a[pr.second] = (ans.a[pr.second] + pr.first) % mod;
        return ans;
    }
    friend polynomial<I, mod> operator-(std::pair<I, I> pr, polynomial<I, mod> p)
    {
        polynomial<I, mod> ans(std::max(p.n, pr.second));

        ans.a = ((I)(-1))*p.a;
        pr.first = pr.first % mod;
        if (pr.first < 0)
            pr.first += mod;
        ans.a[pr.second] = (ans.a[pr.second] + pr.first) % mod;
        return ans;
    }
    void operator+=(polynomial<I, mod> &o)
    {
        this->a.resize(std::max(this->n, o.n) + (I)1);
        I i, msz = std::min(this->n, o.n);
        for (i = 0; i <= msz; i++)
        {
            this->a[i] = (this->a[i] + o.a[i]) % mod;
        }
        for (; i <= o.n; i++)
        {
            this->a[i] = o.a[i];
        }
    }
    void operator-=(polynomial<I, mod> &o)
    {
        this->a.resize(std::max(this->n, o.n) + (I)1);
        I i, msz = std::min(this->n, o.n);
        for (i = 0; i <= msz; i++)
        {
            this->a[i] = (this->a[i] + (mod - o.a[i])) % mod;
        }
        for (; i <= o.n; i++)
        {
            this->a[i] = mod - o.a[i];
        }
    }
    void operator+=(std::pair<I, I> pr)
    {
        this->a.resize(std::max(pr.second, this->n) + (I)1, 0);
        pr.first = pr.first % mod;
        if (pr.first < 0)
            pr.first += mod;
        this->a[pr.second] = (this->a[pr.second] + pr.first) % mod;
    }
    void operator-=(std::pair<I, I> pr)
    {
        this->a.resize(std::max(pr.second, this->n) + (I)1, 0);
        pr.first = pr.first % mod;
        if (pr.first < 0)
            pr.first += mod;
        this->a[pr.second] = (this->a[pr.second] + (mod - pr.first))% mod;
    }

    polynomial<I, mod> operator*(I k)
    {
        polynomial<I, mod> ans(this->n);
        k = (k) % mod;
        if (k < 0)
            k += mod;

        for (I i = 0; i <= this->n; i++)
        {
            ans.a[i] = (k * this->a[i]) % mod;
        }
        return ans;
    }
    void operator*=(I k)
    {
        k = (k) % mod;
        if (k < 0)
            k += mod;

        for (I i = 0; i <= this->n; i++)
        {
            this->a[i] = (k * this->a[i]) % mod;
        }
    }
    friend polynomial<I, mod> operator*(I k, polynomial<I, mod> &p)
    {
        polynomial<I, mod> ans(p.n);
        k = (k) % mod;
        if (k < 0)
            k += mod;

        for (I i = 0; i <= p.n; i++)
        {
            ans.a[i] = (k * p.a[i]) % mod;
        }
        return ans;
    }

    friend polynomial<I, mod> operator*(polynomial<I, mod> a, polynomial<I, mod> b)
    {
        I sz = 1, tot = a.n + b.n;
        while (sz < tot)
            sz *= 2;
        a.a.resize(sz);
        b.a.resize(sz);
        dft<I, mod>(a.a);
        dft<I, mod>(b.a);
        for (I i = 0; i < sz; ++i)
            a.a[i] = (a[i] * b[i]) % mod;
        idft<I, mod>(a.a);
        return polynomial<I, mod>(a.a);
    }

    friend polynomial<I, mod> operatr_mult(polynomial<I, mod> a, polynomial<I, mod> b)
    {
        polynomial<I, mod> ans(a.n + b.n);

        for (I i = 0; i <= ans.n; i++)
        {
            for (I j = 0; j <= a.n; j++)
            {
                ans.a[i] = (ans.a[i] + (b[i - j] * a[j]) % mod) % mod;
            }
        }

        return ans;
    }

    I operator[](I i)
    {
        if (i < 0 || i > n)
            return 0;
        return this->a[i];
    }

    polynomial<I, mod> derivative()
    {
        polynomial<I, mod> ans(this->n - 1);
        for (I i = 0; i < ans.n; i++)
        {
            ans.a[i] = ((i + 1) * this->a[i + 1]) % mod;
        }
        return ans;
    }

    polynomial<I, mod> integral()
    {
        polynomial<I, mod> ans(this->n + 1);
        for (I i = this->n + 1; i >= 1; i--)
        {
            ans.a[i] = (this->power(i, mod - 2) * this->a[i - 1]) % mod;
        }
        ans.a[0] = 0;

        return ans;
    }

    polynomial<I, mod> mod_xk(I k)
    {
        if (k > this->n)
            return polynomial<I, mod>(this->a);
        polynomial<I, mod> p(std::vector<I>(this->a.begin(), this->a.begin() + k));

        return p;
    }

    polynomial<I, mod> mult_xk(I k)
    {
        if (this->n == -1)
            return polynomial<I, mod>();
        polynomial<I, mod> ans(this->n + k);
        for (I i = k; i <= ans.n; i++)
        {
            this->ans[i] = this->a[i - k];
        }

        return ans;
    }

    polynomial<I, mod> div_xk(I k)
    {
        if (k > this->n)
            return polynomial<I, mod>();
        polynomial<I, mod> ans(this->n - k);
        for (I i = 0; i <= ans.n; i++)
        {
            this->ans[i] = this->a[i + k];
        }
        return ans;
    }

    polynomial<I, mod> inverse(I m)
    {
        polynomial<I, mod> x(power(a[0], mod - 2));
        I k = 1;
        while (k < m)
        {
            k *= 2;
            x = (x * (2 - this->mod_xk(k) * x)).mod_xk(k);
        }
        return x.mod_xk(m);
    }

    polynomial<I, mod> log(I m)
    {
        return (this->derivative() * this->inverse(m)).integral().mod_xk(m);
    }

    polynomial<I, mod> exp(I m)
    {
        polynomial<I, mod> x(0);
        x.a[0] = 1;
        I k = 1;
        while (k < m)
        {
            k *= 2;
            x = (x * (1 - x.log(k) + mod_xk(k))).mod_xk(k);
        }
        return x.mod_xk(m);
    }

    polynomial<I, mod> sqrt(I m)
    {
        polynomial<I, mod> x(1);
        I k = 1;
        while (k < m)
        {
            k *= 2;
            x = (x + (mod_xk(k) * x.inverse(k)).mod_xk(k)) * ((mod + 1) / 2);
        }
        return x.mod_xk(m);
    }

    polynomial<I, mod> mulT(polynomial<I, mod> b)
    {
        if (b.size() == 0)
            return polynomial<I, mod>();
        I n = b.size();
        std::reverse(b.a.begin(), b.a.end());
        return ((*this) * b).div_xk(n - 1);
    }

    std::vector<I> eval(std::vector<I> x)
    {
        if (size() == 0)
            return std::vector<I>(x.size(), 0);
        const I n = std::max(I(x.size()), size());
        std::vector<polynomial<I, mod>> q(4 * n);
        std::vector<I> ans(x.size());
        x.resize(n);
        std::function<void(I, I, I)> build = [&](I p, I l, I r) {
            if (r - l == 1)
            {
                q[p] = std::vector<I>{1, (mod - x[l]) % mod};
            }
            else
            {
                I m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(I, I, I, const polynomial<I, mod> &)> work = [&](I p, I l, I r, const polynomial<I, mod> &num) {
            if (r - l == 1)
            {
                if (l < I(ans.size()))
                    ans[l] = num[0];
            }
            else
            {
                I m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).mod_xk(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).mod_xk(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inverse(n)));
        return ans;
    }

    friend std::ostream &operator<<(std::ostream &os, polynomial<I, mod> &p)
    {
        for (I i = 0; i <= p.n; i++)
        {
            os << "(" << std::showpos << p.a[i] << " :[";
            os << std::noshowpos << i << "] ), ";
        }
        os << "\n";
        return os;
    }
};

// template <typename V, typename I, I mod>
// class transforms
// {
// public:
//     std::vector<I> roots
//     I root;
//     // 998244353
//     // has w_{2^23} = 7*17
//     transforms()
//     {
//         this->root=mod-1;
//         while(this->root&1==0)
//         {
//             this->root>>=1;
//         }
//     }

// };

// void ntt(std::vector<I> &a)
// {

// }
