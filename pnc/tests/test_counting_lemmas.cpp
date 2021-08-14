#include <bits/stdc++.h>
#include "../counting_lemmas.hpp"
#include "../permutations.hpp"

typedef long long ll;

using namespace std;

template <typename I, I mod>
class necklace_coloring : public polya_enumeration_theorem<I, mod>
{
    public:
    necklace_coloring(I n, I k, vector<permutation<I>> &_pi) : polya_enumeration_theorem<I, mod>(n,k,_pi){}

    I number_of_cycles_in_pi(const permutation<I> &p)
    {
        return __gcd(p[0]+1ll,this->n);
    }
    
    I num_eq_classes()
    {
        auto phi = [](I n)
        {
            I ans = 1;
            if(n%2==0)
            {
                n/=2;
            }
            while (n%2==0)
            {
                ans = (ans*2);
                n/=2;
            }
            
            I i=3;
            while (i*i<=n)
            {
                if(n%i==0)
                {
                    ans = (ans*(i-1ll));
                    n/=i;
                }
                while (n%i==0)
                {
                    ans = (ans*i);
                    n/=i;
                }
                i+=2ll;
            }

            if(n>1ll)
            {
                ans = (ans*(n-1ll));
            }
            return ans;
        };

        I ans=0;
        I i = 1;
        while (i*i<=this->n)
        {
            if(this->n%i==0)
            {
                ans = (ans + (this->pr(this->k,i)*phi(this->n/i))%mod)%mod;
                if(i*i!=this->n)  ans = (ans + (this->pr(this->k,this->n/i)*phi(i))%mod)%mod;
            }
            i++;
        }

        ans = (this->pr(this->n,mod-2)*ans)%mod;
        return ans;
    }

};

int main()
{
    ll n;
    n = 200;
    vector<permutation<ll>> vp(n,permutation<ll>(n));
    for(ll i=0;i<n;i++)
    {
        vp[i]>>=i;
    }

    necklace_coloring<ll,1000000007ll> nc(n,2ll,vp);
    cout<<nc.num_eq_classes()<<endl;

    return 0;
}