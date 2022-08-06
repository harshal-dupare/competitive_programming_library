#pragma once

#include <bits/stdc++.h>
#include "../algebra/linalg.hpp"
#include "../utils/debug_out.hpp"

using namespace std;

template <typename R, typename I>
class markov_chain
{
public:
    I n;
    R eps = R(1e-7);
    linalg::matrix<R, I> A;

    markov_chain()
    {
        this->n = I(0);
    }

    markov_chain(I _n)
    {
        this->n = _n;
        this->A = linalg::matrix<R, I>(_n, _n);
    }

    R P(I i, I j)
    {
        return A.a[i][j];
    }

    void input()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> A.a[i][j];
            }
        }
    }

    void communicating_classes(vector<vector<I>> &components)
    {
        stack<pair<I, I>> call_stack;
        vector<I> vindex(this->n, I(-1));
        vector<I> vlowlink(this->n, I(-1));
        vector<bool> vonstack(this->n, false);
        stack<I> S;
        I index = 0;

        for (I v = 0; v < this->n; v++)
        {
            if (vindex[v] == -1)
            {
                call_stack.push(make_pair(v, I(0)));

                while (!call_stack.empty())
                {
                    pair<I, I> vt = call_stack.top();
                    call_stack.pop();

                    if (vt.second == 0)
                    {
                        // first time we visit vt.first
                        vindex[vt.first] = index;
                        vlowlink[vt.first] = index;
                        index++;
                        S.push(vt.first);
                        vonstack[vt.first] = true;
                    }
                    else
                    {
                        // we have visited it before and recursed for the previous out edge
                        // so account for that update here
                        I prev = vt.second - 1;
                        while (this->P(vt.first, prev) <= this->eps)
                        {
                            prev--;
                        }
                        vlowlink[vt.first] = min(vlowlink[vt.first], vlowlink[prev]);
                    }

                    // find the next outedge to recurse on
                    while (vt.second < this->n && vindex[vt.second] != -1)
                    {
                        if (this->P(vt.first, vt.second) <= this->eps)
                        {
                            vt.second++;
                            continue;
                        }
                        if (vonstack[vt.second])
                        {
                            vlowlink[vt.first] = min(vlowlink[vt.first], vindex[vt.second]);
                        }
                        vt.second++;
                    }

                    // if found then add it to call_stack also add this vertex before to visit it again
                    // for updating its lowlink through this edge
                    if (vt.second<this->n &&this->P(vt.first, vt.second)> this->eps)
                    {
                        call_stack.push(make_pair(vt.first, vt.second + 1));
                        call_stack.push(make_pair(vt.second, I(0)));
                        continue;
                    }

                    // if v is the root of the connected component
                    // pop all the elements on the top till we find root
                    if (vlowlink[vt.first] == vindex[vt.first])
                    {
                        I id = components.size();
                    components.push_back(vector<I>(0));
                    I w;
                    do
                    {
                        w = S.top();
                        S.pop();
                        vonstack[w] = false;
                        components[id].push_back(w);
                    } while (w != vt.first);
                    }
                }
            }
        }

        return;
    }

    // u_ji = p_jk*u_ki+p_ji for j,k != i && u_ii = 1
    // U_i = (I -P_/i)^-1 * P_i
    vector<R> first_passage_probability(I i)
    {
        linalg::matrix<R, I> P_ti = -linalg::submatrix(this->A,vector<I>{i},vector<I>{i},false,true);
        linalg::matrix<R, I> P_ni = linalg::submatrix(this->A,vector<I>{i},vector<I>{i},false,false);

        P_ni -= R(1);

        linalg::matrix<R, I> U_i = P_ti*linalg::inverse(P_ni);

        I dec = 0;
        vector<R> ui(this->n);
        for (I j = 0; j < this->n; j++)
        {
            if (j == i)
            {
                ui[j] = R(1);
                dec++;
                continue;
            }
            ui[j] = U_i.a[j - dec][0];
        }

        return ui;
    }

    // u_ji = p_jk*(1+u_ki)+p_ji=1+p_jk*u_ki for j,k != i && u_ii = 0
    // U_i = 1*(I -P_/i)^-1
    vector<R> first_passage_time(I i)
    {
        linalg::matrix<R, I> P_it = linalg::submatrix(this->A,vector<I>{i},vector<I>{i},true,false);
        linalg::matrix<R, I> P_ti = linalg::matrix<R,I>(this->n-1,I(1),-R(1));
        linalg::matrix<R, I> P_ni = linalg::submatrix(this->A,vector<I>{i},vector<I>{i},false,false);

        P_ni-=R(1);

        linalg::matrix<R, I> U_i = linalg::inverse(P_ni)*P_ti  ;

        I dec = 0;
        vector<R> ui(this->n);
        for (I j = 0; j < this->n; j++)
        {
            if (j == i)
            {
                linalg::matrix<R, I> temp = P_it * U_i;
                ui[j] = (R)1+temp.a[0][0];
                dec++;
                continue;
            }
            ui[j] = U_i.a[j - dec][0];
        }

        return ui;
    }

    // Pt = P over only trensient states
    // S = (I-Pt)^-1
    linalg::matrix<R, I> mean_time_spent_in_transient_states()
    {
    }

    pair<R, R> f_star_u_star_i(I i, bool both = true)
    {
        // f_ii_star = p_ii + P_it*X*P_ti
        // X = I+P_ni+P^2_ni+....
        linalg::matrix<R, I> P_it = linalg::submatrix(this->A,vector<I>{i},vector<I>{i},true,false);
        linalg::matrix<R, I> P_ti = linalg::submatrix(this->A,vector<I>{i},vector<I>{i},false,true);
        linalg::matrix<R, I> P_ni = linalg::submatrix(this->A,vector<I>{i},vector<I>{i},false,false);

        debug(P_ni);
        P_ni-=R(1);
        debug(P_ni);
        P_ni = linalg::inverse(P_ni);
        debug(P_ni);

        linalg::matrix<R, I> U_i = P_it * (P_ni * P_ti);

        pair<R, R> fiui;
        debug(this->P(i, i));
        debug(U_i);
        fiui.first = this->P(i, i) - U_i.a[0][0];
        fiui.second = fiui.first;
        if (both)
        {
            U_i = (P_it * P_ni) * (P_ni * P_ti);
            fiui.second += U_i.a[0][0];
        }
        return fiui;
    }

    vector<R> steady_state_distribution( I i = 0)
    {
        vector<R> pi(this->n);
        linalg::matrix<R, I> Pi = this->A;
        Pi-=R(1);
        for(I t=0;t<this->n;t++)
        {
            Pi.a[t][i] = R(1);
        }

        linalg::matrix<R, I> Ci(I(1),this->n);
        Ci.a[0][i] = R(1);

        Ci = Ci * linalg::inverse(Pi);
        for(I t = 0; t<this->n;t++)
        {
            pi[t] = Ci.a[0][t];
        }

        return pi;
    }

    friend ostream &operator<<(ostream &os, markov_chain<R, I> m)
    {
        for (int i = 0; i < m.n; i++)
        {
            for (int j = 0; j < m.n; j++)
            {
                os << m.A.a[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }
};
