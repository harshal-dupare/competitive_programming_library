#include <bits/stdc++.h>
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/randoms/random_sampling.hpp"
// FIXME: add statistical tests for randomness

using namespace std;
typedef long long int ll;
typedef double R;

int main()
{
    using namespace random_sampling;
    int n = 100;
    int k = 10;
    vector<int> samples;
    reservoir_L_sampler_static<int,double>(n,k,std::chrono::steady_clock::now().time_since_epoch().count(),samples);
    for(auto x: samples)
    {
        cout<<x<<", ";
    }
    return 0;
}
