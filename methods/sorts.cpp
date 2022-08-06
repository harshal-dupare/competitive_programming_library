#include <bits/stdc++.h>
#include "../utils/debug_out.hpp"

using namespace std;
using ll = long long;
using vll = vector<ll>;
ll invct;

void mymerge(vll& a, ll i, ll mid, ll j)
{
    ll n1 = mid - i + 1;
    ll n2 = j - mid;
    vll ra(n1 + n2);
    ll id = 0;
    ll t = mid + 1;

    while (i < mid + 1 && t < j + 1)
    {
        if (a[i] <= a[t])
        {
            ra[id] = a[i];
            i++;
        }
        else
        {
            ra[id] = a[t];
            invct+=mid+1-i;
            t++;
        }
        id++;
    }
    while (i < mid + 1)
    {
        ra[id] = a[i];
        i++;
        id++;
    }
    while (t < j + 1)
    {
        ra[id] = a[t];
        t++;
        id++;
    }
    i -= n1;
    t = i;
    for (; i < j + 1; i++)
    {
        a[i] = ra[i - t];
    }
}

void inplace_mymerge(vll& a, ll i, ll mid, ll j)
{
    ll n = j-i+1;
    ll k = 1;
    while(k<n) k<<=1;
    k>>=1;
    while(k>0)
    {
        for(ll t=i;t+k<j+1;t++)
        {
            if(a[t] > a[t+k])
            {
                swap(a[t],a[t+k]);
                invct+=1;
            }
        }
        k>>=1;
    }
}

void mergesort(vll &a, ll i, ll j, bool inplace=false)
{
    if (i >= j)
        return;

    ll mid = (i + j) / 2;
    mergesort(a, i, mid, inplace);
    mergesort(a, mid + 1, j, inplace);
    if(!inplace)
        mymerge(a, i, mid, j);
    else
        inplace_mymerge(a,i,mid,j);
    return;
}

void quicksort(vll& a, ll i, ll j, bool stable=false)
{
    if(i>=j) return;
    ll ti=i,tj=j;
    while (tj>ti)
    {
        if(a[ti] <= a[ti+1])
        {
            swap(a[ti+1],a[tj]);
            tj--;
        }
        else
        {
            swap(a[ti+1],a[ti]);
            ti++;
            invct++;
        }
    }

    if(stable)
    {
        reverse(a.begin()+ti+1,a.begin()+j+1);
    }

    quicksort(a,i,ti-1,stable);
    quicksort(a,ti+1,j,stable);
    
}

string solve(ll n)
{
    vll a(n);
    invct=0;
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vll ta;
    ll tic;

    ta = a;
    mergesort(ta, 0, n - 1,true);
    tic = invct;
    invct=0;
    if (!is_sorted(ta.begin(), ta.end()))
    {
        debug(ta);
        return string("inplace mergesort failed");
    }
    debug(tic);

    ta = a;
    mergesort(ta, 0, n - 1);
    tic = invct;
    invct=0;
    if (!is_sorted(ta.begin(), ta.end()))
    {
        debug(ta);
        return string("mergesort failed");
    }
    debug(tic);

    ta = a;
    quicksort(ta,0,n-1);
    if (!is_sorted(ta.begin(), ta.end()))
    {
        return string("quicksort failed");
    }

    ta = a;
    quicksort(ta,0,n-1,true);
    tic = invct;
    invct=0;
    if (!is_sorted(ta.begin(), ta.end()))
    {
        return string("stable quicksort failed");
    }
    debug(tic);
    return string("all passed");
}

int main()
{
    while (true)
    {
        ll n;
        cin >> n;
        cout << solve(n) << endl;
    }
    return 0;
}