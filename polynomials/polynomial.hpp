#pragma once

#include <bits/stdc++.h>
#include "ffts.hpp"

template <typename I, I mod>
struct polynomial
{
    std::vector<I> a;
    polynomial()
    {
        this->a.assign(1, 0);
    }
    polynomial(I deg, I val)
    {
        this->a.assign(deg + 1, val);
    }
    polynomial(const std::vector<I> &_a)
    {
        this->a.assign(_a.begin(), _a.end());
    }
    polynomial(const polynomial<I, mod> &p)
    {
        this->a.assign(p.a.begin(), p.a.end());
    }
    polynomial(const string& s)
    {
        I i=0;
        vector<pair<I,I>> pl;
        I j=-1;
        while (i<s.size())
        {
            if(s[i]=='+')
            {
                i++;
                string c;
                while (s[i]!='*')
                {
                    if(s[i]!=' ') c.push_back(s[i]);
                    i++;
                }
                I ic = atoi(c.c_str());
                pl.push_back(make_pair(-1,ic));
                j++;
            }
            else if(s[i]=='-')
            {
                i++;
                string c;
                while (s[i]!='*')
                {
                    if(s[i]!=' ') c.push_back(s[i]);
                    i++;
                }
                I ic = atoi(c.c_str());
                pl.push_back(make_pair(-1,-ic));
                j++;
            }
            else if(s[i]=='^')
            {
                i++;
                string c;
                while (i<s.size()&&s[i]!='+'&&s[i]!='-')
                {
                    if(s[i]!=' ') c.push_back(s[i]);
                    i++;
                }

                I ic = atoi(c.c_str());
                pl[j].first = ic;
            }
            else
            {
                i++;
            }
        }
        
        sort(pl.begin(),pl.end());
        this->a.clear();
        I n = pl[(int)pl.size()-1].first;
        this->a.assign(n+1,0);
        for(auto p: pl)
        {
            this->a[p.first] = p.second;
        }
    }
    void operator=(const polynomial<I, mod> &other)
    {
        if (this != &other)
        {
            this->a.assign(other.a.begin(), other.a.end());
        }
    }

    // O(deg-last_non_zero_id)
    void shrink_to_fit()
    {
        I _n = (I)this->a.size() - 1;
        while (_n > 0 && this->a[_n] == 0)
        {
            _n--;
        }

        this->a.resize(_n + 1);
    }
    I size() const
    {
        return (I)this->a.size();
    }
    I degree() const
    {
        return (I)this->a.size() - 1;
    }
    I operator[](int idx) const
    {
        if (idx < 0 || idx >= (int)this->size())
            return 0;
        return this->a[idx];
    }

