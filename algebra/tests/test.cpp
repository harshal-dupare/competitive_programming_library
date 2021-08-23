#include <bits/stdc++.h>
#include "../linalg.hpp"
#include "../../utils/debug_out.hpp"
#include "../../randoms/random_gen.hpp"

// namespaces starts
using namespace std;
using namespace linalg;

typedef double R;
typedef long long ll;
const bool isqr = false;
typedef matrix<R,ll,isqr> mat;

mat getmat(ll n, ll m)
{
    auto rg = random_gens::uniform_int<ll>(-100ll,100ll);
    mat ans(n,m);
    for(ll i=0;i<n;i++)for(ll j=0;j<m;j++) ans.a[i][j] = (R) rg();
    return ans;
}

void test_add()
{
    ll n,m,r,k;
    cin>>n>>m>>r>>k;
    while(k--)
    {
        mat a = getmat(n,m);
        mat b = getmat(m,r);
        mat c = a+b;
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<m;j++)
            {
                if(a.a[i][j]+b.a[i][j]!=c.a[i][j])
                {
                    debug(a);
                    debug(b);
                    debug(c);
                }
            }
        }
    }
}

void test_sub()
{
    ll n,m,r,k;
    cin>>n>>m>>r>>k;
    while(k--)
    {
        mat a = getmat(n,m);
        mat b = getmat(m,r);
        mat c = a-b;
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<m;j++)
            {
                if(a.a[i][j]-b.a[i][j]!=c.a[i][j])
                {
                    debug(a);
                    debug(b);
                    debug(c);
                }
            }
        }
    }
}

void test_mult()
{
    ll n,m,r,k;
    cin>>n>>m>>r>>k;
    while(k--)
    {
        mat a = getmat(n,m);
        mat b = getmat(m,r);
        debug(a);
        debug(b);
        debug(a*b);
    }
}

bool iszero(mat& a)
{
    R eps = 0.000001;
    for(ll i=0;i<a.n;i++)
    {
        for(ll j=0;j<a.m;j++)
        {
            if(abs(a.a[i][j])>eps)
            {
                return false;
            }
        }
    }
    return true;
}

bool iseql(const mat& a,const mat& b)
{
    R eps = 0.000001;
    for(ll i=0;i<a.n;i++)
    {
        for(ll j=0;j<a.m;j++)
        {
            if(abs(a.a[i][j]-b.a[i][j])>eps)
            {
                return false;
            }
        }
    }
    return true;
}

void testinv()
{
    ll n,k;
    cin >>k>> n;
    mat I;
    I.diagonal(n,1);
    while(k--)
    {
        mat c = getmat(n,n);
        mat invc = inverse<R,ll,isqr>(c);
        mat diff = invc*c-I;
        // debug(diff);
        if(!iseql(invc*c,I))
        {
            debug(c);
            debug(invc);
            debug(diff);
        }
    }
}


void ttest()
{
    debug(int());
    debug(ll());
}

int main()
{
    //testinv();
    ttest();
    return 0;
}
