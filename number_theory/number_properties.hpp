#pragma onces

#include <vector>
#include <complex>
#include <algorithm>
#include <unordered_map>
#include <iostream>

template <typename I>
class number_properties
{
public:
    I gcd(I n, I m)
    {
        n = std::abs(n);
        m = std::abs(m);
        while (m > 0)
        {
            I temp = m;
            m = n % m;
            n = temp;
            // std::tie(n, m) = std::make_pair(m, n % m);
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
            std::tie(x, xp) = std::make_pair(xp, x - k * xp);
            std::tie(y, yp) = std::make_pair(yp, y - k * yp);
            std::tie(n, n0) = std::make_pair(n0, n % n0);
        }

        return n;
    }

    I gcd_set(std::vector<I> &s)
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

    I lcm_set(std::vector<I> &s)
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
        std::vector<std::pair<I, I>> fcts;
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
        std::vector<I> fcts;
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
        std::vector<I> primes(1, 1);
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

    // MF(a1,...,an) = F(a1,...,an)+a1+..+an
    // Property MF(a1,...,an) = d*MF(a1,a2'.,an')-(d-1)*(a2'+..+an'), d = gcd(a1,..,an), ai=d*ai'
    I modified_frobenius(std::vector<I> &nl, bool brute_force=false)
    {
        if(nl.size()==2)
        {
            return nl[0]*nl[1];
        }

        I n = nl.size();
        if(brute_force)
        {
            std::sort(nl.begin(),nl.end());

            I estimate=-1;
            for(I i=0;i<n;i++)
            {
                for(I j=i+1;j<n;j++)
                {
                    if(this->gcd(nl[i],nl[j])==1)
                    {
                        if(estimate==-1)
                        {
                            estimate = nl[i]*nl[j]-nl[i]-nl[j];
                        }
                        else
                        {
                            estimate = std::min(nl[i]*nl[j]-nl[i]-nl[j],estimate);
                        }
                    }
                }
            }

            assert(estimate<=100000);

            std::vector<bool> poss(estimate+3);
            poss[0]=true;
            I all_sum=0;
            for(I i=0;i<n;i++)
            {
                all_sum+=nl[i];
                for(I j=0;j+nl[i]<=estimate+2;j++)
                {
                    if(poss[j])
                    {
                        poss[j+nl[i]]=true;
                    }
                }
            }

            I i = estimate;
            while(poss[i]&&(i>=0))
            {
                i--;
            }

            return i+all_sum;
        }
        
        std::vector<I> lgcd(n,(I)1), rgcd(n,(I)1), rsum(n,(I)0), lsum(n,(I)0);

        rsum[n-1]=0;
        lsum[0]=0;
        rgcd[0]=0;
        lgcd[n-1]=0;
        for(I i=1;i<n;i++)
        {
            lsum[i] = lsum[i-1]+nl[i-1];
            lgcd[i] = this->gcd(lgcd[i-1],nl[i-1]);
        }
        for(I i=n-2;i>=0;i--)
        {
            rsum[i] = rsum[i+1]+nl[i+1];
            rgcd[i] = this->gcd(lgcd[i+1],nl[i+1]);
        }

        I max_d=0,j=0;
        for(I i=0;i<n;i++)
        {
            lsum[i]+=rsum[i];
            lgcd[i]=this->gcd(lgcd[i],rgcd[i]);
            if(lgcd[i]>=max_d)
            {
                max_d = lgcd[i];
                j = i;
            }
        }
        I ans=0;
        if(max_d>1)
        {
            for(I i=0;i<n;i++)
            {
                if(i!=j)
                {
                    nl[i]/=max_d;
                }
            }

            ans = modified_frobenius(nl);
            ans*=max_d;
            ans-=(max_d-1)*lsum[j];
        }
        else
        {
            ans = modified_frobenius(nl,true);
        }
        return ans;
    }

    I forbenius(std::vector<I> &nl)
    {
        if(nl.size()==1)
        {
            if(nl[0]==1)
            {
                return -1;
            }
            return 0;
        }
        I ans = modified_frobenius(nl);
        for(auto x: nl)
        {
            ans -= x;
        }
        return ans;
    }

    // need to debug
    // reciprocal period of 1/n in O(n^(1/2)+p1^k1+p2^k2+..+pn^kn) where pi^ki's are max power of primes dividing n
    I reciprocal_period(I n)
    {
        std::vector<std::pair<I, I>> fcts;
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
        std::unordered_map<I, I> lstoccr;
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

            rem = ((I)10 * rem) % q;
            i++;
        }

        return period;
    }

};
