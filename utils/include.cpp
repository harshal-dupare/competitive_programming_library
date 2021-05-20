#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
// identify the include statement
string incs = "#include";
// to identify the my_lib content from "my_lib/.." folder call
vector<string> is_my_lib_inc = {"#include \"my_lib", "#include\"my_lib"};
// exclude these files
vector<string> my_lib_dont_inc = {"my_lib/utils/debugger.hpp", "my_lib/utils/debug_out.hpp", "my_lib/utils/plotting.hpp", "my_lib/utils/timer.hpp"};
// content to ignore in .hpp files
vector<string> hpp_ignore_content = {"#pragma", "using namespace std;", "#include <bits/stdc++.h>"};
// to store all my_lib function
vector<string> my_lib;
// to store included lib strings
vector<string> included_libs;


// gets the include file name 
string get_include_name(string s)
{
    string fs;
    cout<<s<<endl;
    int i = 0;
    string ty="\"";
    while (i < s.size())
    {
        if(s[i] == '<')
        {
            ty=">";
            break;
        }
        if(s[i] == '\"')
        {
            ty="\"";
            break;
        }
        i++;
    }

    if (i == s.size())
    {
        return fs;
    }
    i++;

    for (; s[i] != ty[0]; i++)
    {
        fs.push_back(s[i]);
    }
    return fs;
}

// removes the file from path and returns the directory
string remove_file_from_path(string s)
{
    string dp;
    int i = s.size() - 1;
    while (s[i] != '/' & i >= 0)
    {
        i--;
    }
    i--;
    while (i >= 0)
    {
        dp.push_back(s[i]);
        i--;
    }

    if (dp.size() == 0)
    {
        dp.push_back('.');
    }
    i = dp.size() - 1;
    s.clear();
    while (i >= 0)
    {
        s.push_back(dp[i]);
        i--;
    }

    return s;
}

// return PATH from "#include "PATH""
string get_path(string s)
{
    string fs;
    int i = 0;
    while (s[i] != '\"' && i < s.size())
    {
        i++;
    }
    if (i == s.size())
    {
        return fs;
    }
    i++;
    for (; s[i] != '\"'; i++)
    {
        fs.push_back(s[i]);
    }
    return fs;
}

// matches s & p for s being prefix of p, return true else false
bool prefix_match_strings(string s, string p)
{
    if (p.size() > s.size())
    {
        return false;
    }

    for (int i = 0; i < p.size(); i++)
    {
        if (s[i] != p[i])
        {
            return false;
            break;
        }
    }

    return true;
}

// returns true if s and p refer to same
bool refers_to_same(string s, string p)
{
    if (s.size() == 0 || p.size() == 0)
    {
        return false;
    }

    int i = s.size() - 1, j = p.size() - 1;
    bool mat = true;
    while (i >= 0 && j >= 0)
    {
        if (s[i] != p[j])
        {
            mat = false;
            break;
        }
        i--;
        j--;
    }

    if (i == s.size() - 1 || j == p.size() - 1)
    {
        return false;
    }

    if (i == -1 || j == -1)
    {
        return true;
    }

    if (s[i + 1] == '/' && p[j + 1] == '/')
    {
        return true;
    }

    return false;
}

// returns true if the line is #include
bool is_include(string s)
{

    if (s.size() <= incs.size())
    {
        return false;
    }

    for (int i = 0; i < incs.size(); i++)
    {
        if (s[i] != incs[i])
        {
            return false;
        }
    }

    return true;
}

// return true if it is my_lib include statement but not if its in dont_include
bool is_my_lib_include(string s)
{

    for (int j = 0; j < is_my_lib_inc.size(); j++)
    {
        bool in_my_lib_dont_inc = refers_to_same(get_path(s), my_lib_dont_inc[j]);

        if (in_my_lib_dont_inc)
        {
            return false;
        }
    }

    for (int j = 0; j < is_my_lib_inc.size(); j++)
    {
        bool in_my_lib = prefix_match_strings(s, is_my_lib_inc[j]);

        if (in_my_lib)
        {
            return true;
        }
    }

    return false;
}

// returns true if its already included in processing file
bool is_already_included(string s)
{
    for(int i=0;i<included_libs.size();i++)
    {
        if(refers_to_same(s,included_libs[i]))
        {
            return true;
        }
    }
    return false;
}

// loads lib file paths
vector<string> load_lib_paths(string f)
{
    ifstream file(f);
    vector<string> s;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.size() > 0)
            {
                s.push_back(line);
            }
        }
        file.close();
    }

    return s;
}

// returns true if refers to any my_lib file
bool refers_my_lib(string s)
{
    if (s.size() == 0)
    {
        return false;
    }
    for (int j = 0; j < my_lib.size(); j++)
    {
        bool poss = refers_to_same(s, my_lib[j]);

        if (poss)
        {
            return true;
        }
    }

    return false;
}

// returns true if the line is to be ignored in including
bool to_ignore(string s)
{
    for (int j = 0; j < hpp_ignore_content.size(); j++)
    {
        bool match = prefix_match_strings(s, hpp_ignore_content[j]);

        if (match)
        {
            return true;
        }
    }

    return false;
}

// gets content of any my_lib file without the header file part
string get_contents(string f)
{
    cout << f << endl;
    ifstream file(f);
    string s = "\n";
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.size() > 0 && (!to_ignore(line)))
            {
                if(is_include(line))
                {
                    string iis = get_include_name(line);
                    if(!is_already_included(iis))
                    {
                        included_libs.push_back(iis);
                    }
                    else
                    {
                        continue;
                    }

                    if (refers_my_lib(get_path(line)))
                    {
                        s += get_contents(remove_file_from_path(f) + "/" + get_path(line)) + "\n";
                    }
                    else
                    {
                        s += line + "\n";
                    }
                }
                else
                {
                    s += line + "\n";
                }
            }
        }
        file.close();
    }

    return s;
}

void test()
{

    int n;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        cout << "refers_my_lib()" << refers_my_lib(s) << "\n";
        cout << "is_include()" << is_include(s) << "\n";
        cout << "is_my_lib_include()" << is_my_lib_include(s) << "\n";
        cout << "to_ignore()" << to_ignore(s) << "\n";
    }
}

int main()
{
    my_lib = load_lib_paths("my_lib/my_lib.txt");
    // test();
    char fs[100];
    cin >> fs;
    ifstream file(fs);
    ofstream ofile("submit.cpp");

    if (file.is_open() && ofile.is_open())
    {

        string s;
        while (getline(file, s))
        {
            // if(is_include(s))
            // {
            //     string iis = get_include_name(s);
            //     if(!is_already_included(iis))
            //     {
            //         included_libs.push_back(iis);
            //     }
            //     else
            //     {
            //         continue;
            //     }
            // }

            if (is_include(s) && is_my_lib_include(s))
            {
                string mylib = get_contents(get_path(s));
                ofile << mylib << "\n";
            }
            else
            {
                ofile << s << "\n";
            }
        }
        file.close();
        ofile.close();
    }
    else
    {
        cout << "         ||      Operation failed        ||\n";
    }

    return 0;
}
