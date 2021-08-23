#include<bits/stdc++.h>
#include "../utils/debug_out.hpp"

using namespace std;

typedef long long ll;

const ll N=1<<4; // N > number_of_elemetns_in_array
const ll NULL_VAL = 0;
vector<ll> tree(2*N, NULL_VAL); // 1 indexed tree, array elements start from 2^k ... for 2^k > n 
vector<ll> minrange(2*N), maxrange(2*N);

void build(const vector<ll> &a)
{
    for(ll i=0;i<a.size();i++)
    {
        tree[i+N]=a[i];
        minrange[i+N]=i+N;
        maxrange[i+N]=i+N;
    }
    for(ll i=a.size()+N;i<2*N;i++)
    {
        minrange[i]=i;
        maxrange[i]=i;   
    }
    for(ll i=N-1;i>0;i--)
    {
        tree[i] = tree[2*i]+tree[2*i+1];
        minrange[i] = minrange[2*i];
        maxrange[i] = maxrange[2*i+1];
    }
}

// 0 indexed
void update(ll i, ll val)
{
    i+=N;
    tree[i]=val;
    i>>=1;
    while(i>0)
    {
        tree[i] = tree[2*i]+tree[2*i+1];
        i>>=1;
    }
}

// 0 indexed
// i is the index in tree
void rupdate(ll i, ll val)
{
    if(i<1) return;
    if(minrange[i]==maxrange[i])
    {
        tree[i]=val;
    }
    else
    {
        tree[i] = tree[2*i]+tree[2*i+1];
    }
    rupdate(i>>1);
    return;
}

// 0 indexed query, l and r from updated array
// i is the sub-segement tree on which we are querying
// for full tree i = 1
ll query(ll i, ll l, ll r)
{
    if(r < minrange[i] || maxrange[i] < l)
    {
        return NULL_VAL;
    }
    if(l <= minrange[i] && maxrange[i] <= r)
    {
        return tree[i];
    }

    return query(2*i,l,r)+query(2*i+1,l,r);
}

int main()
{
    vector<ll> a(10);
    for(ll i=0;i<10;i++)
    {
        a[i]=i+1;
    }
    build(a);

    while (true)
    {
        ll ty;
        cin>>ty;
        if(ty==0)
        {
            ll i,x;
            cin>>i>>x;
            update(i,x);
        }
        else if (ty==1)
        {
            ll l,r;
            cin>>l>>r;
            l+=N;
            r+=N;
            cout<<query(1,l,r)<<endl;
        }
    }
    
    return 0;
}