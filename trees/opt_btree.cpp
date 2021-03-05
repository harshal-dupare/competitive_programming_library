#include <bits/stdc++.h>
#include "../utils/debug_out.h"

using namespace std;

typedef long long ll;

int main()
{
    ll n;
    vector<ll> cost;
    cin>>n;
    cost.resize(n);
    vector<ll> ccost(n+1);
    ccost[0]=0;
    for(int i=0;i<n;i++)
    {
        cin>>cost[i];
        if(i>0) ccost[i]=ccost[i-1]+cost[i];
        else ccost[i]=cost[i];
    }
    ll inf = 1e10;
    vector<vector<ll>> dp(n,vector<ll>(n,inf));

    for(ll i=0;i<n;i++)dp[i][i]=cost[i];

    auto summ = [&](int i,int j)
    {
        ll ans=0;
        for(int t=i;t<j+1;t++)
        {
            ans+=cost[t];
        }
        return ans;
    };

    ll ct=0;
    for(ll len=2;len<n+1;len++)
    {
        for(ll i=0;i<n-len+1;i++)
        {
            ll j=i+len-1;
            for(ll k=i;k<=j;k++)
            {
                ll new_cost=summ(i,j);
                debug(new_cost);

                if(k>0) new_cost+=dp[i][k-1];
                if(k<n-1) new_cost+=dp[k+1][j];
                dp[i][j] = min(dp[i][j],new_cost);
                mdebug(len,i,j,k,new_cost);
                debug(dp);
                ct++;
            }
        }
    }

    debug(dp);

    cout<<dp[0][n-1]<<endl;
    debug(ct);


    return 0;
}