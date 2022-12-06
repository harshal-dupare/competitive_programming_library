#include <bits/stdc++.h>
#include "../../lib/utils/timer.hpp"
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/data_structure/kd_trees.hpp"

using namespace std;


int main()
{

    int i, j, k, d, n;
    struct tree *T;
    T = (struct tree *)malloc(sizeof(struct tree));
    T->root = NULL;
    int c = 1, *v;

    printf("give the \"d\"  of tree: ");
    scanf("%d", &d);
    v = (int *)malloc(d * sizeof(int));

    while (1)
    {

        printf("1.insert \t 2.traverse \t 3.print tree\t 4.exit \n");
        scanf("%d", &c);

        if (c == 1)
        {
            printf("give the point to insert : ");

            for (i = 0; i < d; i++)
            {
                scanf("%d", &v[i]);
            }
            kd_insert(T, v, d);
        }
        if (c == 2)
        {
            inorderwalk(T->root, d);
            printf("\n");
        }
        if (c == 3)
        {
            printtree(T->root, 0, d);
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
