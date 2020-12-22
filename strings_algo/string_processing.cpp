#include <bits\stdc++.h>
#include "../utils/timer.h"

template<typename I>
class string_matching
{
public:
    char min_char;
    char max_char;
    I base;
    string_matching(char min_char='a',char max_char='z')
    {
        this->min_char = min_char;
        this->max_char = max_char;
        this->base = max_char - min_char+1;
    }

    I hash(string s)
    {
        I b = 0;
        for(auto x: s)
        {
            b*=this->base;
        }
    }

    vector<I> KMP_matching()
    {

    }
};