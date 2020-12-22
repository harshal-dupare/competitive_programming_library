#include <bits/stdc++.h>

// namespaces starts
using namespace std;
// namespaces ends

// MACROS to include exclude starts
#define using_rollup 1
#define using_defines 1
#define using_debug 1
// #define using_pbds 1
// MACROS to include exclude ends

#ifdef using_rollup

#ifdef using_pbds
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int64, null_type, less<int64>, rb_tree_tag, tree_order_statistics_node_update> pbds_tree;

/*
template<
	  typename Key, // Key type
	  typename Mapped, // Mapped-policy
	  typename Cmp_Fn = std::less<Key>, // Key comparison functor
	  typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
	  template<
	  typename Const_Node_Iterator,
	  typename Node_Iterator,
	  typename Cmp_Fn_,
	  typename Allocator_>
	  class Node_Update = null_node_update, // A policy for updating node invariants
	  typename Allocator = std::allocator<char> > // An allocator type
class tree;
*/
#endif

// functional starts
#ifdef using_defines

#define REP(i, n) for (int64 i = 0; i < n; i++)
#define RREP(i, n) for (int64 i = n - 1; i >= 0; i--)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define inrange(i, a, b) ((i >= min(a, b)) && (i <= max(a, b)))
#define IOS                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define LOOPTESTS(TesTcases) \
    int64 tttt;              \
    if (!TesTcases)          \
        tttt = 1;            \
    else                     \
        cin >> tttt;         \
    while (tttt--)

#define FILEIO                        \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define SCD(t) scanf("%d", &t)
#define SCLD(t) scanf("%ld", &t)
#define SCLLD(t) scanf("%lld", &t)
#define SCC(t) scanf("%c", &t)
#define SCS(t) scanf("%s", t)
#define SCF(t) scanf("%f", &t)
#define SCLF(t) scanf("%lf", &t)
#define MEM(a, b) memset(a, (b), sizeof(a))
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
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

template <typename T>
T INF()
{
    return numeric_limits<T>::infinity();
}

#endif
// functional ends

// Debug starts
#ifdef using_debug

#define ok(vari) cerr << #vari << " = " << (vari) << "\n";
#define oka(a, L, R)              \
    cerr << #a << " : \n[ ";      \
    for (int64 i = L; i < R; i++) \
        cerr << a[i] << " ";      \
    cerr << "]\n";
#define oks(s)               \
    cerr << #s << " : \n{ "; \
    for (auto x : s)         \
        cerr << x << " ";    \
    cerr << "}\n";
#define okp(ps)                                         \
    cerr << #ps << " : \n";                             \
    for (auto x : ps)                                   \
        cerr << (x.first) << ":" << (x.second) << ", "; \
    cerr << "\n";
#define okvv(vv)              \
    cerr << #vv << " : \n";   \
    for (auto x : vv)         \
    {                         \
        cerr << "[ ";         \
        for (auto y : x)      \
            cerr << y << " "; \
        cerr << "]\n";        \
    }

#define reply(a) cout << a << "\n";
#define replyf(a, i) cout << fixed << setprecision(i) << a << "\n";

#endif
// Debug ends
#endif

typedef long long ll;

int main()
{
    IOS;
    LOOPTESTS(false)
    {
        ll n;
        cin >> n;
    }
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
*/