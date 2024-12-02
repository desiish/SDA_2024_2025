#include <iostream>
#include <vector>

// recursive
size_t fibb_rec(int n)
{
	if (n == 1 || n == 2)
		return 1;

	return fibb_rec(n - 1) + fibb_rec(n - 2);
}

// dynamic programming - memoization
size_t fibb(int n, std::vector<size_t>& memo)
{
	if (n == 1 || n == 2)
		return 1;

	if (memo[n] != 0)
		return memo[n];

	return memo[n] = fibb(n - 1, memo) + fibb(n - 2, memo);
}

size_t fibb_wrapper(int n)
{
	std::vector<size_t> memo(n + 1, 0);
	return fibb(n, memo);
}

int main()
{

}