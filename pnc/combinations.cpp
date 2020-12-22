#include <bits/stdc++.h>
#include "../utils/timer.h"

using namespace std;

template <typename I>
class combinations
{
public:
    I N;
    vector<I> fact;
    vector<I> subfact;
    vector<I> bell;
    vector<I> central_delannoy;

    combinations(I N)
    {
        this->N = N;
        this->fact = vector<I>(N + 1);
    }

    I add(I a, I b)
    {
        return a + b;
    }

    I sub(I a, I b)
    {
        return a - b;
    }

    I powerm(I n, I k)
    {
        if (k < 1)
            return 1;

        I pw = n;
        n = 1;
        while (k > 0)
        {
            if (k & 1 == 1)
            {
                n *= pw;
            }
            k >>= 1;
            pw = pw * pw;
        }

        return n;
    }

    void computeFact()
    {
        this->fact[0] = 1;

        for (I i = 1; i <= this->N; i++)
        {
            this->fact[i] = (this->fact[i - 1] * i);
        }
    }

    I nCr(I n, I r)
    {
        if (n < r || r < 0)
            return 0;
        I ans = (I)1;
        for (I i = 1; i <= r; i++)
        {
            ans *= (n - r + i);
            ans /= i;
        }
        return ans;
    }

    I nPr(I n, I r)
    {
        if (n < r || r < 0)
            return 0;

        I ans = (I)1;
        for (I i = 1; i <= r; i++)
        {
            ans *= (n - r + i);
        }
        return ans;
    }

    I catalan(I n)
    {
        if (n < 1)
            return 1;
        I ans = (this->fact[2 * n] / this->fact[n]);
        ans /= this->fact[n];
        ans /= (n + 1);
        return ans;
        // return (this->inMOD + (this->fact[2 * n] * this->ifact[n] * this->ifact[n] * this->powerm(n + 1, inMOD - 2)) % this->inMOD) % this->inMOD;
    }

    I bell_number(I n)
    {
        if (n == 0)
            return 1;

        I bn = 0;
        for (I i = 1; i <= n; i++)
        {
            I increment = (this->powerm(i, n) * this->subfact[n - i]);
            increment = (increment / this->fact[n - i]);
            increment = (increment / this->fact[i]);
            bn = (bn + increment);
        }

        return bn;
    }
};

template <typename I>
class combinations_mod2
{
public:
    I N;
    I inMOD;
    vector<I> ifact;
    vector<I> fact;
    vector<I> subfact;
    vector<I> bell;
    vector<I> central_delannoy;

    combinations_mod2(I N, I inMOD)
    {
        this->N = N;
        this->inMOD = inMOD;
        this->fact = vector<I>(N + 1);
        this->ifact = vector<I>(N + 1);
    }

    inline I add(I a, I b)
    {
        return (this->inMOD + (a + b) % this->inMOD) % this->inMOD;
    }

    inline I sub(I a, I b)
    {
        return (this->inMOD + (a - b) % this->inMOD) % this->inMOD;
    }

    inline I mult(I a, I b)
    {
        return (this->inMOD + (a * b) % this->inMOD) % this->inMOD;
    }

    I powerm(I n, I k)
    {
        if (k < 1)
            return 1;

        I pw = n;
        n = 1;
        while (k > 0)
        {
            if (k & 1 == 1)
            {
                n = this->mult(n, pw);
            }
            k >>= 1;
            pw = this->mult(pw, pw);
        }

        return n;
    }

    void computeFact()
    {
        this->fact[0] = 1;
        this->ifact[0] = 1;

        for (I i = 1; i <= this->N; i++)
        {
            this->fact[i] = this->mult(this->fact[i - 1], i);
            this->ifact[i] = this->powerm(this->fact[i], this->inMOD - 2);
        }
    }

    void compute_subfact()
    {
        this->subfact = vector<I>(this->N);
        this->subfact[0] = 1;
        for (I i = 1; i <= this->N; i++)
        {
            this->subfact[i] = this->add(this->mult(i, this->subfact[i - 1]), (i & 1) * (-2) + 1);
        }
    }

    I nCr(I n, I r)
    {
        if (n < r)
            return 0;
        I ans = this->mult(this->fact[n], this->ifact[r]);
        ans = this->mult(ans, this->ifact[n - r]);
        return ans;
        // return (this->inMOD + (this->fact[n] * this->ifact[r] * this->ifact[n - r]) % this->inMOD) % this->inMOD;
    }

    I nPr(I n, I r)
    {
        if (n < r)
            return 0;
        return this->mult(this->fact[n], this->ifact[n - r]);
    }

