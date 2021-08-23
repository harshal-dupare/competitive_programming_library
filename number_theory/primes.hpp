#pragma once
#include <vector>
#include <complex>
// FIXME tests
template <typename I>
class prime_tests
{
public:
    I spl_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    
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

        confidence = std::min(confidence, p - 1);

        while (confidence--)
        {
            I a = 2 + (std::abs(rand()) % (p - 3));
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

        confidence = std::min(confidence, p - 1);

        while (confidence--)
        {
            I a = 2 + (std::abs(rand()) % (p - 3));
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
    std::vector<I> smallest_prime_factor;
    std::vector<I> ith_prime;

    primes(I max_prime)
    {
        this->max_prime = max_prime;
        this->smallest_prime_factor = std::vector<I>(max_prime + 2);
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

    // O(n) time
    void linear_sieve()
    {
        for (I i = 1; i <= this->max_prime; i++)
            this->smallest_prime_factor[i] = i;
        for (I i = 2; i <= this->max_prime; i++)
        {
            if(this->smallest_prime_factor[i]==i)
            {
                this->ith_prime.push_back(i);
            }
            for(I j=0;j<(I)this->ith_prime.size()&&this->ith_prime[j]<=this->smallest_prime_factor[i]&&this->ith_prime[j]*i<=this->max_prime;j++)
            {
                this->smallest_prime_factor[i*this->ith_prime[j]] = this->ith_prime[j];
            }
        }
        
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

    // O(n^1/3) factor fount dynamic
    I fast_factor_count(I n)
    {
        I ans = 1;
        I p_pr = 0;
        while(n%2==0)
        {
            p_pr++;
            n>>=1;   
        }
        ans *= p_pr+1;
        
        // O(n^1/3)
        for(I p=3;((I)(p*p)*p)<=n;p+=2)
        {
            p_pr=0;
            while(n%p==0)
            {
                p_pr++;
                n/=p;
            }
            ans *= p_pr+1;
        }
        
        // remaining n is of the form
        // n = 1
        if(n==(I)1)
        {
            return ans;
        }

        prime_tests<I> ptest;
        // n = p, O(n^1/3)
        if(ptest.deter_miller_check(n)==true)
        {
            return (I)2*ans;
        }
        
        // n = p^2
        I l=1,r=n;
        I rn=-1;
        while (l<r)
        {
            I mid = l+(r-l)/2;
            rn=n/mid;
            if(rn==mid)
            {
                if(n==rn*mid)
                {
                    l=r=rn=mid;
                }
                else
                {
                    l=r=mid;
                    rn=-1;
                }
                break;
            }
            if(rn<mid)
            {
                r=mid-1;
            }
            else
            {
                l=mid+1;
            }
        }
        if(rn!=-1)
        {
            return (I)3*ans;
        }

        // n = p*q
        return (I)4*ans;
    }

};
