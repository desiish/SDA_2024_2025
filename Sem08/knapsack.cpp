/*Given N items where each item has some weight and profit associated with it and also given a bag with capacity W, 
[i.e., the bag can hold at most W weight in it]. 
The task is to put the items into the bag such that the sum of profits associated with them is the maximum possible. */
#include <iostream>
#include <algorithm>
#include <vector>

// recursive
size_t max_profit_rec(std::vector<size_t>& wt, std::vector<size_t>& profits, int curr, int currW)
{
	if (curr < 0 || wt[curr] > currW)
		return 0;

	return std::max(max_profit_rec(wt, profits, curr - 1, currW - wt[curr]) + profits[curr],
		max_profit_rec(wt, profits, curr - 1, currW));
}

// dynamic
size_t max_profit(std::vector<size_t>& wt, std::vector<size_t>& profits, int bagWeight)
{
	std::vector<std::vector<size_t>> dp(wt.size() + 1, std::vector<size_t>(bagWeight + 1, 0));
	size_t len = wt.size();
	for (int currIdx = 0; currIdx <= len; currIdx++)
	{
		for (int currWeight = 0; currWeight <= bagWeight; currWeight++)
		{
			if (currIdx == 0 || currWeight == 0)
			{
				dp[currIdx][currWeight] = 0;
				continue;
			}

			if (wt[currIdx - 1] <= currWeight)
			{
				dp[currIdx][currWeight] = std::max(dp[currIdx - 1][currWeight - wt[currIdx - 1]] + profits[currIdx - 1],
					dp[currIdx - 1][currWeight]);
			}
			else
			{
				dp[currIdx][currWeight] = dp[currIdx - 1][currWeight];
			}
		}
	}

	return dp[len][bagWeight];
}

int main()
{
	std::vector<size_t> profits = { 15, 40, 10 };
	std::vector<size_t> wt = { 3, 1, 2 };
	std::cout << max_profit(wt, profits, 3);
}