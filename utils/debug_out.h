#pragma once

#include <bits/stdc++.h>

#define ONE_EXTRA_LINE 1

using namespace std;

template <typename H, typename T>
void debug_out(pair<H, T> x);

template <typename F, typename S>
void Debug(pair<F, S> x);

//// base debug starts

void debug_out()
{
    cerr << "\n";
}

template <typename T>
void debug_out(T x)
{
    cerr << x;
}

template <std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
debug_out(std::tuple<Tp...> &t)
{
    cerr << ")";
}

template <std::size_t I = 0, typename... Tp>
    inline typename std::enable_if < I<sizeof...(Tp), void>::type debug_out(std::tuple<Tp...> &t)
{
    if (I == 0)
    {
        cerr << "(";
    }
    debug_out(std::get<I>(t));
    cerr << ", ";
    debug_out<I + 1, Tp...>(t);
}

template <typename H, typename T>
void debug_out(pair<H, T> x)
{
    cerr << "{";
    debug_out(x.first);
    cerr << ", ";
    debug_out(x.second);
    cerr << "}";
}

template <typename T>
void debug_out(vector<T> x)
{
    cerr << "[";
    for (auto y : x)
    {
        debug_out(y);
        cerr << ", ";
    }
    cerr << "]";
}

template <typename T>
void debug_out(set<T> x)
{
    cerr << "{";
    for (auto y : x)
    {
        debug_out(y);
        cerr << ", ";
    }
    cerr << "}";
}

template <typename T>
void debug_out(T x[], int n)
{
    cerr << "[";
    for (int i = 0; i < n; i++)
    {
        debug_out(x[i]);
        cerr << ", ";
    }
    cerr << "]";
}

template <int N>
void debug_out(bitset<N> b)
{
    cerr << b;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
    debug_out(H);
    cerr << ", ";
    debug_out(T...);
}

//// base debug ends

template <typename T>
void Debug(T x)
{
    cerr << x << "\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
Debug(std::tuple<Tp...> &t)
{
    cerr << ")\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <typename F, typename S>
void Debug(pair<F, S> x)
{
    cerr << "{";
    debug_out(x.first);
    cerr << ", ";
    debug_out(x.second);
    cerr << "}\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <std::size_t I = 0, typename... Tp>
    inline typename std::enable_if < I<sizeof...(Tp), void>::type Debug(std::tuple<Tp...> &t)
{
    if (I == 0)
    {
        cerr << "(";
    }
    debug_out(std::get<I>(t));
    cerr << ", ";
    Debug<I + 1, Tp...>(t);
}

template <typename T>
void Debug(set<T> s)
{
    cerr << ":" << s.size() << ": {";
    for (auto x : s)
    {
        debug_out(x);
        cerr << ", ";
    }
    cerr << "}\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <typename T>
void Debug(multiset<T> s)
{
    cerr << ":" << s.size() << ": {";
    for (auto x : s)
    {
        debug_out(x);
        cerr << ", ";
    }
    cerr << "}\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <typename T>
void Debug(vector<T> s)
{
    cerr << ":" << s.size() << ": [";
    for (auto x : s)
    {
        debug_out(x);
        cerr << ", ";
    }
    cerr << "]\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <typename T, int N>
void Debug(array<T,N> s)
{
    cerr << ":" << s.size() << ": [";
    for (auto x : s)
    {
        debug_out(x);
        cerr << ", ";
    }
    cerr << "]\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <typename K, typename D>
void Debug(map<K, D> s)
{
    cerr << ":" << s.size() << ": {";
    for (auto x : s)
    {   
        cerr<<x.first<<" :";
        debug_out(x.second);
        cerr << ",";
    }
    cerr << "}\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <typename K, typename D>
void Debug(unordered_map<K, D> s)
{
    cerr << ":" << s.size() << ": {";
    for (auto x : s)
    {   
        cerr<<x.first<<" :";
        debug_out(x.second);
        cerr << ",";
    }
    cerr << "}\n";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <int N>
void Debug(bitset<N> b)
{
    cerr << b << " : ";
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <typename T>
void Debug(vector<vector<T>> vv)
{
    cerr << ":" << vv.size() << "\n";
    for (auto x : vv)
    {
        cerr << "[ ";
        for (auto y : x)
        {
            debug_out(y);
            cerr << ", ";
        }
        cerr << "]\n";
    }
    if (ONE_EXTRA_LINE)
    {
        cerr << "\n";
    }
}

template <typename Head, typename... Tail>
void Debug(Head H, Tail... T)
{
    Debug(H);
    cerr << ", ";
    Debug(T...);
}

#define debug(...) cerr << #__VA_ARGS__ << " =", Debug(__VA_ARGS__)

#define mdebug(...) cerr << #__VA_ARGS__ << " =", debug_out(__VA_ARGS__), cerr << "\n"
