#include <bits/stdc++.h>
using namespace std;

#define using_rollup  1
#define using_defines 1
// #define using_pbds 1
// #define LOCAL         1
#define FAST_IO       1
#define FILE_INPUT    0
#define FILE_OUTPUT   0
#define TESTCASES     1

#ifdef using_rollup
#ifdef using_pbds
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#endif

#ifdef LOCAL
#include "my_lib/utils/debug_out.hpp"
#else
#define debug(...)
#define mdebug(...)
#endif

#define ok(a) cout << a << endl;
#define okp(a, i) cout << fixed << setprecision(i) << a << endl;

#ifdef using_defines
#define REP(i, n) for (int64 i = 0; i < n; i++)
#define rep(i, start, end, incr) for (__typeof(end) i = (start); i <= (end); i += (incr))
#define inrange(i, a, b) ((i >= min(a, b)) && (i <= max(a, b)))
#define SCD(t) scanf("%d", &t)
#define SCLD(t) scanf("%ld", &t)
#define SCLLD(t) scanf("%lld", &t)
#define SCC(t) scanf("%c", &t)
#define SCS(t) scanf("%s", t)
#define SCF(t) scanf("%f", &t)
#define SCLF(t) scanf("%lf", &t)
#define MEM(a, b) memset(a, (b), sizeof(a))
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.rbegin(), cont.rend()

constexpr double PI = 3.1415926535897932384626433832795;
constexpr long long MOD = 1000000007;

typedef short int int16;               // +- 32,767
typedef unsigned short int uint16;     // 0 to 65,535
typedef long int int32;                // +- 2,147,483,647
typedef unsigned long int uint32;      // 0 to 4,294,967,295
typedef long long int int64;           //  +- 9,223,372,036,854,775,807
typedef unsigned long long int uint64; // 0 to 18,446,744,073,709,551,615
typedef float float32;                 // 6-9 significant digits, typically 7
typedef double float64;                // 15-18 significant digits, typically 16
typedef long double float96;           // 18-21 significant digits for 16 bits OR 33-36 significant digits for 18 bits
typedef pair<int64, int64> pll;
typedef vector<int64> vl;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef vector<pll> vpll;
typedef vector<vl> vvl;

// random number generators
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#endif
#endif

typedef long long ll;
typedef unsigned long long ull;

ll TestCaseCount = 0;

void solve()
{

    return;
}

int main()
{
    if (FAST_IO)
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
    }
    if (FILE_INPUT)
    {
        freopen("input.txt", "r", stdin);
    }
    if (FILE_OUTPUT)
    {
        freopen("output.txt", "w", stdout);
    }

    int T = 1;
    if (TESTCASES)
        cin >> T;

    while (T--)
    {
        TestCaseCount++;
        solve();
    }

    return 0;
}
