#include <bits/stdc++.h>
#include "../utils/timer.h"
#include "../utils/debugger.h"

using namespace std;
template <typename I>
class string_matching
{
public:
    char min_char;
    char max_char;
    char out_char;
    I char_size;
    I base;
    I mod = 1e9 + 7;
    vector<I> pi;

    string_matching(char _min_char = 'a', char _max_char = 'z', I _base = 29, char _out_char = '$')
    {
        this->min_char = _min_char;
        this->max_char = _max_char;
        this->out_char = _out_char;
        this->char_size = _max_char - _min_char + 1;
        this->base = _base;
    }

    void set(I n)
    {
        pi.resize(n + 1);
        pi[0] = 1;
        for (I i = 1; i < n + 1; i++)
        {
            pi[i] = (pi[i - 1] * base) % mod;
        }
    }

    // O(|s|)
    void get_prefix_hashes(string &s, vector<I> &hashvec)
    {
        hashvec.resize(s.size());
        hashvec[0] = (s[0] - min_char);
        for (I i = 1; i < s.size(); i++)
        {
            hashvec[i] = (hashvec[i - 1] + pi[i] * (s[i] - min_char)) % mod;
        }
    }

    // O(|s|)
    I hash(string &s)
    {
        I _hash = (s[0] - min_char);
        for (I i = 1; i < s.size(); i++)
        {
            _hash = (_hash + pi[i] * (s[i] - min_char)) % mod;
        }

        return _hash;
    }

    // O(|s|+|p|*|matching_ids|)
    vector<I> rabin_karp(string &s, string &pattern)
    {
        I phash = this->hash(pattern);
        I m = pattern.size();
        I n = s.size();
        vector<I> match_index;
        vector<I> shash;
        this->get_prefix_hashes(s, shash);

        if (shash[m - 1] == phash)
        {
            match_index.push_back(0);
        }

        for (I i = 1; i < n - m; i++)
        {
            if ((pi[i] * phash) % mod == ((shash[m - 1 + i] + mod - shash[i - 1]) % mod))
            {
                bool poss = true;
                for (I j = i; j < i + m; j++)
                {
                    if (s[j] != pattern[j - i])
                    {
                        poss = false;
                        break;
                    }
                }

                if (poss)
                {
                    match_index.push_back(i);
                }
            }
        }

        return match_index;
    }

    // O(|s|)
    void prefix_finction(string &s, vector<I> &prefixf)
    {
        I n = s.size();
        prefixf.resize(n);
        prefixf[0] = 0;
        for (I i = 1; i < n; i++)
        {
            I j = prefixf[i - 1];
            while (j > 0 && s[i] != s[j])
                j = prefixf[j - 1];

            // if last char matches then increase length by 1 ans assign else its zero
            if (s[i] == s[j])
                prefixf[i] = j + 1;
            else
                prefixf[i] = 0;
        }
    }

    // O(|s|+|p|) for proper suffix only
    vector<I> kmp_matching(string &s, string &pattern)
    {
        vector<I> match_id;
        I n = s.size();
        I m = pattern.size();
        vector<I> pref_ptr(m + 1);
        pattern.push_back(this->out_char);
        pref_ptr[0] = 0;
        for (I i = 1; i < m + 1; i++)
        {
            I j = pref_ptr[i - 1];
            while (j > 0 && pattern[i] != pattern[j])
                j = pref_ptr[j - 1];

            if (pattern[i] == pattern[j])
                pref_ptr[i] = j + 1;
            else
                pref_ptr[i] = 0;
        }

        I lst_match = pref_ptr[m - 1];
        I now_match;
        for (I i = 0; i < n; i++)
        {
            I j = lst_match;
            while (j > 0 && s[i] != pattern[j])
                j = pref_ptr[j - 1];

            if (s[i] == pattern[j])
            {
                lst_match = j + 1;
                if (lst_match == m)
                {
                    match_id.push_back(i - m + 1);
                }
            }
            else
            {
                lst_match = 0;
            }
        }

        pattern.pop_back();
        return match_id;
    }

    // O(|w|*|s|)
    void automaton(string &s, vector<vector<I>> &aut)
    {
        s += "$";
        aut.assign(s.size(), vector<I>(char_size, 0));
        vector<I> prefx;
        this->prefix_finction(s, prefx);

        for (I i = 0; i < s.size(); i++)
        {
            for (I k = 0; k < char_size; k++)
            {
                if (i > 0 && min_char + k != s[i])
                    aut[i][k] = aut[prefx[i - 1]][k];
                else
                    aut[i][k] = i + (min_char + k == s[i]);
            }
        }

        s.pop_back();
    }

    // O(|s|)
    void z_function(string &s, vector<I> &zf)
    {
        zf.resize(s.size(), 0);
        I n = s.size();
        zf[0] = 0;
        for (I i = 1, l = 0, r = 0; i < n; i++)
        {
            if (r >= i)
            {
                zf[i] = min(r - i + 1, zf[i - l]);
            }

            while (i + zf[i] < n && s[zf[i] + i] == s[zf[i]])
            {
                zf[i]++;
            }

            if (i + zf[i] - 1 > r)
            {
                l = i;
                r = i + zf[i] - 1;
            }
        }
    }

};

typedef long long ll;

void test_rabin_karp()
{
    string s, p;
    string_matching<ll> sm;
    cin >> s;
    cin >> p;

    sm.set(s.size());
    vector<ll> mtc = sm.rabin_karp(s, p);
    oks(mtc);
}

void test_kmp()
{
    string s, p;
    string_matching<ll> sm;
    cin >> s;
    cin >> p;
    vector<ll> pp;
    sm.prefix_finction(s, pp);
    vector<ll> mtc = sm.kmp_matching(s, p);
    if (mtc.size() > 0)
    {
        cout << (mtc.size()) << endl;
        for (auto x : mtc)
        {
            cout << x + 1 << " ";
        }
        cout << "\n\n";
    }
    else
    {
        cout << ("Not Found\n\n");
    }
}

void test_zf()
{
    string s, p;
    string_matching<ll> sm;
    cin >> s;
    // cin >> p;
    vector<ll> zf(s.size(), 0);
    sm.z_function(s, zf);
    oks(zf);
}

void test_aut()
{
    string s;
    string_matching<ll> sm;
    cin >> s;
    vector<vector<ll>> aut;
    sm.automaton(s, aut);
    vector<ll> pp;
    sm.prefix_finction(s, pp);
    oks(pp);
    okvv(aut);
}

int main()
{
    test_zf();
    return 0;
}