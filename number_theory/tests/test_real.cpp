#include <bits/stdc++.h>

#include "../../utils/debug_out.hpp"
#include "../../utils/timer.hpp"
#include "../../algebra/linear_eq.hpp"
#include "../../number_theory/math_constants.hpp"

void test_round()
{
    double N = 5000000.0;
    double D = 77.0;
    timer tm;
    double newt=0;
    double oldt=0;
    for(double i=-N;i<=N;i++)
    {
        double r = i/D;
        tm.set();
        //double oldr = integral_part<double>(r);
        oldt += tm.get();
        tm.set();
        double newr = decompose<double>(r).second;
        newt+= tm.get();
        if(newr!=oldr) 
        {
            mdebug(i,r,oldr,newr);
            break;
        }

    }
    // newt/oldt =0.984931
    debug(newt/oldt);
}
