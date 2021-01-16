#include <bits/stdc++.h>
#include "polynomial.h"

using namespace std;

typedef long long ll;
typedef polynomial<ll, 711111111ll> poly;

void test_basics()
{
    ll n, m;
    cin >> n >> m;
    poly p(n), q(m);
    p.input();
    q.input();
    cout << p;
    cout << q;
    poly r = p + q;
    cout << r;
    r += p;
    poly t = make_pair(5, 6)+r;
    cout << r;
    cout<<t;
    r=5*r;
    cout << r;
    r+=make_pair(1,3);
    cout<<r;
    poly tp = p*q;
    cout<<tp;

    poly tex=tp.exp(10);
    cout<<tex;
}

int main()
{
    test_basics();
    return 0;
}