#pragma once
#include <vector>
#include <complex>

template <typename I>
class prime_tests
{
public:
    std::vector<I> spl_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    
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
