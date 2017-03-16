// 2-combination-pure-c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>

using namespace std;

typedef unsigned int NumberType;
static const size_t MAX_N = 256;

void PrintArr(NumberType * arr, size_t n) {
	for (size_t i = 0; i < n - 1; ++i) {
		printf("%u ", arr[i]);
	}
	printf("%u\n", arr[n - 1]);
}

bool NextCombination(NumberType * arr, const size_t n, const size_t k)
{
	if (k == 0) return false;
	if (arr[k - 1] < n)
	{
		++arr[k - 1];
		return true;
	}
	else
	{
		if (k < 2) return false;
		size_t i = k - 2;
		while (i > 0 && arr[i] == i + n + 1 - k)
		{
			--i;
		}
		if (i != 0 || arr[i] != i + n + 1 - k)
		{ // need fill
			++arr[i++];
			for (; i < k; ++i)
			{
				arr[i] = arr[i - 1] + 1;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}

void PrintCombinations()
{
	double timeInSec = 0.0;
	bool isResultRight = true;
	size_t i, n = 4, k;
	NumberType arr[MAX_N];
	unsigned long long nCombination = 1, count;

	while (timeInSec < 2.0 && isResultRight)
	{
		count = 0;
		n += 2;
		k = n / 2;
		nCombination = 1;
		for (i = 0; i < k; ++i) {
			arr[i] = 1 + i;
			nCombination = nCombination * (n - i) / arr[i];
		}
		time_t startTime = clock();
		do {
			++count;
			//PrintArr(arr, k);
		} while (NextCombination(arr, n, k));
		time_t endTime = clock();
		timeInSec = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		printf("For n = %2zu  k = %2zu  time = %6g", n, k, timeInSec);
		printf("  Total = %llu", count);
		if (count == nCombination) {
			puts(" OK");
		}
		else {
			puts(" !ERROR!");
			return;
		}
	}
}

int main()
{
	PrintCombinations();
    return 0;
}

