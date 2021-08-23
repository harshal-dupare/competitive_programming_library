#include <bits/stdc++.h>
#include "../../utils/timer.h"
#include "../../utils/debug_out.h"
#include "../matching.hpp"

using namespace std;

typedef long long ll;

void test_rabin_karp()
{
    string s, p;
    string_matching<ll> sm;
    cin >> s;
    cin >> p;

    sm.set(s.size());
    vector<ll> mtc = sm.rabin_karp(s, p);
    oks(mtc);
}

void test_kmp()
{
    string s, p;
    string_matching<ll> sm;
    cin >> s;
    cin >> p;
    vector<ll> pp;
    sm.prefix_function(s, pp);
    vector<ll> mtc = sm.kmp_matching(s, p);
    if (mtc.size() > 0)
    {
        cout << (mtc.size()) << endl;
        for (auto x : mtc)
        {
            cout << x + 1 << " ";
        }
        cout << "\n\n";
    }
    else
    {
        cout << ("Not Found\n\n");
    }
}

void test_zf()
{
    string s, p;
    string_matching<ll> sm;
    cin >> s;
    // cin >> p;
    vector<ll> zf(s.size(), 0);
    sm.z_function(s, zf);
    oks(zf);
}

void test_aut()
{
    string s;
    string_matching<ll> sm;
    cin >> s;
    vector<vector<ll>> aut;
    sm.automaton(s, aut);
    vector<ll> pp;
    sm.prefix_function(s, pp);
    oks(pp);
    okvv(aut);
}

int main()
{
    test_zf();
    return 0;
}