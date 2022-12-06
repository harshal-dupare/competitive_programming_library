#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000000000
struct wedge
{

    int size; // tells if its dimensition of the widge
    struct wedge **child;
    int is;
    int mn;
    int mx;
};

// high
int high(int n, int size)
{

    int temp;

    temp = n / ((int)sqrt(size));
    ;

    return temp;
}

int low(int n, int size)
{

    int temp;

    temp = n % ((int)sqrt(size));

    return temp;
}

// intilz
void intlz(struct wedge *w)
{ // reccursive in to make all wedge till size 2

    int i;
    int k;

    if (w->size > 15)
    {
        k = sqrt((w->size)); // CELEING OF SQRt
        struct wedge **wc;
        w->child = (struct wedge **)malloc(k * sizeof(struct wedge *));
        wc = w->child;

        // printf("%d || ",w->size);
        for (i = 0; i < k; i++)
        {
            wc[i]->is = 0;
            wc[i]->mn = -1;
            wc[i]->mx = MAX;
            wc[i]->size = k;
            wc[i]->child = NULL;
            intlz(wc[i]);
        }
        return;
    }
    else
    {
        k = w->size;
        w->child = (struct wedge **)malloc(k * sizeof(struct wedge *));
        struct wedge **wc = w->child;

        for (i = 0; i < k; i++)
        {
            wc[i]->is = 0;
            wc[i]->mn = -1;
            wc[i]->mx = MAX;
            wc[i]->size = 1;
            wc[i]->child = NULL;
        }
        return;
    }
}

void insrt(struct wedge *w, int x)
{

    struct wedge **wc = w->child;
    int k = w->size, i;

    if (w->size > 15)
    {

        if (w->mx == -1)
        {

            w->mn = x;
            w->mx = x;
            w->is = 1;

            insrt(wc[high(x, w->size)], low(x, w->size));

            return;
        }
        else
        {

            if (x < w->mn)
            {
                w->mn = x;
            }
            if (x > w->mx)
            {
                w->mx = x;
            }

            insrt(wc[high(x, w->size)], low(x, w->size));

            return;
        }
    }
    else
    {

        wc = w->child;
        wc[x]->is = 1;
        wc[x]->mn = x;
        wc[x]->mx = x;
    }

    return;
}

// succ
int succ(struct wedge *w, int x)
{

    struct wedge **wc;
    wc = w->child;
    int i, j, temp;
    int k = w->size;

    if (w->size > 4)
    {

        if (x < w->mn)
        {
            return w->mn;
        }
        if (x >= w->mx)
        {
            return -1;
        }

        if (x < wc[high(x, w->size)]->mn)
        {
            return wc[high(x, w->size)]->mn;
        }

        if (x >= wc[high(x, w->size)]->mx)
        {

            temp = succ(wc[high(x, w->size)], low(x, w->size));
            return wc[high(x, w->size)]->mx;
        }

        for (i = x + 1; i < w->size; i++)
        {
            if (g[i].is == 1)
            {
                break;
            }
        }

        if (i < w->size)
        {
            return i;
        }
        else
        {
            temp = succ(wc, high(x, w->size));
            return b[temp].min;
        }
    }
    else
    {

        for (i = x + 1; i < k; i++)
        {
            if (wc[i]->is == 1)
            {
                break;
            }
        }

        if (i < k)
        {
            return i;
        }
        else
        {
            return -1;
        }
    }
}

//
int pere(struct wedge *w, int x)
{

    struct wedge *wc;
    struct block *b;
    struct block *g;
    int i, j, temp;

    if (w->size > 2)
    {

        if (x > w->mx)
        {
            return w->mx;
        }

        if (x <= w->mn)
        {
            return -1;
        }

        wc = w->next;
        b = wc->a;
        g = w->a;

        if (x > b[high(x, w->size)].max)
        {
            return b[high(x, w->size)].max;
        }

        if (x <= b[high(x, w->size)].min)
        {

            temp = pere(wc, high(x, w->size));
            return b[temp].max;
        }

        for (i = x - 1; i >= 0; i--)
        {
            if (g[i].is == 1)
            {
                break;
            }
        }

        if (i >= 0)
        {
            return i;
        }
        else
        {
            temp = pere(wc, high(x, w->size));
            return b[temp].max;
        }
    }
    else
    {

        g = w->a;

        for (i = x - 1; i >= 0; i--)
        {
            if (g[i].is == 1)
            {
                break;
            }
        }

        if (i >= 0)
        {
            return i;
        }
        else
        {
            return -1;
        }
    }
}
