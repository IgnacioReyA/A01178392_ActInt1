#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

inline string substring(const string &transmissionFileOne, const string &transmissionFileTwo)
{
    int n = transmissionFileOne.size();
    int m = transmissionFileTwo.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLen = 0, endIdx = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (transmissionFileOne[i - 1] == transmissionFileTwo[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen)
                {
                    maxLen = dp[i][j];
                    endIdx = i; // ending index in transmissionFileOne
                }
            }
        }
    }

    int startIdx = endIdx - maxLen; // índice inicial del substring
    string result = transmissionFileOne.substr(startIdx, maxLen);

    // Concatenar posiciones al string encontrado
    result += "\nPosición inicial: " + to_string(startIdx) + " \nPosición final: " + to_string(endIdx - 1);

    return result;
}

#endif
