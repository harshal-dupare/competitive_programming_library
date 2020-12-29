#include <bits/stdc++.h>
#include "../utils/timer.h"
#include "../utils/debugger.h"

using namespace std;

template <typename I>
class number_properties
{
public:
    I gcd(I n, I m)
    {
        n = abs(n);
        m = abs(m);
        while (m > 0)
        {
            I temp = m;
            m = n % m;
            n = temp;
            // tie(n, m) = make_pair(m, n % m);
        }

        return n;
    }

    I lcm(I a, I b)
    {
        if (a == 0 && b == 0)
            return 0;

        return a * b / this->gcd(a, b);
    }

    I extended_gcd(I n, I n0, I &x, I &y)
    {
        x = 1;
        y = 0;
        I xp = 0, yp = 1;

        // n  - n0*k = n1
        // n0 - n1*x1=n2
        // n1 - n2*x2=n3
        while (n0 > 0)
        {
            I k = n / n0;
            tie(x, xp) = make_pair(xp, x - k * xp);
            tie(y, yp) = make_pair(yp, y - k * yp);
            tie(n, n0) = make_pair(n0, n % n0);
        }

        return n;
    }

    I gcd_set(vector<I> &s)
    {
        I ans = 1;
        for (auto x : s)
        {
            ans = gcd(x, ans);
            if (ans == 1)
                return;
        }

        return ans;
    }

    I lcm_set(vector<I> &s)
    {
        I ans = this->lcm(s[0], s[1]);
        for (I i = 2; i < s.size(); i++)
        {
            ans = lcm(ans, s[i]);
        }
        return ans;
    }

    I mmult(I a, I b, I p)
    {
        return (p + (a * b) % p) % p;
    }

    I madd(I a, I b, I p)
    {
        return (p + (a + b) % p) % p;
    }

    I quadratic_residues(I n, I p)
    {
        I pr = (p - 1) / 2;
        I npr = 1;
        I nitr = n;
        while (pr > 0)
        {
            if (pr & 1)
            {
                npr = mmult(npr, nitr, p);
            }

            pr >>= 1;
            nitr = mmult(nitr, nitr, p);
        }

        if (npr == 1)
        {
            return 1;
        }

        return -1;
    }

    I quadratic_residues_f(I n, I p)
    {
        vector<pair<I, I>> fcts;
        I i = 2;
        while (i * i <= n)
        {
            if (n % i == 0)
            {
                fcts.push_back({i, 1});
                n /= i;
            }
            while (n % i == 0)
            {
                n /= i;
                fcts[fcts.size() - 1].second++;
            }
            i++;
        }

        if (n > 1)
        {
            fcts.push_back({n, 1});
        }
        I qr = 1;

        for (auto x : fcts)
        {
            if (x.second % 2 == 1)
            {
                qr *= this->quadratic_residues(x.first, p);
            }
        }

        return qr;
    }

    // O(a^(1/2)+phi(n))
    I order_mod_n(I a, I n)
    {
        if (gcd(a, n) != 1)
        {
            return -1;
        }
        I ord = 1;
        I aord = a;
        while (a != 1)
        {
            aord = mmult(a, aord, n);
            ord++;
        }

        return ord;
    }

    // order of a^k
    I order_mod_n(I a, I k, I n)
    {
        I base_ord = this->order_mod_n(a, n);
        if (base_ord == -1)
            return -1;

        return base_ord / gcd(base_ord, k);
    }

    // O(n^(1/2)+p1^k1+p2^k2+..+pn^kn) where pi^ki's are max power of primes dividing n
    I order_mod_n_f(I a, I n)
    {
        vector<I> fcts;
        I i = 2;
        while (i * i <= n)
        {
            if (n % i == 0)
            {
                n /= i;
                fcts.push_back(i);
            }
            while (n % i == 0)
            {
                n /= i;
                fcts[fcts.size() - 1] *= i;
            }
            i++;
        }

        if (n > 1)
        {
            fcts.push_back(n);
        }

        I ord = order_mod_n(fcts[0]);
        for (I j = 1; j < fcts.size(); j++)
        {
            ord = lcm(ord, order_mod_n(fcts[j]));
        }

        return ord;
    }

