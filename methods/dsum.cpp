#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9L+7ll;

// given distinct numbers x and y find how many numbers with exact number of n digits  have their digit digit sum only containing digits x and y

vector<vector<ll>> dp;

void fillds(vector<ll>&ds, ll x, ll y, ll ld, ll lv, ll md)
{
    if(lv>md)
    {
        return;
    }

    ll nx = ld*10+x;
    ll ny = ld*10+y;
    ds.push_back(nx);
    ds.push_back(ny);
    fillds(ds,x,y,nx,lv+1,md);
    fillds(ds,x,y,ny,lv+1,md);
}

ll gdp(ll n, ll d, bool base=false)
{
    if(n<0||d<0) return 0;
    if(dp[n][d]!=-1) return dp[n][d];
    ll ans = 0;
    for(int dg = (base?1:0);dg<=9;dg++)
    {
        if(n-dg>=0)
        {
            ans = (ans+gdp(n-dg,d-1))%mod;
        }
    }
    dp[n][d] = ans;
    return ans;
}

int main()
{
    ll n,x,y;
    cin>>x>>y>>n;
    vector<ll> ds;
    ll k =0;
    ll tk = 9*n;
    while(tk>0) tk/=10,k++;
    fillds(ds,x,y,0,1,k);
    dp.assign(9*n+10,vector<ll>(n+10,-1));
    for(ll i=0;i<9*n+10;i++)dp[i][0] = 0;
    for(ll i=0;i<n+10;i++)dp[0][i] = 1;

    ll ans = 0;
    for(auto dj : ds)
    {
        if(dj>9ll*n) continue;
        ans = (ans + gdp(dj,n,true));
    }
    cout<<ans<<endl;

    return 0;
}