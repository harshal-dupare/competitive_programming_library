#pragma once

#include "point.hpp"
#include <vector>

template<typename R>
class polygon
{
public:
    int n;
    // clockwise order
    std::vector<point2<R>> points;

    
};