
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N,M;
    
    cin>>N;
    vector<int>px(N),py(N),pt(N);
    for(int i=0;i<N;i++)
    {
        cin>>px[i]>>py[i]>>pt[i];
    }

    cin>>M;
    vector<int> hx(M),hy(M);
    for (int i = 0; i < M; i++)
    {
        cin>>hx[i]>>hy[i];
    }
    
    return 0;
}
