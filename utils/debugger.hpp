#pragma once

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
