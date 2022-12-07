#pragma once
// refer : https://en.wikipedia.org/wiki/Reservoir_sampling
#include <assert.h>
#include <random>
#include <chrono>
#include <functional>
#include <array>
#include <algorithm>
#include "random_gen.hpp"

namespace random_sampling
{
    using namespace std;
    /**
     * @tparam I type of integer to use
     * @tparam E random number generator class, must have range over type `I`
     **/
    template<typename I,class E = std::mt19937>
    class reservoir_R_sampler
    {
    public:
        I k;
        I n;
        std::vector<I> samples;
        E rng;
        /**
         * Time Complexity: 
         * ---> O( n + (n-k) * |time_to_generate_random_number(E)| )
         * Random bits required: 
         * ---> (n-k)*|bits in E's output|
         **/
        reservoir_R_sampler(I k, I r_seed)
        {
            this->k = k;
            this->n = k;
            this->samples = vector<I>(k);
            std::iota(this->samples.begin(),this->samples.end(),0);
            this->rng = E(r_seed);
        }
        /**
         * @param id: 0-indexed, id >= k, assumes that input is given from the k+1 element
         * @returns id at which this element is selected, -1 if not selected
         **/
        I process_next_new_element(I id)
        {
            assert(id==this->n);
            this->n++;
            I rn = this->rng()%this->n;
            if(rn<this->k)
            {
                this->samples[rn] = id;
                return rn;
            }
            return (I)-1;
        }
    };

    template<typename I,class E = std::mt19937>
    void reservoir_R_sampler_static(I n, I k, I r_seed, std::vector<I> & samples)
    {
        assert(n>=k);
        samples = vector<I>(k);
        std::iota(samples.begin(),samples.end(),(I)0);
        E rng = E(r_seed);
        for(I i=k;i<n;i++)
        {
            I rn = rng()%n;
            if(rn<k)
            {
                samples[rn] = i;
            }
        }
        return;
    }

    /**
     * @tparam I type of integer to use
     * @tparam E random number generator class, must have range over type `I`
     **/
    template<typename I,typename R,class E = std::mt19937>
    class reservoir_L_sampler
    {
    public:
        I k;
        std::vector<I> samples;
        I accept_id;
        R w;
        R ik;

        E rng_i;
        std::uniform_real_distribution<R> unf;
        std::_Bind<std::uniform_real_distribution<R>(E)> rng_u01;

        /**
         * Time Complexity: 
         * ---> O_E( k + k*log(n/k) )
         * Random bits required: 
         * ---> Expected : 3*k*log(n/k)*|bits in E's output|
         **/
        reservoir_L_sampler(I k, I r_seed)
        {
            this->k = k;
            this->samples = vector<I>(k);
            std::iota(this->samples.begin(),this->samples.end(),0);
            this->rng_i = E(r_seed);
            this->unf = std::uniform_real_distribution<R>((R)0, (R)1);
            this->rng_u01 = bind(unf, this->rng_i);
            this->w = rng_u01();
            this->ik = (R)1/((R)k);
            this->w = pow(this->w,this->ik);
            this->accept_id= k + (I)floor(log(this->rng_u01())/log((R)1.0-this->w));
        }
        /**
         * id's must be given in sequential order, you can use accept_id to know which next element will be accepted
         * @param id: 0-indexed, id >= k, assumes that input is given from the k+1 element
         * @returns id at which this element is selected, -1 if not selected
         **/
        I process_next_new_element(I id)
        {
            if(id!=this->accept_id)
            {
                return (I)-1;
            }
            accept_id += 1 + (I)floor(log(this->rng_u01())/log((R)1.0-this->w));
            I loc = this->rng_i()%this->k;
            samples[loc] = id;

            R _mw = this->rng_u01();
            _mw = pow(_mw,this->ik);
            this->w *= _mw;
            return loc;
        }
    };

    template<typename I, typename R,class E = std::mt19937>
    void reservoir_L_sampler_static(I n, I k, I r_seed, std::vector<I> & samples)
    {
        assert(n>=k);
        samples = vector<I>(k);
        std::iota(samples.begin(),samples.end(),(I)0);
        std::uniform_real_distribution<R> unf((R)0, (R)1);
        // need to study how will this behave when one rng is used to bind will it
        // create new isntance and use it or use same instance
        E rng_i = E(r_seed);
        std::_Bind<std::uniform_real_distribution<R>(E)> rng_u01 = bind(unf, rng_i);

        R w = rng_u01();
        R ik = (R)1/((R)k);
        w = pow(w,ik);

        I i=k-1;
        while (i<n)
        {
            i += 1 + (I)floor(log(rng_u01())/log((R)1.0-w));
            if(i<n)
            {
                samples[rng_i()%k] = i;
                R _mw = rng_u01();
                _mw = pow(_mw,ik);
                w *= _mw;
            }
        }
        return;
    }

}