    // O(n^(1/2)+w(n)*log(phi(n)/w(n)))
    bool is_premitive_root(I g, I n)
    {   
        // number of primitive roots are phi(phi(n)) if they exist else 0
        // Primitive roots exist modulo 𝑛 if and only if 𝑛 = 2, 4, 𝑝^𝑘, or 2𝑝^𝑘 for 𝑝 an odd prime
        I phi = 1;
        vector<I> primes(1, 1);
        I i = 2;
        while (i * i <= n)
        {
            if (n % i == 0)
            {
                primes.push_back(i);
                phi *= i - 1;
                n /= i;
            }
            while (n % i == 0)
            {
                n /= i;
                phi *= i;
            }
            i++;
        }

        if (n > 1)
        {
            phi *= n - 1;
            primes.push_back(n);
        }

        I pr = 0;
        I gp = 1;
        for (I i = primes.size() - 1; i >= 0; i--)
        {
            I incr = (phi / primes[i]) - pr;
            I gpr = 1, gir = g;
            while (incr > 0)
            {
                if (incr & 1)
                {
                    gpr = (gpr * gir) % n;
                }
                gir = (gir * gir) % n;
                incr >>= 1;
            }
            gp = (gp * gpr) % n;
            if (gp == 1 && primes[i] != 1)
            {
                return false;
            }
        }

        return true;
    }
    // I frobenius(vector<I> &nl)
    // {
    //     if (nl.size() < 2 || this->gcd_set(nl) != 1)
    //         return -1;
    //     if (nl.size() == 2)
    //     {
    //         return
    //     }
    // }

    // need to debug
    // reciprocal period of 1/n in O(n^(1/2)+p1^k1+p2^k2+..+pn^kn) where pi^ki's are max power of primes dividing n
    I reciprocal_period(I n)
    {
        vector<pair<I, I>> fcts;
        I i = 2;
        while (i * i <= n)
        {
            if (n % i == 0)
            {
                fcts.push_back({i, i});
                n /= i;
            }
            while (n % i == 0)
            {
                n /= i;
                fcts[fcts.size() - 1].second *= i;
            }
            i++;
        }

        if (n > 1)
        {
            fcts.push_back({n, n});
        }

        if (fcts.size() == 0)
        {
            return 0;
        }
        // okp(fcts);

        I ans = 1;
        I other_fact = 0;
        for (I j = 0; j < fcts.size(); j++)
        {
            if (fcts[j].first != 2 && fcts[j].first != 5)
            {
                other_fact = 1;
                ans = this->lcm(this->fract_period(1, fcts[j].second), ans);
            }
        }

        return ans * other_fact;
    }

    // reciprocal period of p/q in O(q)
    I fract_period(I p, I q)
    {
        unordered_map<I, I> lstoccr;
        // I gc = this->gcd(p, q);
        // p /= gc;
        // q /= gc;
        I rem = p % q;
        I i = 1;
        I period = 0;
        while (rem > 0)
        {
            auto itr = lstoccr.find(rem);
            if (itr == lstoccr.end())
            {
                lstoccr[rem] = i;
            }
            else
            {
                period = i - itr->second;
                break;
            }

            rem = (10 * rem) % q;
            i++;
        }

        return period;
    }
};

void test_cyc()
{
    number_properties<int> np;
    int n;
    cin >> n;
    // int mxv=-1,mxi;
    for (int i = 1; i <= n; i++)
    {
        // cout << i << ":" << np.reciprocal_period(i) << endl;
        // if(np.fract_period(1,i) >= mxv)
        // {
        //     mxv = np.fract_period(1,i);
        //     mxi=i;
        // }
        // cout << np.fract_period(1,i) << ", ";
        // cout << np.fract_period(1,i) << ", ";
        cout << np.reciprocal_period(i) << ", ";
    }
    // ok(mxi);
}

void test_gcd()
{
    number_properties<int> np;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        int x, y;
        int g = np.extended_gcd(a, b, x, y);
        cout << a << "*(" << x << ") + (" << y << ")*" << b << " = " << g << endl;
    }
}

int main()
{
    test_cyc();
    return 0;
}
