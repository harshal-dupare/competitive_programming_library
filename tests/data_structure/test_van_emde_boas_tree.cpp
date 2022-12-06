#include <bits/stdc++.h>
#include "../../lib/utils/timer.hpp"
#include "../../lib/utils/debug_out.hpp"
#include "../../lib/data_structure/van_emde_boas_tree.hpp"

using namespace std;


int main()
{

    int u, x, c, p, s, i, j;
    struct wedge *w;
    w = (struct wedge *)malloc(sizeof(struct wedge));

    w->size = 16 * 16;
    intlz(w);

    while (1)
    {

        printf("1.Insert || 2.Successor || 3.Predecessor || 4.exit \n");
        scanf("%d", &c);

        if (c == 1)
        {
            printf("Give the number to insert : ");
            scanf("%d", &x);
            insrt(w, x);
        }
        if (c == 2)
        {
            printf("Give the number to find Successor of : ");
            scanf("%d", &x);
            // p = succ(w,x);
            if (p == -1)
            {
                printf("there is no Successor of %d\n", x);
            }
            else
            {
                printf("%d is the Successor of %d\n", p, x);
            }
        }
        if (c == 3)
        {
            printf("Give the number to find Predecessor of : ");
            scanf("%d", &x);
            // p = pere(w,x);
            if (p == -1)
            {
                printf("there is no Predecessor of %d\n", x);
            }
            else
            {
                printf("%d is the Predecessor of %d\n", p, x);
            }
        }
        if (c == 4)
        {
            break;
        }
        if (c != 1 && c != 2 && c != 3 && c != 4)
        {
            printf("Wrong Input\n");
        }
    }
    /*

    struct block* b;
    struct wedge* wc;
    wc=w->next;
    b=w->a;

    for(i=0;i<4;i++){
    for(j=0;j<4;j++){

    printf("%d<%d>%d|",b[4*i+j].min,b[j+4*i].is,b[j+4*i].max);


    }
    }

    b=wc->a;

    for(i=0;i<2;i++){
    for(j=0;j<2;j++){

    printf("%d<%d>%d|",b[2*i+j].min,b[2*i+j].is,b[2*i+j].max);


    }
    }
    */

    return 0;
}
