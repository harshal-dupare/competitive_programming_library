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
    debug_out(")");
}

template <std::size_t I = 0, typename... Tp>
    inline typename std::enable_if < I<sizeof...(Tp), void>::type debug_out(std::tuple<Tp...> &t)
{
    if (I == 0)
    {
        debug_out("(");
    }
    debug_out(std::get<I>(t));
    debug_out(", ");
    debug_out<I + 1, Tp...>(t);
}

template <typename H, typename T>
void debug_out(pair<H, T> x)
{
    debug_out("{");
    debug_out(x.first);
    debug_out(", ");
    debug_out(x.second);
    debug_out("}");
}

template <typename T>
void debug_out(vector<T> x)
{
    debug_out("[");
    for (auto y : x)
    {
        debug_out(y);
        debug_out(", ");
    }
    debug_out("]");
}

template <typename T>
void debug_out(set<T> x)
{
    debug_out("{");
    for (auto y : x)
    {
        debug_out(y);
        debug_out(", ");
    }
    debug_out("}");
}

template <typename T>
void debug_out(T x[], int n)
{
    debug_out("[");
    for (int i = 0; i < n; i++)
    {
        debug_out(x[i]);
        debug_out(", ");
    }
    debug_out("]");
}

template <int N>
void debug_out(bitset<N> b)
{
    debug_out(b);
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
    debug_out(H);
    debug_out(", ");
    debug_out(T...);
}

//// base debug ends

template <typename T>
void Debug(T x)
{
    debug_out(x);
    debug_out("\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
Debug(std::tuple<Tp...> &t)
{
    debug_out(")\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename F, typename S>
void Debug(pair<F, S> x)
{
    debug_out("{");
    debug_out(x.first);
    debug_out(", ");
    debug_out(x.second);
    debug_out("}\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <std::size_t I = 0, typename... Tp>
    inline typename std::enable_if < I<sizeof...(Tp), void>::type Debug(std::tuple<Tp...> &t)
{
    if (I == 0)
    {
        debug_out("(");
    }
    debug_out(std::get<I>(t));
    debug_out(", ");
    Debug<I + 1, Tp...>(t);
}

template <typename T>
void Debug(set<T> s)
{
    debug_out(":");
    debug_out(s.size());
    debug_out("\n{");
    for (auto x : s)
    {
        debug_out(x);
        debug_out(", ");
    }
    debug_out("}\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename T>
void Debug(multiset<T> s)
{
    debug_out(":");
    debug_out(s.size());
    debug_out("\n{");
    for (auto x : s)
    {
        debug_out(x);
        debug_out(", ");
    }
    debug_out("}\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename T>
void Debug(vector<T> s)
{
    debug_out(":");
    debug_out(s.size());
    debug_out("\n[");
    for (auto x : s)
    {
        debug_out(x);
        debug_out(", ");
    }
    debug_out("]\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename T, int N>
void Debug(array<T, N> s)
{
    debug_out(":");
    debug_out(s.size());
    debug_out("\n[");
    for (auto x : s)
    {
        debug_out(x);
        debug_out(", ");
    }
    debug_out("]\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename K, typename D>
void Debug(map<K, D> s)
{
    debug_out(":");
    debug_out(s.size());
    debug_out("\n{");
    for (auto x : s)
    {
        debug_out(x.first);
        debug_out(":");
        debug_out(x.second);
        debug_out(", ");
    }
    debug_out("}\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename K, typename D>
void Debug(unordered_map<K, D> s)
{
    debug_out(":");
    debug_out(s.size());
    debug_out("\n{");
    for (auto x : s)
    {
        debug_out(x.first);
        debug_out(":");
        debug_out(x.second);
        debug_out(", ");
    }
    debug_out("}\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <int N>
void Debug(bitset<N> b)
{
    debug_out(b.size());
    debug_out("\n");
    debug_out(b);
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename T>
void Debug(vector<vector<T>> vv)
{

    debug_out(":");
    debug_out("(");
    debug_out(vv.size());
    debug_out(", ");
    debug_out(vv.size());
    debug_out(")\n");
    for (auto x : vv)
    {
        debug_out("[ ");
        for (auto y : x)
        {
            debug_out(y);
            debug_out(", ");
        }
        debug_out("]\n");
    }
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename T>
void Debug(stack<T> S)
{
    debug_out(S.size());
    debug_out("\n*");
    while (!S.empty())
    {
        T x = S.top();
        S.pop();
        debug_out(x);
        debug_out(", ");
    }
    debug_out("\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename T>
void Debug(queue<T> S)
{
    debug_out(S.size());
    debug_out("\n*");
    while (!S.empty())
    {
        T x = S.front();
        S.pop();
        debug_out(x);
        debug_out(", ");
    }
    debug_out("\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename T>
void Debug(deque<T> S)
{
    debug_out(S.size());
    debug_out("\n*");
    while (!S.empty())
    {
        T x = S.front();
        S.pop_front();
        debug_out(x);
        debug_out(", ");
    }
    debug_out("-\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename T>
void Debug(priority_queue<T> S)
{
    debug_out(S.size());
    debug_out("\n*");
    while (!S.empty())
    {
        T x = S.top();
        S.pop();
        debug_out(x);
        debug_out(", ");
    }
    debug_out("-\n");
    if (ONE_EXTRA_LINE)
    {
        debug_out("\n");
    }
}

template <typename Head, typename... Tail>
void Debug(Head H, Tail... T)
{
    Debug(H);
    debug_out(", ");
    Debug(T...);
}


#define debug(...) cerr <<  #__VA_ARGS__ << " =", Debug(__VA_ARGS__)

#define mdebug(...) cerr << #__VA_ARGS__ << " =", debug_out(__VA_ARGS__), cerr << "\n"