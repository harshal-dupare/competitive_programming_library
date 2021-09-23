#include <bits/stdc++.h>

#include "../../utils/new_debug_out.hpp"
#include "../real.hpp"
using namespace real;
using namespace std;

typedef double R;
R constexpr main_eps = 0.0012;
typedef precision_real<R,main_eps> pr;

int main()
{
    pr x(-0.00120001);
    cout<<x.n<<endl;
    cout<<x<<endl;
    return 0;
}