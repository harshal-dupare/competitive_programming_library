/*
Problem Description
Write a program that counts frequency of each letter in the string (string consists lowercase letters only).
*/

/*
Algorithm
Initialize an array of 26 elements for each letter (a-z) to 0. (array[26]={0})
Scan the entire string and for each string element check the letter and increase the frequency in array by using ASCII value. (array[str[i]-'a']++)
Like in str="aaabbccccddef",
str [3] ='b'
Thus, and str [2]-'a'=1
Thus it increases the frequency of 'b' by 1 (array [str [3]-'a'] turns to be array [1] ++)
Finally print the letter with their respective frequencies. This is the encoded string.
*/

/*
C++ program to find/print frequency of letters in a string
*/

#include <bits/stdc++.h>
using namespace std;

void freq(string s)
{
    //array to store frequency of 26 characters,initialized to 0
    int arr[26] = { 0 };

    for (int i = 0; i < s.length(); i++) {
        // s[i] is the ascii value of the letter at index i & 'a'
        //also gives the ascii value of a, in this way we are
        //checking which alphabet is at index i and increasing its frequency
        arr[s[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (arr[i] != 0)
            printf("%d%c", arr[i], 'a' + i);
    }

    cout << endl;
}

int main()
{
    string s;

    cout << "enter string\n";
    cin >> s;
    cout << "encoded string is : " << endl;
    freq(s);

    return 0;
}
