#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main()
{
    ll n;
    cin >> n;
    rational<ll> a(1, 9), b(9, 1), c(-3, 7);
    cout<<a<<b<<c<<endl;
    cout<<a+b<<endl;
    cout<<a-b<<endl;
    cout<<a*b<<endl;
    cout<<a/b<<endl;

    cout<<c+b<<endl;
    cout<<c-b<<endl;
    cout<<c*b<<endl;
    cout<<c/b<<endl;


    return 0;
}