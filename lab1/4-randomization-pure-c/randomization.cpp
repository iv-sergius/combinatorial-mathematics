// 4-randomization-pure-c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

typedef unsigned int NumberType;
static const size_t MAX_N = 128;

int getN(NumberType *arr, size_t n)
{
	int k = 0;
	for (size_t i = 0; i < n - 1; ++i)
	{
		k += (arr[i] - 1);
		k *= (n - i - 1);
		for (size_t j = i; j < n; ++j) 
			arr[j] -= (arr[j] > arr[i]); // if (arr[j] > arr[i]) --(arr[j]);
	}
	k += arr[n - 1];
	return k;
}

void randomize(NumberType *arr, size_t n)
{
	for (size_t i = 1; i < n; ++i)
	{
		size_t k = rand() % (i + 1);// rand[0, i)
		NumberType tmp = arr[k];
		arr[k] = arr[i];
		arr[i] = tmp;
	}
}

void wrongRandomize(NumberType *arr, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		size_t k = rand() % n;// rand[0, n)
		NumberType tmp = arr[i];
		arr[i] = arr[k];
		arr[k] = tmp;
	}
}

const size_t testN = 5;
const size_t testSize = 120;
const size_t repeatN = testSize * 1000;
const double q005 = 83.01815;
const double q995 = 162.48149;

// this test only for const defined above
double chisqTest120(NumberType *distrib)
{
	double chisqStat = 0.;
	double E = (double)repeatN / testSize;
	for (size_t i = 0; i < testSize; ++i) {
		chisqStat += (distrib[i] - E) * (distrib[i] - E) / E;
	}
	return chisqStat;
}

void testRandomization(void(*randFunc)(NumberType *arr, size_t n))
{
	unsigned int distrib[testSize];
	for (size_t i = 0; i < testSize; ++i) {
		distrib[i] = 0;
	}
	NumberType arr[testN];
	for (size_t i = 0; i < repeatN; ++i) {
		for (size_t j = 0; j < testN; ++j) arr[j] = j + 1;
		randFunc(arr, testN);
		++distrib[getN(arr, testN) - 1];
	}
	for (size_t i = 0; i < testSize; ++i)
		printf("%5u", distrib[i]);
	printf("\n");
	double chisqStat = chisqTest120(distrib);
	if (chisqStat > q005 && chisqStat < q995) {
		printf("All OK : ");
	} else {
		printf("!Error : ");
	}
	printf("chi-square statistic = %g and must lie in (%g ,%g) with p = 0.99\n\n", chisqStat, q005, q995);
}

int main()
{
	testRandomization(randomize);
	testRandomization(wrongRandomize);
    return 0;
}

