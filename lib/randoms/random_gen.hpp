#pragma once

#include <random>
#include <chrono>
#include <functional>

namespace random_gens
{
    template <typename I, class E = std::mt19937>
    std::_Bind<std::uniform_int_distribution<I>(E)> uniform_int(I a, I b)
    {
        std::uniform_int_distribution<I> unf(a, b);
        return bind(unf, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    template <typename R, class E = std::mt19937>
    std::_Bind<std::uniform_real_distribution<R>(E)> uniform_real(R a, R b)
    {
        std::uniform_real_distribution<R> unf(a, b);
        return bind(unf, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    template <typename R, class E = std::mt19937>
    std::_Bind<std::bernoulli_distribution(E)> bernoulli(R p_true)
    {
        std::bernoulli_distribution ber(p_true);
        return bind(ber, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    template <typename I, typename R, class E = std::mt19937>
    std::_Bind<std::binomial_distribution<I>(E)> binomial(I n, R p_success)
    {
        std::binomial_distribution<I> bino(n, p_success);
        return bind(bino, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    // distribution of failure before a given number of success
    template <typename I, typename R, class E = std::mt19937>
    std::_Bind<std::negative_binomial_distribution<I>(E)> neg_binomial(I success_count, R p_success)
    {
        std::negative_binomial_distribution<I> nbino(success_count, p_success);
        return bind(nbino, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    template <typename I, typename R, class E = std::mt19937>
    std::_Bind<std::poisson_distribution<I>(E)> poisson(R lambda)
    {
        std::poisson_distribution<I> poisson(lambda);
        return bind(poisson, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    // counts number of failures
    template <typename I, typename R, class E = std::mt19937>
    std::_Bind<std::geometric_distribution<I>(E)> geometric(R p)
    {
        std::geometric_distribution<I> geom(p);
        return bind(geom, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    // 0 to n-1
    template <typename I, class E = std::mt19937>
    std::_Bind<std::discrete_distribution<I>(E)> discrete(std::vector<I> p)
    {
        std::discrete_distribution<I> dist = p;
        return bind(dist, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    // continious
    template <typename I,  typename R, class E = std::mt19937>
    std::_Bind<std::exponential_distribution<R>(E)> expo(R lambda)
    {
        std::exponential_distribution<R> expontial(lambda);
        return bind(expontial, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    template <typename R, class E = std::mt19937>
    std::_Bind<std::gamma_distribution<R>(E)> gamma(R alpha, R beta)
    {
        std::gamma_distribution<R> gam(alpha, beta);
        return bind(gam, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    template <typename R, class E = std::mt19937>
    std::_Bind<std::weibull_distribution<R>(E)> weibull(R a, R b)
    {
        std::weibull_distribution<R> weibull(a, b);
        return bind(weibull, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    template <typename R, class E = std::mt19937>
    std::_Bind<std::extreme_value_distribution<R>(E)> extreme(R a, R b)
    {
        std::extreme_value_distribution<R> extr(a, b);
        return bind(extr, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    // p(x|x_i<= x < x_i+1) = p[i]
    template <typename R, class E = std::mt19937>
    std::_Bind<std::piecewise_constant_distribution<R>(E)> piecewise(std::vector<R> p, std::vector<R> x)
    {
        std::piecewise_constant_distribution<R> x_with_p(x.begin(), x.end(), p.begin());
        return bind(x_with_p, E(std::chrono::steady_clock::now().time_since_epoch().count()));
    }
};