#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
// #include "int_base.hpp"
#include "../bigint.hpp"
#include "../../randoms/random_gen.hpp"

using namespace std;

// typedef int_base<int, 13> intb;
typedef bigint<long long, 2> bint;
typedef bigint<long long, 5> bint2;
typedef long long ll;

vector<pair<ll,ll>> add,sub,mult,diver,qut;
vector<ll> assig,inc,erdec;

void check_assign()
{
    ll n;
    cin>>n;
    bint x;
    for(ll i=-n;i<=n;i++)
    {
        x=i;
        if(x.get_int()!=i)
        {
            assig.push_back(i);
            break;
        }
        x++;
        if(x.get_int()!=i+1)
        {
            inc.push_back(i);
        }
        x=i;
        x--;
        if(x.get_int()!=i-1)
        {
            erdec.push_back(i);
        }
    }
    debug(inc);
    debug(erdec);
    debug(assig);

    cin>>n;
    auto rg = random_gens::uniform_int<ll>(-10000000000ll,10000000000ll);
    bint2 x2;
    while(n--)
    {
        ll i = rg();
        x2=i;
        if(x2.get_int()!=i)
        {
            assig.push_back(i);
            break;
        }
        x2++;
        if(x2.get_int()!=i+1)
        {
            inc.push_back(i);
        }
        x2=i;
        x2--;
        if(x2.get_int()!=i-1)
        {
            erdec.push_back(i);
        }
        cout<<"["<<x2<<":"<<i-1<<"] ";
    }

    debug(inc);
    debug(erdec);
    debug(assig);
}

void check_add_sub()
{
    ll n,k;
    cin>>n>>k;
    bint x,K(k);
    for(ll i=-n;i<=n;i++)
    {
        x=i;
        if(x.get_int()!=i)
        {
            assig.push_back(i);
            break;
        }
        auto ans = x+K;
        if(ans.get_int()!=i+k)
        {
            add.push_back({i,k});
        }
        ans = x-K;
        if(ans.get_int()!=i-k)
        {
            sub.push_back({i,k});
        }
    }

}

void check_mul_div()
{
    ll n,m;
    cin>>n>>m;
    bint x;
    for(ll i=-n;i<=n;i++)
    {
        x=i;
        if(x.get_int()!=i)
        {
            assig.push_back(i);
            break;
        }
        for(ll j=-m;j<=m;j++)
        {
            if(j==0) continue;
            bint y(j);
            if(y.get_int()!=j)
            {
                assig.push_back(j);
                break;
            }
            auto ans = x*y;
            if(ans.get_int()!=i*j)
            {
                add.push_back({i,j});
            }
            ans = x/y;
            if(ans.get_int()!=i/j)
            {
                sub.push_back({i,j});
            }
        }
    }
    debug(assig.size());
    debug(sub.size());
    debug(add.size());

}

void test_bint()
{
    bint x,y,one({1ll},1),neg_one({1ll},-1);
    cout<<x<<","<<y<<endl;
    ll n;
    cin>>n;
    bint ans;
    for(ll i=-n;i<=n;i++)
    {
        x=i;
        if(x.get_int()!=i)
        {
            assig.push_back(i);
            break;
        }
        y=n;
        if(y.get_int()!=n)
        {
            assig.push_back(n);
        }
        for(ll j=n;j>=-n;j--)
        {
           ans = x+y;
            if(ans.get_int()!=i+j)
            {
                add.push_back({i,j});
            }
            ans = x-y;
            if(ans.get_int()!=i-j)
            {
                sub.push_back({i,j});
            }
            y--;
            if(y.get_int()!=j-1)
            {
                erdec.push_back(j);
            }
        }
        x++;
        if(x.get_int()!=i+1)
        {
            inc.push_back(i);
        }
    }
    

}

int main()
{
    // test_bint();
    check_assign();
    // check_add_sub();
    // check_mul_div();
    return 0;
}