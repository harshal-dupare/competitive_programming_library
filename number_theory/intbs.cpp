#include <bits/stdc++.h>
#include "../utils/debug_out.hpp"
// #include "int_base.hpp"
#include "bigint.hpp"


using namespace std;

// typedef int_base<int, 13> intb;
typedef bigint<long long, 2> bint;
typedef long long ll;

// void test_intb()
// {
//     intb x(120), y(13);
//     debug(x);
//     debug(y);
//     debug(x + y);
//     debug(x >> 1);
//     debug(y >> 1);
//     debug(x << 1);
//     debug(y << 1);
//     debug(y - x);
//     debug(y * x);
// }

void check_assign()
{
    ll n;
    cin>>n;
    bint x;
    vector<ll> inc,dec,assig;
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
            dec.push_back(i);
        }
    }

}

void check_add_sub()
{
    ll n,k;
    cin>>n>>k;
    bint x,K(k);
    vector<pair<ll,ll>> add,sub;
    vector<ll> assig;
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
    ll n,k;
    cin>>n>>k;
    bint x,K(k);
    vector<pair<ll,ll>> add,sub;
    vector<ll> assig;
    for(ll i=-n;i<=n;i++)
    {
        x=i;
        if(x.get_int()!=i)
        {
            assig.push_back(i);
            break;
        }
        auto ans = x*K;
        if(ans.get_int()!=i*k)
        {
            add.push_back({i,k});
        }
        ans = x/K;
        if(ans.get_int()!=i/k)
        {
            sub.push_back({i,k});
        }
    }

}

void test_bint()
{
    vector<ll> inc,dec,assig;
    vector<pair<ll,ll>> add,sub;
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
                dec.push_back(j);
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
    // check_assign();
    // check_add_sub();
    check_mul_div();
    return 0;
}