// 1-permutation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
using namespace std;

typedef int NumberType;
static const size_t MAX_N = 128;

void PrintArr(NumberType * arr, size_t n) {
	for (size_t i = 0; i < n - 1; ++i) {
		printf("%u ", arr[i]);
	}
	printf("%u\n", arr[n - 1]);
}

size_t findNext(NumberType * arr, size_t from, size_t to, NumberType value) {
	size_t i = to;
	while (arr[i] < value) {
		--i;
	}
	return i;
}

size_t findNextBin(NumberType * arr, size_t from, size_t to, NumberType value) {
	if (arr[to] > value) {
		return to;
	}
	while (to - from > 1) {
		size_t middle = from + (to - from) / 2 ;
		if (arr[middle] < value) {//left higher half
			to = middle;
		}
		else {// right lower half
			from = middle;
		}
	}
	size_t result = (arr[to] > value) ? to : from;
	return result;
}

void reverseArr(NumberType * arr, size_t from, size_t to) {
	NumberType tmp;
	for (; from < to; ++from, --to) {
		tmp = arr[from];
		arr[from] = arr[to];
		arr[to] = tmp;
	}
}

/*
 * ѕолучает некоторую перестановку в виде массива 
 * »змен€ет ее на следующую согласно лексикографичесому пор€дку
 * \returns true если удалось изменить перестановку
 *          false если перестановка максимальна€
 */
bool NextPermutation(NumberType *arr, size_t n)
{
	size_t i = n - 1;
	if (arr[i - 1] < arr[i]) {
		NumberType tmp = arr[i - 1];
		arr[i - 1] = arr[i];
		arr[i] = tmp;
		return true;
	}
	do {
		--i;
	} while (i > 0 && arr[i - 1] > arr[i]);

	if (i > 0) {
		NumberType tmp = arr[i - 1];
		size_t k = i;
		do {
			++k;
		} while (arr[k] > tmp);
		arr[i - 1] = arr[k - 1];
		arr[k - 1] = tmp;
		k = n - 1;
		do {
			tmp = arr[i];
			arr[i] = arr[k];
			arr[k] = tmp;
			++i;
			--k;
		} while (i < k);
		return true;
	}
	else { // no more permutation
		return false;
	}
}

void PrintAllPermutations()
{
	double timeInSec = 0.0;
	bool isResultRight = true;
	size_t i, n = 1;
	static NumberType arr[MAX_N];
	unsigned long long factorial = 1, count;
	
	while (timeInSec < 2.0 && isResultRight)
	{
		count = 0;
		++n;
		factorial *= n;
		for (i = 0; i < n; ++i) {
			arr[i] = static_cast<NumberType>(1 + i);
		}
		time_t startTime = clock();
		do {
			++count;
			//PrintArr(arr, n);
		}
		while(NextPermutation(arr, n));
		time_t endTime = clock();
		timeInSec = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		printf("For n = %2zu  time = %6g", n, timeInSec);
		printf("  Total = %llu", count);
		if (count == factorial)	{
			puts(" OK");
		} else {
			puts(" !ERROR!");
			return;
		}
	}
}

int main(int argv, char* argc[])
{
	PrintAllPermutations();
    return 0;
}