    // O(max(deg1,deg2))
    polynomial<I, mod> operator+(const polynomial<I, mod> &y)
    {
        vector<I> _a(this->a.begin(), this->a.end());
        _a.resize(std::max(this->size(), y.size()), 0);
        for (int i = 0; i < y.size(); i++)
        {
            _a[i] += y.a[i];
            if (_a[i] >= mod)
            {
                _a[i] -= mod;
            }
        }
        int i=_a.size()-1;
        while(i>0&&_a[i]==0)
        {
            i--;
        }
        _a.resize(i+1);
        return polynomial<I, mod>(_a);
    }
    // O(max(deg1,deg2))
    void operator+=(polynomial<I, mod> &y)
    {
        this->a.resize(std::max(this->size(), y.size()), 0);
        for (int i = 0; i < y.size(); i++)
        {
            this->a[i] += y.a[i];
            if (this->a[i] >= mod)
            {
                this->a[i] -= mod;
            }
        }
        this->shrink_to_fit();
    }
    // O(max(deg1,deg2))
    polynomial<I, mod> operator-(const polynomial<I, mod> &y)
    {
        vector<I> _a(this->a.begin(), this->a.end());
        _a.resize(std::max(this->size(), y.size()), 0);
        for (int i = 0; i < y.size(); i++)
        {
            _a[i] -= y.a[i];
            if (_a[i] < 0)
            {
                _a[i] += mod;
            }
        }
        int i=_a.size()-1;
        while(i>0&&_a[i]==0)
        {
            i--;
        }
        _a.resize(i+1);
        return polynomial<I, mod>(_a);
    }
    // O(max(deg1,deg2))
    void operator-=(polynomial<I, mod> &y) 
    {
        this->a.resize(std::max(this->size(), y.size()), 0);
        for (int i = 0; i < y.size(); i++)
        {
            this->a[i] -= y.a[i];
            if (this->a[i] < 0)
            {
                this->a[i] += mod;
            }
        }
        this->shrink_to_fit();
    }
    // O( deg*log(deg) )
    friend polynomial<I, mod> operator*(polynomial<I, mod> a, polynomial<I, mod> b)
    {
        I sz = 1, tot = a.degree() + b.degree();
        while (sz < tot + 1)
            sz *= 2;
        a.a.resize(sz, 0);
        b.a.resize(sz, 0);

        fft::ntt<I, mod>(a.a);
        fft::ntt<I, mod>(b.a);
        for (I i = 0; i < sz; ++i)
            a.a[i] = (a.a[i] * b.a[i]) % mod;
        fft::ntt<I, mod>(a.a,true);
        a.shrink_to_fit();
        return a;
    }
    // O( deg*log(deg) )
    void operator*=(polynomial<I, mod> b)
    {
        I sz = 1, tot = this->degree() + b.degree();
        while (sz < tot + 1)
            sz *= 2;
        this->a.resize(sz, 0);
        b.a.resize(sz, 0);

        fft::ntt<I, mod>(this->a);
        fft::ntt<I, mod>(b.a);
        for (I i = 0; i < sz; ++i)
            this->a[i] = (this->a[i] * b.a[i]) % mod;
        fft::ntt<I, mod>(this->a,true);
        this->shrink_to_fit();
    }
    // O( deg )
    friend polynomial<I, mod> operator*(I k, polynomial<I, mod> &p)
    {
        I n = p.degree();
        polynomial<I, mod> ans(n,0);
        k = (k) % mod;
        if (k < 0)
            k += mod;

        for (I i = 0; i <= n; i++)
        {
            ans.a[i] = (k * p.a[i]) % mod;
        }
        ans.shrink_to_fit();
        return ans;
    }
    // O( deg )
    void operator*=(I k)
    {
        k %= mod;
        if (k < 0)
            k += mod;
        I n = this->degree();
        for (I i = 0; i <= n; i++)
        {
            this->a[i] = (k * this->a[i]) % mod;
        }
        this.shrink_to_fit();
    }
    // O( deg*log(deg) )
    friend polynomial<I, mod> operator/(polynomial<I, mod> a, polynomial<I, mod> b)
    {
        a.shrink_to_fit();
        b.shrink_to_fit();
        if (a.degree() < b.degree())
        {
            return polynomial<I, mod>(0,0);
        }
        std::reverse(a.a.begin(),a.a.end());
        std::reverse(b.a.begin(),b.a.end());
        I dega=a.degree(),degb=b.degree();
        a = (a * b.inverse(dega-degb+1)).mod_xk(dega-degb+1);
        a.shrink_to_fit();
        std::reverse(a.a.begin(),a.a.end());
        a = a.mult_xk(dega-degb-a.degree());
        return a;
    }
    // O( deg*log(deg) )
    void operator/=(polynomial<I, mod> b)
    {
        this->shrink_to_fit();
        b.shrink_to_fit();
        if (this->degree() < b.degree())
        {
            this->a.assign(0,0);
        }
        std::reverse(this->a.begin(),this->a.end());
        std::reverse(b.a.begin(),b.a.end());
        I dega=this->degree(),degb=b.degree();
        (*this) = ((*this)* b.inverse(dega-degb+1)).mod_xk(dega-degb+1);
        this->shrink_to_fit();
        std::reverse(this->a.begin(),this->a.end());
        (*this) = this->mult_xk(dega-degb-this->degree());
    }
    // O( deg*log(deg) )
    friend polynomial<I, mod> operator%(polynomial<I, mod> a, polynomial<I, mod> b)
    {
        a.shrink_to_fit();
        b.shrink_to_fit();
        if (a.degree() < b.degree())
        {
            return a;
        }
        polynomial<I, mod> d = a/b;
        d = (d*b).mod_xk(b.degree());
        a = (a - d).mod_xk(b.degree());
        return a;
    }
    // O( deg*log(deg) )
    void operator%=(polynomial<I, mod> b)
    {
        this->shrink_to_fit();
        b.shrink_to_fit();
        if (this->degree() < b.degree())
        {
            return;
        }
        polynomial<I, mod> d = (*this)/b;
        (*this) -=((d*b).mod_xk(b.degree()));   
        (*this) = this->mod_xk(b.degree());  
    }
    // O( deg^2 )
    friend polynomial<I, mod> mult(polynomial<I, mod> &a, polynomial<I, mod> &b)
    {
        polynomial<I, mod> ans(a.degree() + b.degree());
        I n1 = ans.degree();
        I n2 = a.degree();
        for (I i = 0; i <= n1; i++)
        {
            for (I j = 0; j <= n2; j++)
            {
                ans.a[i] = (ans.a[i] + (b[i - j] * a[j]) % mod) % mod;
            }
        }

        return ans;
    }

