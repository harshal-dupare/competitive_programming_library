#pragma once

#include <bits/stdc++.h>

using namespace std;

template<typename R>
class markov_chain
{
public:
    int n;
    vector<vector<R>> a;
    markov_chain(){}

    markov_chain(int _n)
    {
        this->n=_n;
        this->a.assign(_n,vector<R>(_n));
    }

    void input()
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>a[i][j];
            }
        }
    }

    void normalize()
    {
        for(int i=0;i<n;i++)
        {
            R su=0;
            for(int j=0;j<n;j++)
            {
                su+=a[i][j];
            }
            for(int j=0;j<n;j++)
            {
                a[i][j]/=su;
            }
        }
    }

    friend ostream& operator<<(ostream& os, markov_chain<R> m)
    {
        for(int i=0;i<m.n;i++)
        {
            for(int j=0;j<m.n;j++)
            {
                os<<m.a[i][j]<<" ";
            }
            os<<"\n";
        }
        return os;
    }

};

