#pragma once

namespace constants
{
    constexpr double pi = 3.14159265358979323846264338327950288;
    constexpr double e = 2.71828182845904523536028747135266249;
    constexpr double euler_mascheroni_constant = 0.57721566490153286060651209008240243;
    // solution of xe^x = 1
    constexpr double omega = 0.56714329040978387299996866221035554;
    // limit of avg taken over max cycle length of all permutation of n
    constexpr double golomb_dickman_constant = 0.62432998854355087099293638310083724;
    // average of 1s and 2s in look and say sequence
    constexpr double conways_constant = 1.30357726903429639125709911215255189;
    // A such that floor(a^3^n) is prime for all n
    constexpr double mills_constant = 1.30637788386308069046861449260260571;
}
