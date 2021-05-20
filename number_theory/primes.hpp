

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
