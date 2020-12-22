#include <bits/stdc++.h>

using namespace std;

template <typename I>
class rational
{
public:
    I p = 0, q = 1;
    rational(I pp, I qq)
    {
        this->p = pp;
        this->q = qq;
    }

    void reduce()
    {
        I tp = abs(this->p);
        I tq = abs(this->q);
        I pqgcd = __gcd(tp, tq);
        this->p /= pqgcd;
        this->q /= pqgcd;
    }

    rational operator+(const rational &b)
    {
        rational ans(this->p * b.q + this->q * b.p, this->q * b.q);
        ans.reduce();
        return ans;
    }

    rational operator-(const rational &b)
    {
        rational ans(this->p * b.q - this->q * b.p, this->q * b.q);
        ans.reduce();
        return ans;
    }

    void operator+=(const rational &b)
    {
        I num = this->p * b.q + this->q * b.p;
        I din = this->q * b.q;
        I ndgcd = __gcd(abs(num), abs(din));
        num /= ndgcd;
        din /= ndgcd;
        this->p = num;
        this->q = din;
    }

    void operator-=(const rational &b)
    {
        I num = this->p * b.q - this->q * b.p;
        I din = this->q * b.q;
        I ndgcd = __gcd(abs(num), abs(din));
        num /= ndgcd;
        din /= ndgcd;
        this->p = num;
        this->q = din;
    }


    rational operator*(const rational &b)
    {
        rational ans(this->p * b.p, this->q * b.q);
        ans.reduce();
        return ans;
    }

    void operator*=(const rational &b)
    {
        I num = this->p * b.p;
        I din = this->q * b.q;
        I ndgcd = __gcd(abs(num), abs(din));
        num /= ndgcd;
        din /= ndgcd;
        this->p = num;
        this->q = din;
    }

    rational operator/(const rational &b)
    {
        rational ans(this->p * b.q, this->q * b.p);
        ans.reduce();
        return ans;
    }

    void operator/=(const rational &b)
    {
        I num = this->p * b.q;
        I din = this->q * b.p;
        I ndgcd = __gcd(abs(num), abs(din));
        num /= ndgcd;
        din /= ndgcd;
        this->p = num;
        this->q = din;
    }

    friend ostream &operator<<(ostream &os, const rational<I> &r)
    {
        os << r.p << '/' << r.q;
        return os;
    }
};

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