#pragma once

#include <bits/stdc++.h>

namespace debug_space
{
    void debug_out();
    template <typename T>
    void debug_out(const T &x);
    template <typename H, typename T>
    void debug_out(const std::pair<H, T> &x);
    template <std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I == sizeof...(Tp), void>::type
    debug_out(const std::tuple<Tp...> &t);
    template <std::size_t I = 0, typename... Tp>
        inline typename std::enable_if < I<sizeof...(Tp), void>::type debug_out(const std::tuple<Tp...> &t);
    template <typename H, typename T>
    void debug_out(const std::pair<H, T> &x);
    template <typename T>
    void debug_out(const std::vector<T> &x);
    template <typename T>
    void debug_out(const std::set<T> &x);
    template <typename T, typename I>
    void debug_out(T *x, const std::vector<I> &dim);
    template <typename T>
    void debug_out(const std::multiset<T> &s);
    template <typename T, int N>
    void debug_out(const std::array<T, N> &s);
    template <typename K, typename D>
    void debug_out(const std::map<K, D> &s);
    template <typename K, typename D>
    void debug_out(const std::unordered_map<K, D> &s);
    template <int N>
    void debug_out(const std::bitset<N> &b);
    template <typename T>
    void debug_out(const std::vector<std::vector<T>> &vv);
    template <typename T>
    void debug_out(const std::stack<T> &_S);
    template <typename T>
    void debug_out(const std::queue<T> &_S);
    template <typename T>
    void debug_out(const std::deque<T> &_S);
    template <typename T>
    void debug_out(const std::priority_queue<T> &_S);

    void debug_out()
    {
        std::cerr << "\n";
    }

    template <typename T>
    void debug_out(const T &x)
    {
        std::cerr << x;
    }

    template <std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I == sizeof...(Tp), void>::type
    debug_out(const std::tuple<Tp...> &t)
    {
        debug_out(")");
    }

    template <std::size_t I = 0, typename... Tp>
        inline typename std::enable_if < I<sizeof...(Tp), void>::type debug_out(const std::tuple<Tp...> &t)
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
    void debug_out(const std::pair<H, T> &x)
    {
        debug_out("{");
        debug_out(x.first);
        debug_out(", ");
        debug_out(x.second);
        debug_out("}");
    }

    template <typename T>
    void debug_out(const std::vector<T> &x)
    {
        debug_out("[ ");
        for (auto y : x)
        {
            debug_out(y);
            debug_out(", ");
        }
        debug_out("]");
    }

    template <typename T>
    void debug_out(const std::set<T> &x)
    {
        debug_out("{ ");
        for (auto y : x)
        {
            debug_out(y);
            debug_out(", ");
        }
        debug_out("}");
    }

    template <typename T, typename I>
    void debug_out(T *x, const std::vector<I> &dim)
    {
        // genera n-d array with dim as dimensions
        std::vector<I> ids(dim.size(), 0);
        I cr = 0;
        I id = 0;
        I loc = 0;
        while (cr == 0)
        {
            /*
            I loc = 0;
            id=0;
            while(id<(I)dim.size())
            {
                loc *= dim[id];
                loc += ids[id];
                id++;
            }
            */
            debug_out(*(x + loc));
            debug_out(" ");
            loc++;

            cr = 1;
            id = (I)((int)dim.size() - 1);
            while (id >= 0 && cr > 0)
            {
                ids[id] += cr;
                cr = ids[id] / dim[id];
                ids[id] %= dim[id];
                id--;
                if (cr > 0)
                {
                    debug_out();
                }
            }
        }
    }

    template <typename T>
    void debug_out(const std::multiset<T> &s)
    {
        debug_out("{ ");
        for (auto x : s)
        {
            debug_out(x);
            debug_out(", ");
        }
        debug_out("}");
    }

    template <typename T, int N>
    void debug_out(const std::array<T, N> &s)
    {
        debug_out("[ ");
        for (auto x : s)
        {
            debug_out(x);
            debug_out(", ");
        }
        debug_out("]");
    }

    template <typename K, typename D>
    void debug_out(const std::map<K, D> &s)
    {
        debug_out("{ ");
        for (auto x : s)
        {
            debug_out(x.first);
            debug_out(" : ");
            debug_out(x.second);
            debug_out(", ");
        }
        debug_out("}");
    }

    template <typename K, typename D>
    void debug_out(const std::unordered_map<K, D> &s)
    {
        debug_out("{ ");
        for (auto x : s)
        {
            debug_out(x.first);
            debug_out(":");
            debug_out(x.second);
            debug_out(", ");
        }
        debug_out("}");
    }

    template <int N>
    void debug_out(const std::bitset<N> &b)
    {
        debug_out("[");
        debug_out(b.size());
        debug_out("]:");
        debug_out(b);
    }

    template <typename T>
    void debug_out(const std::vector<std::vector<T>> &vv)
    {
        debug_out(":(");
        debug_out(vv.size());
        debug_out(",");
        if(!vv.empty()) 
        {
            debug_out(vv[0].size());
        }
        else
        {
             debug_out("0)\n");
             return;
        }
        debug_out(")\n");
        debug_out("[");
        int i=1;
        for (auto x : vv)
        {
            debug_out("[");
            for (auto y : x)
            {
                debug_out(y);
                debug_out(",");
            }
            debug_out("],");
            if(i<(int)vv.size()) debug_out("\n ");
            else debug_out("]");
            i++;
        }
    }

    template <typename T>
    void debug_out(const std::stack<T> &_S)
    {
        std::stack<T> S = _S;
        debug_out(" { *");
        while (!S.empty())
        {
            T x = S.top();
            S.pop();
            debug_out(x);
            debug_out(", ");
        }
        debug_out("}");
    }

    template <typename T>
    void debug_out(const std::queue<T> &_S)
    {
        std::queue<T> S = _S;
        debug_out(" { *");
        while (!S.empty())
        {
            T x = S.front();
            S.pop();
            debug_out(x);
            debug_out(", ");
        }
        debug_out("}");
    }

    template <typename T>
    void debug_out(const std::deque<T> &_S)
    {
        std::deque<T> S = _S;
        debug_out(" { *");
        while (!S.empty())
        {
            T x = S.front();
            S.pop_front();
            debug_out(x);
            debug_out(", ");
        }
        debug_out("}");
    }

    template <typename T>
    void debug_out(const std::priority_queue<T> &_S)
    {
        std::priority_queue<T> S = _S;
        debug_out(" { *");
        while (!S.empty())
        {
            T x = S.top();
            S.pop();
            debug_out(x);
            debug_out(", ");
        }
        debug_out("}");
    }

    template <typename Head, typename... Tail>
    void debug_out(Head H, Tail... T)
    {
        debug_out(H);
        debug_out(", ");
        debug_out(T...);
    }
}

#define debug(...) std::cerr << "# " << #__VA_ARGS__ << " = ", debug_space::debug_out(__VA_ARGS__), debug_space::debug_out()
