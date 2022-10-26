#pragma onces
#include <vector>
#include <complex>
#include <algorithm>
#include <unordered_map>
#include <iostream>
// FIXME Lcm Gcd of sets
template <typename I>
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

template <typename I>
I lcm(I a, I b)
{
    if (a == 0 && b == 0)
        return 0;

    return a * b / gcd(a, b);
}

template <typename I>
I extended_gcd(I n0, I n1, I &n0cn0, I &n0cn1)
{
    // n_(i+1) < n_i
    n0cn0 = 1, n0cn1 = 0;   // n0 = n1*n0cn1 + n0*n0cn0 = (n0cn1, n0cn0)
    I n1cn0 = 0, n1cn1 = 1; // n1 = n1*n1cn1 + n0*n1cn0  = (n1cn1, n1cn0)

    // k = n0/n1
    // n2 = n0  - n1*k --> n_(i+1) = n_(i-1) - k*n_(i)
    // n2 = (n0cn1-k*n1cn1, n0cn0-k*n1cn0) -> new n1
    // n1 = (        n1cn1,         n1cn0) -> new n0

    while (n1 > 0)
    {
        I k = n0 / n1;
        std::tie(n0, n1) = std::make_pair(n1, n0 % n1);
        std::tie(n0cn0, n1cn0) = std::make_pair(n1cn0, n0cn0 - k * n1cn0);
        std::tie(n0cn1, n1cn1) = std::make_pair(n1cn1, n0cn1 - k * n1cn1);
    }

    return n0;
}

template <typename I>
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

template <typename I>
I lcm_set(std::vector<I> &s)
{
    I ans = lcm(s[0], s[1]);
    for (I i = 2; i < s.size(); i++)
    {
        ans = lcm(ans, s[i]);
    }
    return ans;
}

template <typename I>
I mmult(I a, I b, I p)
{
    return (p + (a * b) % p) % p;
}

template <typename I>
I madd(I a, I b, I p)
{
    return (p + (a + b) % p) % p;
}

template <typename I>
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

template <typename I>
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
            qr *= quadratic_residues(x.first, p);
        }
    }

    return qr;
}

// O(a^(1/2)+phi(n))
template <typename I>
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
template <typename I>
I order_mod_n(I a, I k, I n)
{
    I base_ord = order_mod_n(a, n);
    if (base_ord == -1)
        return -1;

    return base_ord / gcd(base_ord, k);
}

// O(n^(1/2)+p1^k1+p2^k2+..+pn^kn) where pi^ki's are max power of primes dividing n
template <typename I>
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
template <typename I>
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
template <typename I>
I modified_frobenius(std::vector<I> &nl, bool brute_force = false)
{
    if (nl.size() == 2)
    {
        return nl[0] * nl[1];
    }

    I n = nl.size();
    if (brute_force)
    {
        std::sort(nl.begin(), nl.end());

        I estimate = -1;
        for (I i = 0; i < n; i++)
        {
            for (I j = i + 1; j < n; j++)
            {
                if (gcd(nl[i], nl[j]) == 1)
                {
                    if (estimate == -1)
                    {
                        estimate = nl[i] * nl[j] - nl[i] - nl[j];
                    }
                    else
                    {
                        estimate = std::min(nl[i] * nl[j] - nl[i] - nl[j], estimate);
                    }
                }
            }
        }

        assert(estimate <= 100000);

        std::vector<bool> poss(estimate + 3);
        poss[0] = true;
        I all_sum = 0;
        for (I i = 0; i < n; i++)
        {
            all_sum += nl[i];
            for (I j = 0; j + nl[i] <= estimate + 2; j++)
            {
                if (poss[j])
                {
                    poss[j + nl[i]] = true;
                }
            }
        }

        I i = estimate;
        while (poss[i] && (i >= 0))
        {
            i--;
        }

        return i + all_sum;
    }

    std::vector<I> lgcd(n, (I)1), rgcd(n, (I)1), rsum(n, (I)0), lsum(n, (I)0);

    rsum[n - 1] = 0;
    lsum[0] = 0;
    rgcd[0] = 0;
    lgcd[n - 1] = 0;
    for (I i = 1; i < n; i++)
    {
        lsum[i] = lsum[i - 1] + nl[i - 1];
        lgcd[i] = gcd(lgcd[i - 1], nl[i - 1]);
    }
    for (I i = n - 2; i >= 0; i--)
    {
        rsum[i] = rsum[i + 1] + nl[i + 1];
        rgcd[i] = gcd(lgcd[i + 1], nl[i + 1]);
    }

    I max_d = 0, j = 0;
    for (I i = 0; i < n; i++)
    {
        lsum[i] += rsum[i];
        lgcd[i] = gcd(lgcd[i], rgcd[i]);
        if (lgcd[i] >= max_d)
        {
            max_d = lgcd[i];
            j = i;
        }
    }
    I ans = 0;
    if (max_d > 1)
    {
        for (I i = 0; i < n; i++)
        {
            if (i != j)
            {
                nl[i] /= max_d;
            }
        }

        ans = modified_frobenius(nl);
        ans *= max_d;
        ans -= (max_d - 1) * lsum[j];
    }
    else
    {
        ans = modified_frobenius(nl, true);
    }
    return ans;
}

template <typename I>
I forbenius(std::vector<I> &nl)
{
    if (nl.size() == 1)
    {
        if (nl[0] == 1)
        {
            return -1;
        }
        return 0;
    }
    I ans = modified_frobenius(nl);
    for (auto x : nl)
    {
        ans -= x;
    }
    return ans;
}

// need to debug
// reciprocal period of 1/n in O(n^(1/2)+p1^k1+p2^k2+..+pn^kn) where pi^ki's are max power of primes dividing n
template <typename I>
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
            ans = lcm(fract_period(1, fcts[j].second), ans);
        }
    }

    return ans * other_fact;
}

// reciprocal period of p/q in O(q)
template <typename I>
I fract_period(I p, I q)
{
    std::unordered_map<I, I> lstoccr;
    // I gc = gcd(p, q);
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

// solving for k*a^x=b mod(m)
// methode used x = p*n-q so eq becomes  k*(a^n)^p = b*a^q mod(m)
// f1 = f2 mod(m), meet in the middle method
// as x lies in intervl (0,m) so searching between range of p in (1,m/n) and q in (1,n)
template <typename I>
I discrete_log(I k, I a, I b, I m)
{
    a %= m;
    b %= m;
    if (a == 0)
        return -1;
    I g = __gcd(a, m);
    if (g != (I)1)
    {
        if (b % g != 0)
            return -1;
        // multiply LHS by a and then reduce the eq to new eq
        // and solve for x- if g > 1 else for x
        // at the end add 1 if g > 1
        // k *(a/g) a^(x-1) = (g/b) mod(m/g)
        m /= g;
        k = (k * (a / g)) % m;
        b /= g;
        b %= m;
    }

    I n = 1;
    while (n * n < m)
        n++;

    unordered_map<I, I> f2;
    for (I i = 0; i <= n; i++)
    {
        f2[b] = i;
        b = (b * a) % m;
    }
    I an = 1;
    I ta = a;
    I tn = n;
    while (tn > 0)
    {
        if (tn % 2 == 1)
        {
            tn >>= 1;
            an = (an * ta % m);
        }
        ta = (ta * ta) % m;
    }

    b = (k * an) % m;
    for (I i = 1; i * m <= n + m - 1; i++)
    {
        if (f2.count(b))
        {
            return i * m - f2[b] + (g > 1 ? 1 : 0);
        }
        b = (b * an) % m;
    }

    return -1;
}
