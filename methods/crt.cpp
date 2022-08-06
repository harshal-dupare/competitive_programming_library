#include <bits/stdc++.h>
#include "../utils/debug_out.hpp"

using namespace std;
using ll = long long;
using vll = vector<ll>;
const ll mod = 1e9L+7ll;
vector<ll> largest_pfact;

void sieve(ll N)
{
    largest_pfact.resize(N+1,-1);
    for(ll i=2;i<=N;i++)
    {
        if(largest_pfact[i]!=-1) continue;
        largest_pfact[i] = i;
        for(ll j = 2*i;j<=N;j+=i)
        {
            largest_pfact[j] = i;
        }
    }
}

ll pr(ll x, ll n, ll p=mod)
{
    ll tx = 1;
    while(n>0)
    {
        if(n%2==1)
        {
            if(p==-1)
            {
                tx*=x;
            }
            else
            {
                tx=(tx*x)%p;
            }
        }
        n>>=1;
        if(p==-1)
        {
            x*=x;
        }
        else
        {
            x=(x*x)%p;
        }
    }
    return tx;
}

map<ll,ll> get_facts(ll n)
{
    map<ll,ll> fcts;
    while(n>1)
    {
        fcts[largest_pfact[n]]++;
        n/=largest_pfact[n];
    }
    return fcts;
}

ll phi(ll n)
{
    map<ll,ll> fcts = get_facts(n);
    ll ans = 1;
    for(auto x: fcts)
    {
        ans*=(x.first-1)*pr(x.first,x.second-1,-1);
    }
    return ans;
}

ll CRT(vll &a, vll& p)
{
    ll n = p.size();
    vll x(n);
    vll phip(n);
    for(ll i=0;i<n;i++)
    {
        ll prev = a[i]%p[i];
        phip[i] = phi(p[i]);
        for(ll j=0;j<i;j++)
        {
            prev = prev - x[j];
            if(prev<0)prev+=p[i];
            prev=(prev*pr(p[j],phip[i]-1,p[i]))%p[i];
        }
        x[i] = prev;
    }

    ll ppi =1;
    ll ans = 0;
    for(ll i=0;i<n;i++)
    {
        ans+=x[i]*ppi;
        ppi*=p[i];
    }
    if(ans==0)
    {
        ans=1;
        for(ll i=0;i<n;i++)
        {
            ans*=p[i];
        }
    }
    return ans;
}

ll get_low(ll x)
{
    map<ll,ll> fcts = get_facts(x);
    vector<pair<ll,ll>> fpll;
    for(auto x: fcts)
    {
        fpll.emplace_back(x.first,x.second);
    }
    ll n = fpll.size();
    if(n==0) return 1;
    ll k = 1<<n;
    ll x_min = mod+1;
    for(ll i=1;i<k;i++)
    {
        ll p1=1,p2=1;
        ll id = 0;
        ll ti=i;
        while(ti>0)
        {
            if(ti%2==1)
            {
                p1*=pr(fpll[id].first,fpll[id].second,-1ll);
            }
            ti>>=1;
            id++;
        }
        p2=x/p1;
        vll a{0ll,p2-1ll};
        vll pl{p1,p2};
        ll x_candi = CRT(a,pl);
        x_min = min(x_candi,x_min);
    }

    return x_min;
}

int main()
{

    sieve(10000ll);

    for(ll i=1;i<30;i++)
    {
        cout<<get_low(i)<<" ";
    }
    cout<<endl;
    while (true)
    {
        ll n;
        cin>>n;
        vll a(n),p(n);
        for(ll i=0;i<n;i++)
        {
            cin>>a[i]>>p[i];
        }
        ll ans = CRT(a,p);
        cout<<ans<<endl;
    }
    
    return 0;
}