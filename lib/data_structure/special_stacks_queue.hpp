#pragma once
#include <stack>
#include <queue>
// FIXME improve the robustness of implementation

template<typename T>
struct min_stack
{
    std::stack<std::pair<T,T>> s;

    min_stack(){};

    void push(T a)
    {
        if(s.empty())
        {
            s.push(std::make_pair(a,a));
            return;
        }
        T new_min = std::min(a,s.top().second);
        s.push(std::make_pair(a,new_min));
    }

    void pop()
    {
        s.pop();
    }

    std::pair<T,T> top()
    {
        return s.top();
    }

    int size()
    {
        return s.size();
    }

    T min()
    {
        return s.top().second;
    }

    bool empty()
    {
        return s.empty();
    }

    void clear()
    {
        while(!s.empty())
        {
            s.pop();
        }
    }

};

template<typename T>
struct min_queue
{
    min_stack<T> s1,s2;

    min_queue(){};

    void transfer()
    {
        while(!s2.empty())
        {
            s1.push(s2.top().first);
            s2.pop();
        }
    }

    void enque(T a)
    {
        s2.push(a);
    }

    void deque()
    {
        if(s1.size()>0)
        {
            s1.pop();
            return;
        }

        if(s2.size()>0)
        {
            this->transfer();
            s1.pop();
        }
    }

    bool empty()
    {
        return s1.empty()&&s2.empty();
    }

    T min()
    {
        if(s1.size()>0)
        {
            if(s2.size()>0)
            {
                return std::min(s1.min(),s2.min());
            }

            return s1.min();
        }

        return s2.min();
    }

    int size()
    {
        return s1.size()+s2.size();
    }

    void clear()
    {
        s1.clear();
        s2.clear();
    }
};

template<typename T>
struct max_stack
{
    std::stack<std::pair<T,T>> s;
    max_stack(){};

    void push(T a)
    {
        if(s.empty())
        {
            s.push(std::make_pair(a,a));
            return;
        }
        T new_max = std::max(a,s.top().second);
        s.push(std::make_pair(a,new_max));
    }

    void pop()
    {
        s.pop();
    }

    std::pair<T,T> top()
    {
        return s.top();
    }

    int size()
    {
        return s.size();
    }

    T max()
    {
        return s.top().second;
    }

    bool empty()
    {
        return s.empty();
    }

    void clear()
    {
        while(!s.empty())
        {
            s.pop();
        }
    }
};

template<typename T>
struct max_queue
{
    max_stack<T> s1,s2;

    max_queue(){};

    void transfer()
    {
        while(!s2.empty())
        {
            s1.push(s2.top().first);
            s2.pop();
        }
    }

    void enque(T a)
    {
        s2.push(a);
    }

    void deque()
    {
        if(s1.size()>0)
        {
            s1.pop();
            return;
        }

        if(s2.size()>0)
        {
            this->transfer();
            s1.pop();
        }
    }

    bool empty()
    {
        return s1.empty()&&s2.empty();
    }

    T max()
    {
        if(s1.size()>0)
        {
            if(s2.size()>0)
            {
                return std::max(s1.max(),s2.max());
            }

            return s1.max();
        }

        return s2.max();
    }

    int size()
    {
        return s1.size()+s2.size();
    }

    void clear()
    {
        s1.clear();
        s2.clear();
    }
};
