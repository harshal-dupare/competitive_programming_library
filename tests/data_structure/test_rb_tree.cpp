#include <bits/stdc++.h>
#include "../../lib/utils/timer.hpp"
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/data_structure/rb_tree.hpp"

using namespace std;

int main()
{
    using namespace rb_tree;
    shared_ptr<tree<int, int>> T = make_shared<tree<int, int>>();
    int c = 1, v;

    while (1)
    {

        printf("1.insert \t 2.traverse \t 3.print tree\t 4.exit \n");
        scanf("%d", &c);

        if (c == 1)
        {
            printf("give the value to insert : ");
            scanf("%d", &v);
            rb_insert<int, int>(T, v);
        }
        if (c == 2)
        {
            inorderwalk<int, int>(T->root);
            printf("\n");
        }
        if (c == 3)
        {
            printtree<int, int>(T->root, 0);
            printf("\n");
        }
        if (c == 4)
        {
            break;
        }
        if (c != 1 && c != 2 && c != 3 && c != 4)
        {
            printf("wrong input\n");
        }
    }

    return 0;
}
