int getInsertedIndex(const int* X, const int* Y, size_t xLen)
{
	int beg = 0, end = xLen;

	while (beg <= end)
	{
		int mid = beg + (end - beg) / 2;

		if (Y[mid] == -1)
			return mid;

		if (Y[mid] == X[mid])
			beg = mid + 1;
		else
			end = mid - 1;
	}

	return -1;
}
