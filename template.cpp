#include <bits/stdc++.h>

// namespaces starts
using namespace std;
// namespaces ends

// MACROS to include exclude starts
#define using_rollup 1
#define using_defines 1
// #define using_pbds 1
// MACROS to include exclude ends

#ifdef using_rollup

#ifdef using_pbds
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#endif

// functional starts
#ifdef using_defines

#define REP(i, n) for (int64 i = 0; i < n; i++)
#define IREP(i, a, b) for (int64 i = a; i < b; i++)
#define RREP(i, n) for (int64 i = n - 1; i >= 0; i--)
#define IRREP(i, a, b) for (int64 i = a - 1; i >= b; i--)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
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
// functional ends

// types and values start
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795

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
// functional ends

#define ok(a) cout << a << "\n";
#define okf(a) cout << a << endl;
#define okp(a, i) cout << fixed << setprecision(i) << a << "\n";

#endif

#define FASTIO 1
#define FILEIO 0
#define TESTCASES 1
// #define LOCAL

#ifdef LOCAL
#include "my_lib/utils/debug_out.h"
#else
#define debug(...)
#endif

typedef long long ll;
typedef unsigned long long ull;

void solve()
{

    return;
}

int main()
{
    if (FASTIO)
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
    }
    if (FILEIO)
    {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int T = 1;
    if (TESTCASES)
        cin >> T;

    while (T--)
        solve();

    return 0;
}

/*
1. Check edge cases?
2. Try few simple examples to test hypothesis and observe property
3. Greedy or DP?
4. Write in more mathematical way
5. Maybe generalization can help?
6. Is their some speical object that satisfies this property always?

1. Is implimentation ok?
2. No Datatype overflow?
3. No index overflow?
4. Are the values initilized properly?
5. Is every input read properly? is output format ok?

• Do you understand all the words used in stating the problem?
• What are you asked to find or show?
• Can you restate the problem in your own words?
• Can you think of a picture or diagram that might help you understand the
problem?

• Guess and check 
• Look for a pattern
• Make an orderly list 
• Draw a picture
• Eliminate possibilities 
• Solve a simpler problem
• Use symmetry 
• Use a model
• Consider special cases 
• Work backwards
• Use direct reasoning 
• Use a formula
• Solve an equation 
• Be ingenious
*/