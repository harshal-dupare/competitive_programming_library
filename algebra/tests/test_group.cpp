#include <bits/stdc++.h>
#include "../../utils/debug_out.hpp"
#include "../group.hpp"

using namespace std;
typedef long long int ll;
typedef double R;

void test_subg_S3()
{
    group<int> g(6);
    vector<vector<int>> subgs;
    map<int, int> mp, imp;
    mp[123] = 0, imp[0] = 123;
    mp[213] = 1, imp[1] = 213;
    mp[132] = 2, imp[2] = 132;
    mp[321] = 3, imp[3] = 321;
    mp[231] = 4, imp[4] = 231;
    mp[312] = 5, imp[5] = 312;
    g.input(mp);
    g.find_subgroups(subgs, imp);
    debug(subgs);
}

void test_subg_D4()
{
    group<int> g(8);
    vector<vector<int>> subgs;
    map<int, int> mp, imp;
    mp[0] = 0, imp[0] = 0;
    mp[180] = 1, imp[1] = 180;
    mp[90] = 2, imp[2] = 90;
    mp[270] = 3, imp[3] = 270;
    mp[1] = 4, imp[4] = 1;
    mp[2] = 5, imp[5] = 2;
    mp[3] = 6, imp[6] = 3;
    mp[4] = 7, imp[7] = 4;
    g.input(mp);
    g.find_subgroups(subgs, imp);
    debug(subgs);
}

int main()
{
    test_subg_S3();
    // test_subg_D4();
    return 0;
}

// s3
// 123	213	132	321	231	312
// 213	123	231	312	132	321
// 132	312	123	231	321	213
// 321	231	312	123	213	132
// 231	321	213	132	312	123
// 312	132	321	213	123	231

// d4

// 0 180 90 270 1 2 3 4
// 180 0 270 90 2 1 4 3
// 90 270 180 0 4 3 1 2
// 270 90 2 180 3 4 2 1
// 1 2 3 4 0 180 90 270
// 2 1 4 3 180 0 270 90
// 3 4 2 1 270 90 0 180
// 4 3 1 2 90 270 180 0