#include<bits/stdc++.h>

#include "markov_chain.h"
#include "../utils/debug_out.h"

typedef double R;

using namespace std;
void test_opt_matrix()
{
    markov_chain<R> m;
    int n;
    cin>>n;
    vector<int> d(n+1);
    vector<pair<int,int>> md(n);
    for(int i=0;i<n+1;i++)
    {
        cin>>d[i];
    }
    for(int i=0;i<n;i++)
    {
        md[i].first=d[i];
        md[i].second=d[i+1];
    }
    vector<vector<int>> dp(n,vector<int>(n,1e8));
    for(int i=0;i<n;i++)
    {
        dp[i][i]=0;
    }

    debug(d);
    debug(md);
    
    for(int k=1;k<n+1;k++)
    {
        for(int i=0;i<n-k;i++)
        {
            for(int j=i;j<i+k;j++)
            {
                dp[i][i+k]=min(dp[i][i+k],dp[i][j]+dp[j+1][i+k]+md[i].first*md[j].second*md[i+k].second);
            }
        }
        // debug(dp);
    }

    // debug(dp);
    debug(dp[0][n-1]);

}

int main()
{
    test_opt_matrix();
    return 0;
}