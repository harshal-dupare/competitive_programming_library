#include <bits/stdc++.h>
#include "../utils/debug_out.h"
#include "../utils/timer.h"

using namespace std;

typedef long long ll;

template <typename I, typename R, class E>
struct randoms
{
    unsigned seed;
    E rng;

    randoms()
    {
        this->seed = chrono::steady_clock::now().time_since_epoch().count();
        this->rng.seed(this->seed);
    }

    void reseed(unsigned _seed)
    {
        this->seed = _seed;
        this->rng.seed(this->seed);
    }

    std::_Bind<std::uniform_int_distribution<I>(E)> uniform_int(I a, I b)
    {
        uniform_int_distribution<I> unf(a, b);
        return bind(unf, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    std::_Bind<std::uniform_real_distribution<R>(E)> uniform_real(R a, R b)
    {
        uniform_real_distribution<R> unf(a, b);
        auto x = bind(unf, E(chrono::steady_clock::now().time_since_epoch().count()));
        return x;
    }

    std::_Bind<std::bernoulli_distribution(E)> bernoulli(R p_true)
    {
        bernoulli_distribution ber(p_true);
        return bind(ber, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    std::_Bind<std::binomial_distribution<I>(E)> binomial(I n, R p_success)
    {
        binomial_distribution<I> bino(n, p_success);
        return bind(bino, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    // distribution of failure before a given number of success
    std::_Bind<std::negative_binomial_distribution<I>(E)> neg_binomial(I success_count, R p_success)
    {
        negative_binomial_distribution<I> nbino(success_count, p_success);
        return bind(nbino, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    std::_Bind<std::poisson_distribution<I>(E)> poisson(R lambda)
    {
        poisson_distribution<I> poisson(lambda);
        return bind(poisson, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    // counts number of failures
    std::_Bind<std::geometric_distribution<I>(E)> geometric(R p)
    {
        geometric_distribution<I> geom(p);
        return bind(geom, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    // 0 to n-1
    std::_Bind<std::discrete_distribution<I>(E)> discrete(vector<I> p)
    {
        discrete_distribution<I> dist = p;
        return bind(dist, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    // continious
    std::_Bind<std::exponential_distribution<R>(E)> expo(R lambda)
    {
        exponential_distribution<R> expontial(lambda);
        return bind(expontial, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    std::_Bind<std::gamma_distribution<R>(E)> gamma(R alpha, R beta)
    {
        gamma_distribution<R> gam(alpha, beta);
        return bind(gam, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    std::_Bind<std::weibull_distribution<R>(E)> weibull(R a, R b)
    {
        weibull_distribution<R> weibull(a, b);
        return bind(weibull, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    std::_Bind<std::extreme_value_distribution<R>(E)> extreme(R a, R b)
    {
        extreme_value_distribution<R> extr(a, b);
        return bind(extr, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    // p(x|x_i<= x < x_i+1) = p[i]
    std::_Bind<std::piecewise_constant_distribution<R>(E)> piecewise(vector<R> p, vector<R> x)
    {
        piecewise_constant_distribution<R> x_with_p(x.begin(), x.end(), p.begin());
        return bind(x_with_p, E(chrono::steady_clock::now().time_since_epoch().count()));
    }

    void fill(vector<I> &a, I x, I y)
    {
        auto ugen = this->uniform_int(x, y);
        for (I i = 0; i < a.size(); i++)
        {
            a[i] = ugen();
        }
    }
};

void test()
{
    randoms<ll, double, std::mt19937> rd;
    ll n = 10, mxitr = 10;
    vector<ll> a(n);
    while (mxitr--)
    {
        rd.fill(a, 10, 15);
        debug(a);
    }
}

int main()
{
    test();
    return 0;
}