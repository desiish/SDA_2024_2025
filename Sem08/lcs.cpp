/*Given two strings, s1 and s2, the task is to find the length of the Longest Common Subsequence. If there is no common subsequence, return 0.
A subsequence is a string generated from the original string by deleting 0 or 
more characters and without changing the relative order of the remaining characters. 
For example , subsequences of “ABC” are “”, “A”, “B”, “C”, “AB”, “AC”, “BC” and “ABC”.
In general a string of length n has 2n subsequences.*/
 
#include <iostream>
#include <vector>
#include <algorithm>

// recursive
size_t lcs_rec(std::string& s1, int idx1, std::string& s2, int idx2)
{
	if (idx1 < 0 || idx2 < 0)
		return 0;

	if (s1[idx1] == s2[idx2])
		return 1 + lcs_rec(s1, idx1 - 1, s2, idx2 - 1);

	return std::max(lcs_rec(s1, idx1 - 1, s2, idx2), lcs_rec(s1, idx1, s2, idx2 - 1));
}

size_t lcs_wrapper(std::string& s1, std::string& s2)
{
	return lcs_rec(s1, s1.length() - 1, s2, s2.length() - 1);
}

//dynamic
size_t lcs(std::string& s1, std::string& s2)
{
	size_t len1 = s1.length(), len2 = s2.length();
	std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));

	for (size_t i = 0; i <= len1; i++)
	{
		for (size_t j = 0; j <= len2; j++)
		{
			if (i == 0 || j == 0)
				continue;

			if (s1[i - 1] == s2[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
		}
	}

	return dp[len1][len2];
}
int main()
{
	std::string s1 = "abcaall", s2 = "plaabcaalmmm";

	std::cout << lcs(s1, s2);
}