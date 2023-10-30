#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dl;
#define pb push_back
#define F first
#define S second
#define inf LLONG_MAX
#define mod 1000000007
#define PI 3.1415926536
#define vll vector <ll>
#define pll pair <ll,ll>
#define dbg(n) cout<<n<<' '
#define cu continue
#define br break
#define N 100005

// program to find the GCD of two node values in a tree in O(log n) time

bool prime[N];
vll v[N];
ll n,a[N],p[18][N],pgcd[18][N],lvl[N];

void sieve()
{
    memset(prime,true,sizeof prime);
    for(ll i=2;i*i<N;i++)
        if(prime[i])
            for(ll j=i*i;j<N;j+=i)
                prime[j]=0;
    prime[0]=0;
    prime[1]=0;
}

pll divisors(ll n)
{
    ll P=0,Q=0;
    for(ll i=1;i*i<=n;i++)
        if(n%i==0)
        {
            if(prime[i])
                P++;
            Q++;
            if(i==(n/i)) cu;
            if(prime[n/i])
                P++;
            Q++;
        }
    Q--;
    return {P,Q};
}

void dfs(ll x,ll par=-1)
{
    if(par!=-1)
    {
        lvl[x]=lvl[par]+1;
        p[0][x]=par;
        pgcd[0][x]=__gcd(a[x],a[par]);
    }
    for(auto y:v[x])
    {
        if(y!=par)
            dfs(y,x);
    }
}

ll walk(ll x,ll len,ll &res)
{
    for(ll i=18;i>=0;i--)
    {
        if((len>>i)&1)
        {
            res=__gcd(res,pgcd[i][x]);
            x=p[i][x];
        }
    }
    return x;
}

ll lca(ll x,ll y)
{
    if(lvl[x]<lvl[y]) swap(x,y);
    ll len=lvl[x]-lvl[y],res=0;
    x=walk(x,len,res);
    if(x==y) return res;
    for(ll i=17;i>=0;i--)
    {
        if(p[i][x]!=p[i][y])
        {
            res=__gcd(res,pgcd[i][x]);
            res=__gcd(res,pgcd[i][y]);
            x=p[i][x];
            y=p[i][y];
        }
    }
    res=__gcd(res,pgcd[0][x]);
    res=__gcd(res,pgcd[0][y]);
    return res;
}

ll mpow(ll x,ll y)
{
    ll res=1;
    x=(x%mod);
    while(y>0)
    {
        if(y&1)
            res=(res*x)%mod;
        y>>=1;
        x=(x*x)%mod;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("/home/r0b0t/Documents/C++/input.txt","r",stdin);
    // freopen("/home/r0b0t/Documents/C++/output.txt","w",stdout);
    #endif

    sieve();
    cin>>n;
    ll m=n-1;
    while(m--)
    {
        ll x,y;
        cin>>x>>y;
        v[x].pb(y);
        v[y].pb(x);
    }
    for(ll i=1;i<=n;i++)
        cin>>a[i];
    for(ll i=0;i<18;i++)
        for(ll j=0;j<=n;j++)
        {
            p[i][j]=-1;
            pgcd[i][j]=0;
        }
    dfs(1);
    for(ll i=1;i<18;i++)
        for(ll j=1;j<=n;j++)
        {
            ll t1=p[i-1][j],t2=pgcd[i-1][j];
            if(t1!=-1)
            {
                p[i][j]=p[i-1][t1];
                pgcd[i][j]=__gcd(t2,pgcd[i-1][t1]);
            }
        }
    ll q;
    cin>>q;
    while(q--)
    {
        ll l,r;
        cin>>l>>r;
        ll g=lca(l,r);
        if(l==r)
        {
            g=a[l];
        }
        if(g==1)
        {
            cout<<-1<<'\n';
            cu;
        }
        pll P=divisors(g);
        ll ans=(P.F * mpow(P.S,mod-2))%mod;
        cout<<ans<<'\n';
    }
}