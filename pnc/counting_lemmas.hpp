#pragma once
#include <vector>
#include <iostream>
// FIXME add other counting lemmas and methods
#include "permutations.hpp"

// given a set of objects (f) which can be represented by a permutations of size `n`
// lets say there are some permuattion `pi` which when applied to any of the object 
// leaves the structrue of object unchanged but may make 2 different object same 
// i.e. `f1 = f2*pi` now say we make equavalance classes on (f)'s
// and now we need to count the number of such equavaalnt classes
// lets G be the group of such structure preserving permutations
template <typename I, I mod>
class burnside_lemma
{
    public:
    std::vector<permutation<I>> pi;
    I n;
    burnside_lemma(I n,const std::vector<permutation<I>> &_pi)
    {
        this->pi = _pi;
        this->n = n;
    }

    I pr(I a, I n)
    {
        I ta = 1;
        while(n>0)
        {
            if(n%2==1)
            {
                ta = (ta*a)%mod;
            }
            n>>=1;
            a=(a*a)%mod;
        }
        return ta;
    }

    virtual I number_of_fixed_points(const permutation<I>& p)
    {
        std::cerr<<"Write the code to calculate number of fixed points"<<std::endl;
        return 0;
    }

    // may overload it to compute faster
    virtual I num_eq_classes()
    {
        I eq = 0;
        for(I i=0;i<this->n;i++)
        {
            eq = (eq + this->number_of_fixed_points(this->pi[i]))%mod;
        }
        eq = (((I)this->pr(this->n,mod-2))*eq)%mod;
        return eq;
    }
};


template <typename I, I mod>
class polya_enumeration_theorem
{
    public:
    std::vector<permutation<I>> pi;
    I n;
    I k;
    polya_enumeration_theorem(){}
    polya_enumeration_theorem(I n, I k, const std::vector<permutation<I>> &_pi)
    {
        this->pi = _pi;
        this->n = n;
        this->k = k;
    }

    I pr(I a, I n)
    {
        I ta = 1;
        while(n>0)
        {
            if(n%2==1)
            {
                ta = (ta*a)%mod;
            }
            n>>=1;
            a=(a*a)%mod;
        }
        return ta;
    }

    virtual I number_of_cycles_in_pi(const permutation<I>& p)
    {
        std::cerr<<"Write the code to calculate number of cycles in the permutation"<<std::endl;
        return 0;
    }

    // may overload it to compute faster
    virtual I num_eq_classes()
    {
        I eq = 0;
        for(I i=0;i<this->n;i++)
        {
            eq = (eq + this->pr(this->k,this->number_of_cycles_in_pi(this->pi[i])))%mod;
        }
        eq = (((I)this->pr(this->n,mod-2))*eq)%mod;
        return eq;
    }
};