    I catalan(I n)
    {
        if (n < 1)
            return 1;
        I ans = this->mult(this->fact[2 * n], this->ifact[n]);
        ans = this->mult(ans, this->ifact[n]);
        ans = this->mult(ans, this->powerm(n + 1, inMOD - 2));
        return ans;
        // return (this->inMOD + (this->fact[2 * n] * this->ifact[n] * this->ifact[n] * this->powerm(n + 1, inMOD - 2)) % this->inMOD) % this->inMOD;
    }

    I bell_number(I n)
    {
        if (n == 0)
            return 1;

        I bn = 0;
        for (I i = 1; i <= n; i++)
        {
            I increment = this->mult(this->powerm(i, n), this->subfact[n - i]);
            increment = this->mult(increment, this->ifact[n - i]);
            increment = this->mult(increment, this->ifact[i]);
            bn = this->add(bn, increment);
            // bn = (bn + this->inMOD + (this->powerm(i, n) * this->subfact[n - i] * this->ifact[n - i] * this->ifact[i]) % this->inMOD) % this->inMOD;
        }

        return bn;
    }

    // O(n)
    void delannoy_number(I n)
    {
        this->central_delannoy = vector<I>(n);

        this->central_delannoy[0] = 1;
        this->central_delannoy[1] = 3;
        for (I i = 2; i < n; i++)
        {
            this->central_delannoy[i] = this->sub(this->mult((I)6, this->central_delannoy[i - 1]), this->central_delannoy[i - 2]);
            this->central_delannoy[i] = this->mult(this->central_delannoy[i], (i - 1));
            this->central_delannoy[i] = this->add(this->central_delannoy[i], this->mult((I)3, this->central_delannoy[i - 1]));
            this->central_delannoy[i] = this->mult(this->central_delannoy[i], this->powerm(i, this->inMOD - 2));
        }
    }
};

template <typename I>
class combinations_mod
{
public:
    I N;
    I inMOD;
    vector<I> ifact;
    vector<I> fact;
    vector<I> subfact;
    vector<I> bell;
    vector<I> central_delannoy;

    combinations_mod(I N, I inMOD)
    {
        this->N = N;
        this->inMOD = inMOD;
        this->fact = vector<I>(N + 1);
        this->ifact = vector<I>(N + 1);
    }

    inline I add(I a, I b)
    {
        I ans = (a + b) % this->inMOD;
        if (ans < 0)
            ans += this->inMOD;
        return ans;
    }

    inline I sub(I a, I b)
    {
        I ans = (a - b) % this->inMOD;
        if (ans < 0)
            ans += this->inMOD;
        return ans;
    }

    inline I mult(I a, I b)
    {
        I ans = (a * b) % this->inMOD;
        if (ans < 0)
            ans += this->inMOD;
        return ans;
    }

    I powerm(I n, I k)
    {
        if (k < 1)
            return 1;

        I pw = n;
        n = 1;
        while (k > 0)
        {
            if (k & 1 == 1)
            {
                n = this->mult(n, pw);
            }
            k >>= 1;
            pw = this->mult(pw, pw);
        }

        return n;
    }

    void computeFact()
    {
        this->fact[0] = 1;
        this->ifact[0] = 1;

        for (I i = 1; i <= this->N; i++)
        {
            this->fact[i] = this->mult(this->fact[i - 1], i);
            this->ifact[i] = this->powerm(this->fact[i], this->inMOD - 2);
        }
    }

    void compute_subfact()
    {
        this->subfact = vector<I>(this->N);
        this->subfact[0] = 1;
        for (I i = 1; i <= this->N; i++)
        {
            this->subfact[i] = this->add(this->mult(i, this->subfact[i - 1]), (i & 1) * (-2) + 1);
        }
    }

    I nCr(I n, I r)
    {
        if (n < r)
            return 0;
        I ans = this->mult(this->fact[n], this->ifact[r]);
        ans = this->mult(ans, this->ifact[n - r]);
        return ans;
        // return (this->inMOD + (this->fact[n] * this->ifact[r] * this->ifact[n - r]) % this->inMOD) % this->inMOD;
    }

    I nPr(I n, I r)
    {
        if (n < r)
            return 0;
        return this->mult(this->fact[n], this->ifact[n - r]);
    }

    I catalan(I n)
    {
        if (n < 1)
            return 1;
        I ans = this->mult(this->fact[2 * n], this->ifact[n]);
        ans = this->mult(ans, this->ifact[n]);
        ans = this->mult(ans, this->powerm(n + 1, inMOD - 2));
        return ans;
        // return (this->inMOD + (this->fact[2 * n] * this->ifact[n] * this->ifact[n] * this->powerm(n + 1, inMOD - 2)) % this->inMOD) % this->inMOD;
    }

