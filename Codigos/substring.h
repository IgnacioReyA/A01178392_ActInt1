#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
inline string substring(const string &transmissionFileOne, const string &transmissionFileTwo)
{

    ifstream in1(transmissionFileOne);
    if (!in1)
    {
        cerr << "Error opening file: " << transmissionFileOne << endl;
        return "";
    }

    ifstream in2(transmissionFileTwo);
    if (!in2)
    {
        cerr << "Error opening file: " << transmissionFileTwo << endl;
        return "";
    }
    string transmission1String((istreambuf_iterator<char>(in1)), istreambuf_iterator<char>());
    string transmission2String((istreambuf_iterator<char>(in2)), istreambuf_iterator<char>());
    /*
        // Read entire file into a string
        cout << "=== Contents of " << transmissionFileOne << " ===\n";
        cout << transmission1String; // print file1 contents
        cout << "\n\n";

        // Read entire file into a string
        cout << "=== Contents of " << transmissionFileTwo << " ===\n";
        cout << transmission2String; // print file2 contents
        cout << "\n";
    */
    // Finding the longest common substring using dynamic programming
    int n = transmission1String.size();
    int m = transmission2String.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLen = 0, endIdx = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (transmission1String[i - 1] == transmission2String[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen)
                {
                    maxLen = dp[i][j];
                    endIdx = i; // ending index in s1
                }
            }
        }
    }
    return transmission1String.substr(endIdx - maxLen, maxLen);
}
#endif
