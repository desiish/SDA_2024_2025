/*Given an positive integer N and a list of N integers A[]. 
Each element in the array denotes the maximum length of jump you can cover. 
Find out if you can make it to the last index if you start at the first index of the list.*/
#include <iostream>
#include <vector>

// recursive
size_t jump_game_rec(std::vector<int>& jumps, int curr)
{
	if (curr >= jumps.size())
		return 0;

	size_t min_jumps = SIZE_MAX;

	for (int i = curr + 1; i <= curr + jumps[curr]; i++)
	{
		size_t curr_min_jumps = jump_game_rec(jumps, i);

		if(curr_min_jumps!= SIZE_MAX)
			min_jumps = std::min(curr_min_jumps + 1, min_jumps);
	}

	return min_jumps;
}

// dynamic
size_t jump_game(std::vector<int>& jumps, int curr, std::vector<int>& memo)
{
	if (curr >= jumps.size())
		return 0;

	if (memo[curr] != -1)
		return memo[curr];

	size_t min_jumps = SIZE_MAX;

	for (int i = curr + 1; i <= curr + jumps[curr]; i++)
	{
		size_t curr_min_jumps = jump_game(jumps, i, memo);

		if (curr_min_jumps != SIZE_MAX)
			min_jumps = std::min(curr_min_jumps + 1, min_jumps);
	}

	return memo[curr] = min_jumps;
}

size_t jump_game_wrapper(std::vector<int>& jumps)
{
	std::vector<int> memo(jumps.size(), -1);

	return jump_game(jumps, 0, memo);
}

int main()
{

}