    // O( max(deg1,deg2) )
    bool operator==(const polynomial<I, mod> &_a)
    {
        I mn = std::max(this->size(),_a.size());
        I i=0;
        for(i=0;i<mn;i++)
        {
            if(this->a[i]!=_a.a[i])
            {
                return false;
            }
        }
        for(;i<_a.size();i++)
        {
            if(_a.a[i]!=0)
            {
                return false;
            }
        }
        for(;i<this->size();i++)
        {
            if(this->a[i]!=0)
            {
                return false;
            }
        }
        return true;
    }
    // O( max(deg1,deg2) )
    bool operator!=(const polynomial<I, mod> &_a)
    {
        I mn = std::max(this->size(),_a.size());
        I i=0;
        for(i=0;i<mn;i++)
        {
            if(this->a[i]!=_a.a[i])
            {
                return true;
            }
        }
        for(;i<_a.size();i++)
        {
            if(_a.a[i]!=0)
            {
                return true;
            }
        }
        for(;i<this->size();i++)
        {
            if(this->a[i]!=0)
            {
                return true;
            }
        }
        return false;
    }

    // O(deg)
    polynomial<I, mod> derivative()
    {
        polynomial<I, mod> ans(this->degree() - 1, 0);
        I n = ans.degree();
        for (I i = 0; i < n; i++)
        {
            ans.a[i] = ((i + 1) * this->a[i + 1]) % mod;
        }
        return ans;
    }
    // O(deg)
    polynomial<I, mod> integral()
    {
        polynomial<I, mod> ans(this->degree() + 1, 0);
        for (I i = this->degree() + 1; i >= 1; i--)
        {
            ans.a[i] = (fft::power(i, mod - 2) * this->a[i - 1]) % mod;
        }
        ans.a[0] = 0;

        return ans;
    }
    // O(k)
    polynomial<I, mod> mod_xk(I k)
    {
        if (k > this->degree())
            return polynomial<I, mod>(this->a);
        vector<I> p(k, 0);
        k = std::min(k, this->degree() + 1);
        for (I i = 0; i < k; i++)
        {
            p[i] = this->a[i];
        }
        return polynomial<I, mod>(p);
    }
    // O(deg)
    polynomial<I, mod> mult_xk(I k)
    {

        polynomial<I, mod> ans(this->degree() + k, 0);
        I n = ans.degree();
        for (I i = k; i <= n; i++)
        {
            ans.a[i] = this->a[i - k];
        }
        return ans;
    }
    // O(deg-k)
    polynomial<I, mod> div_xk(I k)
    {
        if (k > this->degree())
            return polynomial<I, mod>(0, 0);
        polynomial<I, mod> ans(this->degree() - k, 0);
        I n = ans.degree();
        for (I i = 0; i <= n; i++)
        {
            ans.a[i] = this->a[i + k];
        }
        return ans;
    }
    // O( deg*log(deg) )
    polynomial<I, mod> inverse(I m)
    {
        polynomial<I, mod> x(0, fft::power<I>(a[0], mod - 2, mod));
        polynomial<I, mod> tx;
        I k = 1;
        polynomial<I, mod> two(0, 2);
        while (k < m)
        {
            k *= 2;
            tx = (*this) * x;
            tx.shrink_to_fit();
            tx = two - tx;
            x = x*tx;
            x = x.mod_xk(k);
        }
        return x.mod_xk(m);
    }
    // O(deg)
    polynomial<I, mod> log(I m)
    {
        return (this->derivative() * this->inverse(m)).integral().mod_xk(m);
    }
    // O(deg)
    polynomial<I, mod> exp(I m)
    {
        polynomial<I, mod> x(1, 1);
        I k = 1;
        while (k < m)
        {
            k *= 2;
            x = (x * (1 - x.log(k) + mod_xk(k))).mod_xk(k);
        }
        return x.mod_xk(m);
    }
    // O(deg)
    polynomial<I, mod> sqrt(I m)
    {
        polynomial<I, mod> x(1, 1);
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
    // O( deg )
    I eval(I x) const
    {
        x = x%mod;
        if(x<0) x+=mod;

        I fx = 0;
        for (I i = this->a.size() - 1; i >= 0; i--)
        {
            fx = (fx * x) % mod;
            fx = (fx + this->a[i]);
            if (fx >= mod)
                fx -= mod;
            else if (fx < 0)
                fx += mod;
        }

        return fx;
    }
    friend std::ostream &operator<<(std::ostream &os, const polynomial<I, mod> &p)
    {
        for (I i = p.a.size()-1; i >=0; i--)
        {
            if (p.a[i] != (I)0)
            {
                os << std::showpos << p.a[i] << "*x^";
                os << std::noshowpos << i ;
            }
        }
        
        os << "\n";
        return os;
    }
};

// O( n * log(n) * log(deg) )
template <typename I, I mod>
std::vector<I> multipoint_eval(polynomial<I, mod> &poly,const std::vector<I> &u)
{
    I on = u.size();
    I q = std::max((I)u.size(), poly.size());
    I k = 0;
    while (q > 0)
    {
        q >>= 1;
        k++;
    }
    q = 1 << k;
    vector<I> fu(on, poly.a[0]);
    if(poly.degree()==0)
    {
        return fu;
    }

    // // construct P[i][j] polynomials
    // std::vector<std::vector<polynomial<I, mod>>> P(k + 1);
    // for (I i = 0; i < on; i++)
    // {
    //     polynomial<I, mod> tp(1, 1);
    //     tp.a[0] = (mod-(u[i]%mod));
    //     if(tp.a[0]<0) tp.a[0]+=mod;
    //     else if (tp.a[0]>=mod) tp.a[0]-=mod;
    //     P[0].push_back(tp);
    // }
    // for (I i = on; i < q; i++)
    // {
    //     polynomial<I, mod> tp(1, 1);
    //     tp.a[0]=0;
    //     P[0].push_back(tp);
    // }
    // for (I i = 1; i <= k; i++)
    // {
    //     I qi = (q >> i);
    //     P[i].resize(qi);
    //     for (I j = 0; j < qi; j++)
    //     {
    //         P[i][j]=P[i - 1][2 * j + 1] * P[i - 1][2 * j];
    //     }
    // }

    // construct P[i][j] polynomials
    // P[i][j] = xi....xi+2^j-1
    std::vector<std::vector<polynomial<I, mod>>> P(k + 1);
    for (I i = 0; i < on; i++)
    {
        polynomial<I, mod> tp(1, 1);
        tp.a[0] = (mod-(u[i]%mod));
        if(tp.a[0]<0) tp.a[0]+=mod;
        else if (tp.a[0]>=mod) tp.a[0]-=mod;
        P[0].push_back(tp);
    }
    for (I i = on; i < q; i++)
    {
        polynomial<I, mod> tp(1, 1);
        tp.a[0]=0;
        P[0].push_back(tp);
    }
    for (I i = 1; i <= k; i++)
    {
        I qi = (1 << i);
        P[i].resize(q-qi+1);
        for (I j = 0; j + qi - 1 < q; j++)
        {
            P[i][j]=P[i - 1][j] * P[i - 1][j+(1<<(i-1))];
        }
    }

    // init stack
    stack<polynomial<I, mod>> Sp;
    stack<I> Sl;
    stack<I> Sr;
    stack<I> Sk;
    Sp.push(poly);
    Sl.push((I)0);
    Sr.push(q - 1);
    Sk.push(k);

    while (!Sl.empty())
    {
        I l = Sl.top();
        Sl.pop();
        I r = Sr.top();
        Sr.pop();
        I tk = Sk.top();
        Sk.pop();
        polynomial<I, mod> f = Sp.top();
        Sp.pop();

        if(l>=on)
        {
            break;
        }
        f.shrink_to_fit();
        if (f.degree() == 0 && (l==r))
        {
            fu[l] = f[0];
            // I tv = poly.eval(u[l]);
            // if(tv!=fu[l])
            // {
            //     cout<<poly;
            //     cout<<u[l]<<": ( "<<fu[l]<<", "<<tv<<" )"<<endl;
            //     r = 0;
            // }
            continue;
        }
        I mid = (l + r) / 2;
        // polynomial<I, mod> r0 = f % P[tk - 1][0];
        // polynomial<I, mod> r1 = f % P[tk - 1][1];
        polynomial<I, mod> r0 = f % P[tk - 1][l];
        polynomial<I, mod> r1 = f % P[tk - 1][mid+1];

        Sl.push(mid+1);
        Sr.push(r);
        Sk.push(tk - 1);
        Sp.push(r1);

        Sl.push(l);
        Sr.push(mid);
        Sk.push(tk - 1);
        Sp.push(r0);
    }
    return fu;
}