    I bell_number(I n)
    {
        if (n == 0)
            return 1;

        I bn = 0;
        for (I i = 1; i <= n; i++)
        {
            I increment = this->mult(this->powerm(i, n), this->subfact[n - i]);
            increment = this->mult(increment, this->ifact[n - i]);
            increment = this->mult(increment, this->ifact[i]);
            bn = this->add(bn, increment);
            // bn = (bn + this->inMOD + (this->powerm(i, n) * this->subfact[n - i] * this->ifact[n - i] * this->ifact[i]) % this->inMOD) % this->inMOD;
        }

        return bn;
    }

    // O(n)
    void delannoy_number(I n)
    {
        this->central_delannoy = vector<I>(n);

        this->central_delannoy[0] = 1;
        this->central_delannoy[1] = 3;
        for (I i = 2; i < n; i++)
        {
            this->central_delannoy[i] = this->sub(this->mult((I)6, this->central_delannoy[i - 1]), this->central_delannoy[i - 2]);
            this->central_delannoy[i] = this->mult(this->central_delannoy[i], (i - 1));
            this->central_delannoy[i] = this->add(this->central_delannoy[i], this->mult((I)3, this->central_delannoy[i - 1]));
            this->central_delannoy[i] = this->mult(this->central_delannoy[i], this->powerm(i, this->inMOD - 2));
        }
    }
};

#define ll long long
int main()
{

    ll n;
    cin >> n;
    timer tm;
    double tf = 0, tsf = 0, tct = 0, tcd = 0, tif = 0;
    double tf2 = 0, tsf2 = 0, tct2 = 0, tcd2 = 0, tif2 = 0;

    combinations_mod<ll> cb(100005, (1e9 + 7));
    tm.set();
    cb.computeFact();
    tf = tm.get();

    tm.set();
    cb.compute_subfact();
    tsf = tm.get();

    combinations_mod2<ll> cb2(100005, (1e9 + 7));
    tm.set();
    cb2.computeFact();
    tf2 = tm.get();

    tm.set();
    cb2.compute_subfact();
    tsf2 = tm.get();

    ll ct = 0;
    for (ll i = 0; i < n; i++)
    {
        ll ans = cb.fact[i];
        ll ans2 = cb2.fact[i];
        if (ans == ans2)
        {
            ct++;
        }
        // cout << i << ":" << ans << endl;
    }
    cout << endl;
    cout << ct << "/ " << n << endl;

    ct = 0;
    for (ll i = 0; i < n; i++)
    {
        ll ans = cb.ifact[i];
        ll ans2 = cb2.ifact[i];
        if (ans == ans2)
        {
            ct++;
        }
        // cout << i << ":" << ans << endl;
    }
    cout << endl;
    cout << ct << "/ " << n << endl;

    ct = 0;
    ct = 0;
    for (ll i = 0; i < n; i++)
    {
        ll ans = cb.subfact[i];
        ll ans2 = cb2.subfact[i];
        if (ans == ans2)
        {
            ct++;
        }
        // cout << i << ":" << ans << endl;
    }
    cout << endl;
    cout << ct << "/ " << n << endl;

    ct = 0;
    for (ll i = 0; i < n; i++)
    {
        tm.set();
        ll ans = cb.catalan(i);
        tct += tm.get();
        // cout << i << ":" << ans << endl;

        tm.set();
        ll ans2 = cb2.catalan(i);
        tct2 += tm.get();

        if (ans == ans2)
        {
            ct++;
        }
    }
    cout << endl;
    cout << ct << "/ " << n << endl;

    ct = 0;

    tm.set();
    cb.delannoy_number(100);
    tcd = tm.get();

    tm.set();
    cb2.delannoy_number(100);
    tcd2 = tm.get();

    ct = 0;
    for (ll i = 0; i < 100; i++)
    {
        ll ans = cb.central_delannoy[i];
        ll ans2 = cb2.central_delannoy[i];

        if (ans == ans2)
        {
            ct++;
        }
        // cout << i << ":" << ans << endl;
    }
    cout << endl;
    cout << ct << "/ " << 100 << endl;

    cout << fixed << setprecision(6) << "fact: " << tf2 / tf << endl;
    // cout << fixed << setprecision(6) << "ifact: " << tif2 / tif << endl;
    cout << fixed << setprecision(6) << "subfact: " << tsf2 / tsf << endl;
    cout << fixed << setprecision(6) << "cat: " << tct2 / tct << endl;
    cout << fixed << setprecision(6) << "cd: " << tcd2 / tcd << endl;

    return 0;
}


/*

1000

1000/ 1000

1000/ 1000

1000/ 1000

1000/ 1000

100/ 100
fact: 1.899322
subfact: 1.484769
cat: 1.352475
cd: 1.708066


*/