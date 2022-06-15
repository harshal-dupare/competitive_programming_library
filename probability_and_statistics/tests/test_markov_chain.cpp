#include<bits/stdc++.h>

#include "../markov_chain.hpp"
#include "../../utils/debug_out.hpp"

typedef double R;
using namespace std;

void test_classes()
{
    int n;
    cin>>n;
    markov_chain<R,int> mc(n);
    mc.input();
    vector<vector<int>> cc;
    mc.communicating_classes(cc);
    debug(cc);
    return;
}

void test_f_star_u_star_i()
{
    int n,i;
    cin>>n;
    markov_chain<R,int> mc(n);
    mc.input();
    cin>>i;
    auto fusi = mc.f_star_u_star_i(i);
    debug(fusi);
    return;
}

void test_steady_state_distribution()
{
    int n,i;
    cin>>n;
    markov_chain<R,int> mc(n);
    mc.input();
    auto s = mc.steady_state_distribution(0);
    debug(s);
    return;
}

void test_first_passage_time()
{
    int n,i;
    cin>>n;
    markov_chain<R,int> mc(n);
    mc.input();
    cin>>i;
    auto u = mc.first_passage_time(i);
    debug(u);
}

int main()
{
    test_steady_state_distribution();
    return 0;
}