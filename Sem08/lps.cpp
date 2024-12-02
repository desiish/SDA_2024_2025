/*Given a string str, the task is to find the length of the longest substring which is a palindrome.*/

#include <iostream>
#include <vector>

// dynamic
size_t lps(std::string& s)
{
	size_t len = s.length();
	std::vector<std::vector<bool>> dp(len, std::vector<bool>(len, false));

	for (int i = 0; i < len; i++)
		dp[i][i] = true;

	size_t max_len = 1;
	for (int i = 0; i < len - 1; i++)
	{
		if (s[i] == s[i + 1])
		{
			dp[i][i + 1] = true;
			max_len = std::max(max_len, (size_t)2);
		}
	}

	for (size_t i = 3; i <= len; i++)
	{
		for (int beg = 0; beg < len - i + 1; beg++)
		{
			int end = beg + i - 1;

			if (s[beg] == s[end] && dp[beg + 1][end - 1] == true)
			{
				dp[beg][end] = true;
				max_len = std::max(max_len, i);
			}
		}
	}

	return max_len;
}

int main()
{
	std::string s = "abbammallla";
	std::cout << lps(s);
}