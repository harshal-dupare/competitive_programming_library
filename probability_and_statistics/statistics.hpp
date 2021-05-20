#pragma once

using namespace std;

#include <iostream>
#include <vector>
#include <random>
#include <limits>

template<typename T>
struct report
{
    double p_limit=0.05;
    double p_value;
    bool significant=false;
    void negative_tail(T statistic, double (*F0x)(T))
    {
        this->p_value=F0x(statistic);
        if(this->p_value<=this->p_limit) significant=true;
        else significant = false;
    }

    void positive_tail(T statistic, double (*F0x)(T))
    {
        this->p_value=this->p_value=1.0-F0x(statistic);
        if(this->p_value<=this->p_limit) significant=true;
        else significant = false;
    }

    void both_tail(T neg_statistic, T pos_statistic, double (*F0x)(T))
    {
        this->p_value=this->p_value=1.0-F0x(pos_statistic)+F0x(neg_statistic);
        if(this->p_value<=this->p_limit) significant=true;
        else significant = false;
    }

};

template<typename T>
T static_mean(std::vector<T>& a)
{
    T sum = 0;
    T n = (T)a.size();
    for(auto x: a)
    {
        sum+=x;
    }

    return (sum/n);
}

template<typename T>
T variation(std::vector<T>& a, T mean, T lost_degree_of_freedom)
{
    T n = (T)a.size();
    T sd=0;
    for(auto x: a)
    {
        sd+=(x-mean)*(x-mean);
    }

    return (sd/(n-lost_degree_of_freedom));
}

template<typename T>
T variation(std::vector<T>& a)
{
    T mean = static_mean(a);
    T n = (T)a.size();
    T sd=0;
    for(auto x: a)
    {
        sd+=(x-mean)*(x-mean);
    }

    return (sd/(n-1));
}

