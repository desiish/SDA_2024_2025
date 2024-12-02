///*Given two strings s1 and s2 of lengths m and n respectively and below operations that can be performed on s1.
//Find the minimum number of edits (operations) to convert ‘s1‘ into ‘s2‘.  
//
//Insert: Insert any character before or after any index of s1
//Remove: Remove a character of s1
//Replace: Replace a character at any index of s1 with some other character.*/
 
#include <iostream>
#include <vector>
#include <algorithm>

//recursive
size_t edit_dist_rec(std::string& s1, int idx1, std::string& s2, int idx2)
{
	if (idx1 < 0 || idx2 < 0)
		return 0;

	if (s1[idx1] == s2[idx2])
		return edit_dist_rec(s1, idx1 - 1, s2, idx2 - 1);

	return 1 + std::min({ edit_dist_rec(s1, idx1, s2, idx2 - 1), edit_dist_rec(s1, idx1 - 1, s2, idx2),
		edit_dist_rec(s1, idx1 - 1, s2, idx2 - 1) } );
}

// dynamic
size_t edit_dist(std::string& s1, std::string& s2)
{
	size_t len1 = s1.length(), len2 = s2.length();

	std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));

	for (int i = 0; i <= len1; i++)
	{
		for (int j = 0; j <= len2; j++)
		{
			if (i == 0)
				dp[i][j] = len2;
			else if (j == 0)
				dp[i][j] = len1;
			else if (s1[i - 1] == s2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = std::min({ dp[i][j - 1], 
									  dp[i - 1][j],
									  dp[i - 1][j - 1] });

		}
	}
	
	return dp[len1][len2];
}

int main()
{
	std::string s1 = "aabc", s2 = "lbc";

	std::cout << edit_dist_rec(s1, s1.length() - 1, s2, s2.length() - 1);
}