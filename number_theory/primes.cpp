#include <bits/stdc++.h>
#include "../utils/timer.h"

using namespace std;

template <typename I>
class prime_tests
{
public:
    // O(0.167*n^(1/2))
    bool check_till_root(I n)
    {
        if (n == 1)
            return false;
        if (n == 2 || n == 3)
            return true;
        if (n % 2 == 0 || n % 3 == 0)
            return false;

        I d = 6;
        while ((d - 1) * (d - 1) <= n)
        {
            if (n % (d + 1) == 0 || n % (d - 1) == 0)
                return false;

            d += 6;
        }

        return true;
    }

    // O(log(p))
    I Pt_power(I a, I p, I k = -1)
    {
        if (p == 2)
            return a;

        if (k == -1)
            k = p - 1;
        I ans = 1;
        I pr = a;
        while (k > 0)
        {
            if ((k & 1) == 1)
            {
                ans = (p + (ans * pr) % p) % p;
            }
            pr = (p + (pr * pr) % p) % p;
            k >>= 1;
        }

        return ans;
    }

    // O(C*log(p))
    bool fermat_check(I p, I confidence = 100)
    {
        if (p < 10)
        {
            if (p == 2 || p == 3 || p == 5 || p == 7)
                return true;
            else
                return false;
        }

        confidence = min(confidence, p - 1);

        while (confidence--)
        {
            I a = 2 + (abs(rand()) % (p - 3));
            // cout << a << endl;
            if (this->Pt_power(a, p) != 1)
                return false;
        }

        return true;
    }

    // O(C*log(p)^2)
    bool prob_miller_check(I p, I confidence = 100)
    {
        if (p < 10)
        {
            if (p == 2 || p == 3 || p == 5 || p == 7)
                return true;
            else
                return false;
        }

        if ((p & 1) == 0)
            return false;

        // decompose p = 2^s*d + 1
        I d = p - 1;
        I s = 0;
        while ((d & 1) == 0)
        {
            s++;
            d >>= 1;
        }

        confidence = min(confidence, p - 1);

        while (confidence--)
        {
            I a = 2 + (abs(rand()) % (p - 3));
            bool satisfy = false;
            if (this->Pt_power(a, p, d) == 1)
            {
                satisfy = true;
            }
            else
            {
                int ts = s;
                while (ts > 0)
                {
                    if ((this->Pt_power(a, p, d) + 1) % p == 0)
                    {
                        satisfy = true;
                        break;
                    }
                    d <<= 1;
                    --ts;
                }
            }

            if (!satisfy)
            {
                return false;
            }
        }

        return true;
    }

    // O(log(p)^2)
    bool deter_miller_check(I p)
    {
        if (p < 10)
        {
            if (p == 2 || p == 3 || p == 5 || p == 7)
                return true;
            else
                return false;
        }

        if ((p & 1) == 0)
            return false;

        // decompose p = 2^s*d + 1
        I d = p - 1;
        I s = 0;
        while ((d & 1) == 0)
        {
            s++;
            d >>= 1;
        }
        vector<I> spl_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
        for (I a : spl_primes)
        {
            if (a == p)
                return true;

            bool satisfy = false;
            if (this->Pt_power(a, p, d) == 1)
            {
                satisfy = true;
            }
            else
            {
                int ts = s;
                while (ts > 0)
                {
                    if ((this->Pt_power(a, p, d) + 1) % p == 0)
                    {
                        satisfy = true;
                        break;
                    }
                    d <<= 1;
                    --ts;
                }
            }

            if (!satisfy)
            {
                return false;
            }
        }

        return true;
    }
};

template <typename I>
class primes
{
public:
    I max_prime;
    I largest_prime;
    vector<I> smallest_prime_factor;
    vector<I> ith_prime;

    primes(I max_prime)
    {
        this->max_prime = max_prime;
        this->smallest_prime_factor = vector<I>(max_prime + 2);
    }

    // O(log(p))
    I Pt_power(I a, I p, I k = -1)
    {
        if (p == 2)
            return a;

        if (k == -1)
            k = p - 1;
        I ans = 1;
        I pr = a;
        while (k > 0)
        {
            if ((k & 1) == 1)
            {
                ans = (p + (ans * pr) % p) % p;
            }
            pr = (p + (pr * pr) % p) % p;
            k >>= 1;
        }

        return ans;
    }

    // O(nlog(log(n))) time
    void sieve()
    {
        for (I i = 1; i <= this->max_prime; i++)
            this->smallest_prime_factor[i] = i;

        for (I i = 2; i * i <= this->max_prime; i++)
            if (this->smallest_prime_factor[i] == i)
                for (I j = i + i; j <= this->max_prime; j += i)
                    if (this->smallest_prime_factor[j] == j)
                        this->smallest_prime_factor[j] = i;
        for (I i = 2; i <= this->max_prime; i++)
            if (this->smallest_prime_factor[i] == i)
                this->ith_prime.push_back(i);

        this->ith_prime.shrink_to_fit();
        this->largest_prime = this->ith_prime[this->ith_prime.size() - 1];
    }

