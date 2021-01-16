#include <bits/stdc++.h>

// namespaces starts
using namespace std;
// namespaces ends

// void debug_out()
// {
//     cerr << "\n";
// }

// template <typename T>
// void debug_out(T x)
// {
//     cerr << x << ", ";
// }

// template <typename H, typename T>
// void debug_out(pair<H, T> x)
// {
//     cerr << "{" << x.first << ":" << x.second << "}, ";
// }

// template <std::size_t I = 0, typename... Tp>
// inline typename std::enable_if<I == sizeof...(Tp), void>::type
// debug_out(std::tuple<Tp...> &t)
// {
//     cerr << ")\n";
// }

// template <std::size_t I = 0, typename... Tp>
// inline typename std::enable_if < I<sizeof...(Tp), void>::type debug_out(std::tuple<Tp...> &t)
// {
//     if (I == 0)
//     {
//         cerr << "(";
//     }
//     debug_out(std::get<I>(t));
//     debug_out<I + 1, Tp...>(t);
// }

// template <typename Head, typename... Tail>
// void Debug(Head H, Tail... T)
// {
//     cerr << " " << to_string(H);
//     Debug(T...);
// }

// template <typename T>
// void Debug(T x)
// {
//     cerr << " = " << x << "\n";
// }

// template <typename F, typename S>
// void Debug(pair<F, S> x)
// {
//     cerr << " = {" << x.first << ":" << x.second << "}\n";
// }

// template <std::size_t I = 0, typename... Tp>
// inline typename std::enable_if<I == sizeof...(Tp), void>::type
// Debug(std::tuple<Tp...> &t)
// {
//     cerr << ")\n";
// }

// template <std::size_t I = 0, typename... Tp>
// inline typename std::enable_if < I<sizeof...(Tp), void>::type Debug(std::tuple<Tp...> &t)
// {
//     if (I == 0)
//     {
//         cerr << "(";
//     }
//     debug_out(std::get<I>(t));
//     Debug<I + 1, Tp...>(t);
// }

// template <typename T>
// void Debug(set<T> s)
// {
//     cerr << ":" << s.size() << "\n{";
//     for (auto x : s)
//         debug_out(x);
//     cerr << "}\n";
// }

// template <typename T>
// void Debug(vector<T> s)
// {
//     cerr << ":" << s.size() << "\n[";
//     for (auto x : s)
//         debug_out(x);
//     cerr << "]\n";
// }

// template <typename K, typename D>
// void Debug(map<K, D> s)
// {
//     cerr << ":" << s.size() << "\n{";
//     for (auto x : s)
//         debug_out(x);
//     cerr << "}\n";
// }

// template <typename T>
// void Debug(vector<vector<T>> vv)
// {
//     cerr << ":" << vv.size() << "\n";
//     for (auto x : vv)
//     {
//         cerr << "[ ";
//         for (auto y : x)
//             debug_out(y);
//         cerr << "]\n";
//     }
// }

// #define debug(...) cerr << #__VA_ARGS__, Debug(__VA_ARGS__)


#include "debug_out.h"

int main()
{
    int i = 0;
    pair<int, int> x({9, 0});
    tuple<int, string, float> t(0, "gyg", 0.987);
    pair<int,pair<pair<int,string>,float>> ppp({3,{{9,"hie"},0.98}});
    vector<pair<int, int>> vk(10);
    vector<tuple<pair<int, int>, int>> vt(10);
    vector<vector<pair<int, int>>> vvk(10, vector<pair<int, int>>(5));
    set<pair<string,int>> sp;
    sp.insert({"fgd",87});
    sp.insert({"fd",7});
    sp.insert({"gd",8});

    map<int,int> mp;
    mp[9]=0;
    mp[5]=0;
    mp[7]=0;
    mp[2]=0;

    debug(i);
    debug(x);
    debug(t);
    debug(i,x,t);
    debug(ppp);
    debug(vk);
    debug(vt);
    debug(vvk);
    debug(mp);
    debug(sp);
    return 0;
}