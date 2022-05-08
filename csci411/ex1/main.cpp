// CSCI 411 - Spring 2021
// Exam 1 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on Exam 1.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/****************************************************************************************************************
 * A function to determine the length of the longest palindromic subsequence of a given string                  *
 * s - string - a string for which we would like to determine the length of the longest palindromic subsequence *
 * return - int - the length of the longest palindromic subsequence of s                                        *
 * **************************************************************************************************************/
int LPS(string s){
    string sp = s;
    vector<vector<unsigned>> M;
    M.resize(s.size()+1);

    for (unsigned i = 0; i < s.size(); i++)
    {
        sp[i] = s[s.size()-i-1];
    }
    for (unsigned i = 0; i <= s.size(); i++)
    {
        M.at(i).resize(s.size()+1);
        for (unsigned j = 0; j <= s.size(); j++)
        {
            M.at(i).at(j) = 0;
        }
    }

    for (unsigned j = 1; j <= s.size(); j++)
    {
        for (unsigned i = 1; i <= s.size(); i++)
        {
            if (s[j-1] == sp[i-1])
            {
                M.at(i).at(j) = min(M.at(i-1).at(j-1), min(M.at(i-1).at(j), M.at(i).at(j-1)))+1;
            }
            else
            {
                M.at(i).at(j) = max(M.at(i-1).at(j), M.at(i).at(j-1));
            }
        }
    }
    return M.at(s.size()).at(s.size());
}

int main(){
    //get the total number of test sequences
    int n = -1;
    cin >> n;

    //read each test sequence and print the length of the longest palindromic subsequence
    for (int i = 0; i < n; i++){
        string s = "";
        cin >> s;
        cout << LPS(s) << endl;
    }

    return 0;
}