    // O(w(x)) <= O(log(x)) or O(PI(max_prime)) OR O(PI(max_prime)+0.167*(x-max_prime)^0.5)
    map<I, I> factorize(I x)
    {
        map<I, I> res;
        if (x <= this->max_prime)
        {
            while (x > 1)
            {
                res[this->smallest_prime_factor[x]]++;
                x /= this->smallest_prime_factor[x];
            }
        }
        else if (x <= (this->max_prime * this->max_prime))
        {
            I i = 0;
            // O(MAX_ITH_PRIME)
            while (x > 1 && i < this->ith_prime.size())
            {
                if (x % this->ith_prime[i] == 0)
                {
                    res[this->ith_prime[i]]++;
                    x /= this->ith_prime[i];
                }
                else
                {
                    i++;
                }
            }

            if (x > 1)
            {
                // x is a prime
                res[x] = 1;
            }
        }
        else
        {
            I i = 0;
            // O(MAX_ITH_PRIME)
            while (x > 1 && i < this->ith_prime.size())
            {
                if (x % this->ith_prime[i] == 0)
                {
                    res[this->ith_prime[i]]++;
                    x /= this->ith_prime[i];
                }
                else
                {
                    i++;
                }
            }

            if (x > 1)
            {
                I d = 6 * ((this->ith_prime[this->ith_prime.size() - 1]) / 6);
                while ((d - 1) * (d - 1) <= x)
                {
                    bool nxt = true;
                    if (x % (d - 1) == 0)
                    {
                        x /= (d - 1);
                        res[d - 1]++;
                        nxt = false;
                    }
                    if (x % (d + 1) == 0)
                    {
                        x /= (d + 1);
                        res[d + 1]++;
                        nxt = false;
                    }

                    if (nxt)
                        d += 6;
                }

                if (x > 1)
                {
                    res[x]++;
                }
            }
        }

        return res;
    }

    // O(0.167*(x)^0.5)
    map<I, I> factorize_id(I x)
    {
        map<I, I> res;
        while (x % 2 == 0)
        {
            x /= 2;
            res[2]++;
        }
        while (x % 3 == 0)
        {
            x /= 3;
            res[3]++;
        }

        I d = 6;
        while ((d - 1) * (d - 1) <= x)
        {
            bool nxt = true;
            if (x % (d - 1) == 0)
            {
                x /= (d - 1);
                res[d - 1]++;
                nxt = false;
            }
            if (x % (d + 1) == 0)
            {
                x /= (d + 1);
                res[d + 1]++;
                nxt = false;
            }

            if (nxt)
                d += 6;
        }

        if (x > 1)
            res[x]++;

        return res;
    }

    // O(w(n)) <= O(log(n)) time
    I euler_totient(I n)
    {
        auto factors = this->factorize(n);
        I et = 1;
        for (auto p : factors)
        {
            et *= (pow(p.first, p.second - 1) * (p.first - 1));
        }

        return et;
    }

    // O(w(n)) <= O(log(n)) time
    I factors_count(I n)
    {
        auto factors = this->factorize(n);
        I w = 1;
        for (auto p : factors)
        {
            w *= (p.second + 1);
        }

        return w;
    }
};


#define ll long long

int main()
{
    primes<ll> ps(100005);
    ps.sieve();
    int t;
    cin >> t;
    while (t-- > 0)
    {
        // prime testing tests
        // float t1 = 0, t2 = 0, t3 = 0, t4 = 0;
        // timer tm;
        // prime_tests<long long> pt;
        // int tt = t;
        // while (tt--)
        // {
        //     int n;
        //     // cin>>n;
        //     n = tt;
        //     // cout << n << ": ";
        //     tm.set();
        //     int a = pt.check_till_root(n);
        //     t1 += tm.get();
        //     // cout << a;

        //     tm.set();
        //     int b = (pt.fermat_check(n));
        //     t2 += tm.get();
        //     // cout << b;

        //     tm.set();
        //     int c = (pt.prob_miller_check(n));
        //     t3 += tm.get();
        //     // cout << c;

        //     tm.set();
        //     int d = (pt.deter_miller_check(n));
        //     t4 += tm.get();
        //     // cout << d << endl;
        // }

        // cout << t1 << ", " << t2 << ", " << t3 << ", " << t4 << endl;
        // t /= 10;

        // primes factor test
        ll n;
        cin >> n;
        for (auto x : ps.factorize_id(n))
        {
            cout << x.first << ":" << x.second << endl;
        }
        cout << endl;
    }
    return 0;
}

/*

10000000
14.3397, 64.8257, 94.5135, 39.9679
1.04883, 6.87673, 9.54103, 3.86097
0.0948232, 0.682812, 0.934151, 0.369178
0.00895428, 0.0667426, 0.0904803, 0.0345295
0.000891205, 0.00625259, 0.00827469, 0.00313209
8.65999e-05, 0.0003559, 0.000421, 0.0002045
9.4e-06, 9.5e-06, 3.83e-05, 9.9e-06
1.1e-06, 9e-07, 9e-07, 9e-07

100000
0.0952627, 0.587831, 0.79096, 0.320024
0.00903027, 0.0573916, 0.0765467, 0.0301386
0.000877906, 0.00542827, 0.0070421, 0.00274819
8.78e-05, 0.0003005, 0.0003645, 0.0002365
8.7e-06, 8.6e-06, 8.8e-06, 8.6e-06
1e-06, 9e-07, 8e-07, 9e-07

*/