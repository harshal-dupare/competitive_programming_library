#include <bits/stdc++.h>
#include "../../lib/polynomials/polynomial.hpp"
// #include "../../lib/polynomials/ffts.hpp"

using namespace std;

typedef long long ll;
ll mod = 998244353ll;
// ll mod = 97ll;

typedef polynomial<ll, 998244353ll> poly;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

poly rand_poly(ll N)
{
    vector<ll> a;
    ll n = rng() % N;
    if(n<0) n+=N;

    for (ll i = 0; i <= n; i++)
    {
        ll tp =rng() % (mod);
        if(tp<0) tp+=mod;
        else if(tp>=mod) tp-=mod;
        a.push_back(tp);
    }

    return poly(a);
}

void test_add_sub()
{
    ll n, N;
    cin >> n >> N;

    while (n--)
    {
        auto a = rand_poly(N);
        auto b = rand_poly(N);
        auto apb = a + b;
        auto amb = a - b;
        auto bma = b - a;
        ll k = 100ll;
        while(k--)
        {
            ll r = (rng()%mod);
            if(r<0) r+=mod;

            ll va=a.eval(r);
            ll vb=b.eval(r);
            ll vapb=apb.eval(r);
            ll vamb=amb.eval(r);
            ll vbma=bma.eval(r);

            // cout<<"r="<<r<<endl;
            // cout<<va<<":"<<a;
            // cout<<vb<<":"<<b;
            // cout<<vapb<<":"<<apb;
            // cout<<vamb<<":"<<amb;
            // cout<<vbma<<":"<<bma;
            if((va+vb)%mod!=vapb)
            {
                cout<<"a+b\n";
            }
            if((va+mod-vb)%mod!=vamb)
            {
                cout<<"a-b\n";
            }
            if((vb+mod-va)%mod!=vbma)
            {
                cout<<"b-a\n";
            }
            // cout << endl;
        }
        // cout << endl;
    }
}

void test_mult()
{
    ll ct=0;
    ll n, N;
    cin >> n >> N;

    while (n--)
    {
        auto a = rand_poly(N);
        auto b = rand_poly(N);

        auto apb = a*b;
        ll k = 100ll;
        while(k--)
        {
            ll r = (rng()%mod);
            if(r<0) r+=mod;

            ll va=a.eval(r);
            ll vb=b.eval(r);
            ll vapb=apb.eval(r);

            if((va*vb)%mod!=vapb)
            {
                cout<<"a*b\n";
                ct++;
            }
            else
            {
                // cout<<"r="<<r<<endl;
                // cout<<va<<":"<<a;
                // cout<<vb<<":"<<b;
                // cout<<vapb<<":"<<apb;
            }
        }
        cout << endl;

    }

    cout<<"Total Erros: "<<ct<<endl;
}

void test_div_mod()
{
    ll ct=0;
    ll n, N;
    cin >> n >> N;

    while (n--)
    {
        auto a = rand_poly(N);
        auto b = rand_poly(N);
        auto aqb = a/b;
        auto arb = a%b;
        ll k = 1ll;
        while(k--)
        {
            ll r = (rng()%mod);
            if(r<0) r+=mod;

            ll va=a.eval(r);
            ll vb=b.eval(r);
            ll vaqb=aqb.eval(r);
            ll varb=arb.eval(r);

            auto ra = arb+b*aqb;

            // cout<<"r="<<r<<endl;
            // cout<<"a="<<va<<":"<<a;
            // cout<<"b="<<vb<<":"<<b;
            // cout<<"a/b="<<vaqb<<":"<<aqb;
            // cout<<"a%b="<<varb<<":"<<arb;
            ll ans = (vb*vaqb+varb)%mod;
            if(ans<0)
                ans+=mod;
            // cout<<"qb+r="<<ans<<":"<<ra;
            
            if(ans!=va)
            {
                cout<<"Error\n";
                cout<<"r="<<r<<endl;
                cout<<"a="<<va<<":"<<a;
                cout<<"b="<<vb<<":"<<b;
                cout<<"a/b="<<vaqb<<":"<<aqb;
                cout<<"a%b="<<varb<<":"<<arb;
                ct++;
            }
        }
        // cout << endl;

    }

    cout<<"Total Erros: "<<ct<<endl;
}

void test_multi_point_eval()
{
    ll ct=0;
    ll tc=0;
    ll n, N,K;
    cin >> n >> N >> K;

    while (n--)
    {
        auto a = rand_poly(N);
        // cout<<a;
        ll k = K;
        vector<ll> x;
        while(k--)
        {
            ll r = (rng()%mod);
            if(r<0) r+=mod;
            x.push_back(r);
        }

        auto ax = multipoint_eval(a,x);
        for(ll i=0;i<x.size();i++)
        {
            ll val = a.eval(x[i]);
            if(ax[i]!=val)
            {
                // cout<<a;
                // cout<<x[i]<<": ( "<<ax[i]<<", "<<val<<" )"<<endl;
                ct++;
            }
            tc++;
        }

    }

    cout<<"Total Erros: "<<ct<<"/"<<tc<<endl;
}

void test()
{
    poly a(vector<ll>{6,7,6,3,5});
    vector<ll> x = {32,55};
    auto ax = multipoint_eval(a,x);
    for(ll i=0;i<x.size();i++)
    {
        ll val = a.eval(x[i]);
        if(ax[i]!=val)
        {
            // cout<<a;
            cout<<x[i]<<": ( "<<ax[i]<<", "<<val<<" )"<<endl;
        }
    }
    // cout<<p;
    // p+=q;
    // cout<<p;
    // p+=q;
    // cout<<p;
    // p+=q;
    // cout<<p;
}

void test2()
{
    poly a("+7*x^24+6*x^23+7*x^22+1*x^21+1*x^20+7*x^19+4*x^18+5*x^17+6*x^16+1*x^15+8*x^14+6*x^12+8*x^11+8*x^10+4*x^9+8*x^8+3*x^7+7*x^6+4*x^5+6*x^4+2*x^3+7*x^2+1*x^1+6*x^0");
    vector<ll> x = {79,16,68,75};
    auto ax = multipoint_eval(a,x);
    for(ll i=0;i<x.size();i++)
    {
        ll val = a.eval(x[i]);
        if(ax[i]!=val)
        {
            // cout<<a;
            cout<<x[i]<<": ( "<<ax[i]<<", "<<val<<" )"<<endl;
        }
    }
}

int main()
{
    // test_add_sub();
    // test_mult();
    // test_div_mod();
    // test2();
    test_multi_point_eval();
    return 0;
}

// 1,2,3,4
// 2,-3,1*15,4
// 0+30,8-45,-12+15,4
// 30,-37,3,4
// -29,39