#pragma once

using namespace std;

#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <functional>
#include "../randoms/random_gen.hpp"
// FIXME define scope andfind fuc and methods to add
// FIXME correctness of known methods

template <typename T>
struct report
{
    double p_limit = 0.05;
    double p_value;
    bool significant = false;
    void negative_tail(T statistic, double (*F0x)(T))
    {
        this->p_value = F0x(statistic);
        if (this->p_value <= this->p_limit)
            significant = true;
        else
            significant = false;
    }

    void positive_tail(T statistic, double (*F0x)(T))
    {
        this->p_value = this->p_value = 1.0 - F0x(statistic);
        if (this->p_value <= this->p_limit)
            significant = true;
        else
            significant = false;
    }

    void both_tail(T neg_statistic, T pos_statistic, double (*F0x)(T))
    {
        this->p_value = this->p_value = 1.0 - F0x(pos_statistic) + F0x(neg_statistic);
        if (this->p_value <= this->p_limit)
            significant = true;
        else
            significant = false;
    }
};

template <typename T>
T static_mean(std::vector<T> &a)
{
    T sum = 0;
    T n = (T)a.size();
    for (auto x : a)
    {
        sum += x;
    }

    return (sum / n);
}

template <typename T>
T variation(std::vector<T> &a, T mean, T lost_degree_of_freedom)
{
    T n = (T)a.size();
    T sd = 0;
    for (auto x : a)
    {
        sd += (x - mean) * (x - mean);
    }

    return (sd / (n - lost_degree_of_freedom));
}

template <typename T>
T variation(std::vector<T> &a)
{
    T mean = static_mean(a);
    T n = (T)a.size();
    T sd = 0;
    for (auto x : a)
    {
        sd += (x - mean) * (x - mean);
    }

    return (sd / (n - 1));
}

// given a sequence of elements at any point output a random element uniformaly from the numbers seen so far
// note we cant query 2 times in a row without adding a new element as it will give same value
template <typename T, typename R = double, class E = std::mt19937>
class online_sample_uniform_random
{
    T a;
    R n;
    R lq;
    std::_Bind<std::uniform_real_distribution<R>(E)> gen;

public:
    online_sample_uniform_random()
    {
        n = (R)0;
        lq = (R)0;
        gen = random_gens::uniform_real<R, E>(0.0, 1.0);
    }
    online_sample_uniform_random(const T &_a)
    {
        a = _a;
        n = (R)1;
        lq = (R)0;
        gen = random_gens::uniform_real<R, E>(0.0, 1.0);
    }

    void add(T &x)
    {
        n++;
        if (n * gen() <= (R)1.0)
            a = x;
    }

    T get()
    {
        assert(lq != n); // cant query more than once consequtively as it will give same number
        lq = n;
        return a;
    }
};