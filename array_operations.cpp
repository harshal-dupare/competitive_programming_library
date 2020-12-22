#include <bits/stdc++.h>

// namespaces starts
using namespace std;
// namespaces ends

template <typename I>
class array_op
{
    void diff_array(vector<I> &a, vector<I> &b)
    {
        b[0] = a[0];
        for (I i = 1; i < a.size(); i++)
        {
            b[i + 1] = a[i] - a[i - 1];
        }
    }

    void prefix_array(vector<I> &a, vector<I> &b)
    {
        b[0] = a[0];
        for (I i = 0; i < a.size() - 1; i++)
        {
            b[i + 1] = a[i + 1] + b[i];
        }
    }

    bool isincreasing(vector<I> &a)
    {
        for (I i = 0; i < a.size(); i++)
        {
            if (a[i] < a[i - 1])
            {
                return false;
            }
        }
        return true;
    }

    bool isdecreasing(vector<I> &a)
    {
        for (I i = 0; i < a.size(); i++)
        {
            if (a[i] > a[i - 1])
            {
                return false;
            }
        }
        return true;
    }

    void remap(vector<I> &a)
    {
        vector<pair<I, I>> pr(a.size(), make_pair(0, 0));
        for (I i = 0; i < a.size(); i++)
        {
            pr[i].first = a[i];
            pr[i].second = i;
        }
        sort(pr.begin(), pr.end());

        for (I i = 0; i < a.size(); i++)
        {
            a[pr[i].second] = i;
        }
    }
};


int main()
{
    return 0;
}