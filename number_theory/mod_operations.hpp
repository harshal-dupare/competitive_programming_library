#pragma once

namespace mod_operations
{
    using ll = long long;
    ll mod=1000000007ll;
    ll one = 1ll;

    ll add(const ll a, const ll b)
    {
        return (a+b)%mod_operations::mod;
    }

    ll sub(const ll a, const ll b)
    {
        return (a+mod_operations::mod-b)%mod_operations::mod;
    }

    ll mult(const ll a,const ll b)
    {
        return (a*b)%mod_operations::mod;
    }

    ll power(ll a, ll n)
    {
        ll ta=1;
        while(n>0)
        {
            if(n&mod_operations::one)
            {
                ta = (ta*a)%mod_operations::mod;
            }
            n>>=1;
            a = (a*a)%mod_operations::mod;
        }
        return ta;
    }

    ll inv(const ll a)
    {
        return mod_operations::power(a,mod_operations::mod-2);
    }

}

