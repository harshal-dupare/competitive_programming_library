#include <bits/stdc++.h>

// namespaces starts
using namespace std;
// namespaces ends

#include "debug_out.hpp"

int main()
{
    int i = 0;
    pair<int, int> x({9, 0});
    tuple<int, string, float> t(0, "gyg", 0.987);
    pair<int,pair<pair<int,string>,float>> ppp({3,{{9,"hie"},0.98}});
    vector<pair<int, int>> vk(10);
    vector<tuple<pair<int, int>, int>> vt(10);
    vector<vector<pair<int, int>>> vvk(10, vector<pair<int, int>>(5));
    set<pair<string,int>> sp;
    stack<int> st;
    queue<int> qe;
    deque<int> dqe;

    sp.insert({"fgd",87});
    sp.insert({"fd",7});
    sp.insert({"gd",8});

    map<int,int> mp;
    mp[9]=0;
    mp[5]=0;
    mp[7]=0;
    mp[2]=0;

    st.push(1);
    st.push(1);
    st.push(1);
    st.push(1);
    st.push(1);

    qe.push(1);
    qe.push(1);
    qe.push(1);
    qe.push(1);
    qe.push(1);

    dqe.push_front(1);
    dqe.push_front(2);
    dqe.push_front(3);
    dqe.push_front(4);
    dqe.push_front(5);

    debug(i);
    debug(x);
    debug(t);
    mdebug(i,x,t);
    debug(ppp);
    debug(vk);
    debug(vt);
    debug(vvk);
    debug(mp);
    debug(sp);
    debug(st);
    debug(qe);
    debug(dqe);

    return 0;
}