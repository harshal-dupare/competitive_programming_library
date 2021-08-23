#pragma once
// FIXME correctness and other mathching algo from cp-algos
#include <string>
#include <vector>

namespace string_matching
{
    char min_char = 'a';
    char max_char = 'z';
    char out_char = '$';
    int char_size = 26;
    int base = 29;
    int mod = 1e9 + 7;

    template <typename I>
    void set(I n, std::vector<I> &pi)
    {
        pi.resize(n + 1);
        pi[0] = 1;
        for (I i = 1; i < n + 1; i++)
        {
            pi[i] = (pi[i - 1] * string_matching::base) % string_matching::mod;
        }
    }

    // O(|s|)
    template <typename I>
    void get_prefix_hashes(std::string &s, std::vector<I> &hashvec, std::vector<I> &pi)
    {
        hashvec.resize(s.size());
        hashvec[0] = (s[0] - string_matching::min_char);
        for (I i = 1; i < s.size(); i++)
        {
            hashvec[i] = (hashvec[i - 1] + pi[i] * (s[i] - string_matching::min_char)) % string_matching::mod;
        }
    }

    // O(|s|)
    template <typename I>
    I hash(std::string &s,std::vector<I> &pi)
    {
        I _hash = (s[0] - string_matching::min_char);
        for (I i = 1; i < s.size(); i++)
        {
            _hash = (_hash + pi[i] * (s[i] - string_matching::min_char)) % string_matching::mod;
        }

        return _hash;
    }

    // O(|s|+|p|*|matching_ids|)
    template <typename I>
    std::vector<I> rabin_karp(std::string &s, std::string &pattern, std::vector<I> &pi)
    {
        I phash = string_matching::hash<I>(pattern,pi);
        I m = pattern.size();
        I n = s.size();
        std::vector<I> match_index;
        std::vector<I> shash;
        string_matching::get_prefix_hashes<I>(s, shash, pi);

        if (shash[m - 1] == phash)
        {
            match_index.push_back(0);
        }

        for (I i = 1; i < n - m; i++)
        {
            if ((pi[i] * phash) % string_matching::mod == ((shash[m - 1 + i] + string_matching::mod - shash[i - 1]) % string_matching::mod))
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
    template <typename I>
    void prefix_function(std::string &s, std::vector<I> &prefixf)
    {
        I n = s.size();
        prefixf.resize(n);
        prefixf[0] = 0;
        for (I i = 1; i < n; i++)
        {
            I j = prefixf[i - 1];
            while (j > 0 && s[i] != s[j])
                j = prefixf[j - 1];

            // if last char matches then increase length by 1
            if (s[i] == s[j])
                j++;

            prefixf[i] = j;
        }
    }

    // O(|s|+|p|) for proper suffix only
    template <typename I>
    std::vector<I> kmp_matching(std::string &s, std::string &pattern)
    {
        std::vector<I> match_id;
        I n = s.size();
        I m = pattern.size();
        std::vector<I> pref_ptr(m + 1);
        pattern.push_back(string_matching::out_char);
        pref_ptr[0] = 0;
        for (I i = 1; i < m + 1; i++)
        {
            I j = pref_ptr[i - 1];
            while (j > 0 && pattern[i] != pattern[j])
                j = pref_ptr[j - 1];

            if (pattern[i] == pattern[j])
                j++;
            pref_ptr[i] = j;
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
    template <typename I>
    void automaton(std::string &s, std::vector<std::vector<I>> &aut)
    {
        s += "$";
        aut.assign(s.size(), std::vector<I>(string_matching::char_size, 0));
        std::vector<I> prefx;
        string_matching::prefix_function(s, prefx);

        for (I i = 0; i < s.size(); i++)
        {
            for (I k = 0; k < string_matching::char_size; k++)
            {
                if (i > 0 && string_matching::min_char + k != s[i])
                    aut[i][k] = aut[prefx[i - 1]][k];
                else
                    aut[i][k] = i + (string_matching::min_char + k == s[i]);
            }
        }

        s.pop_back();
    }

    // O(|s|)
    template <typename I>
    void z_function(std::string &s, std::vector<I> &zf)
    {
        zf.resize(s.size(), 0);
        I n = s.size();
        zf[0] = 0;
        for (I i = 1, l = 0, r = 0; i < n; i++)
        {
            // initial estmate is 0 if i > r
            // i.e. new matching is outside the right most matching
            // else its min of seen region after i and the length of matching at i-l
            // as s[0.....r-l] == s[l....r]
            if (r >= i)
            {
                zf[i] = std::min(r - i + 1, zf[i - l]);
            }

            // run trivial algo to compute the increment on initial estimate
            while (i + zf[i] < n && s[zf[i] + i] == s[zf[i]])
            {
                zf[i]++;
            }

            // update the right most matching
            if (i + zf[i] - 1 > r)
            {
                l = i;
                r = i + zf[i] - 1;
            }
        }
    }
};
