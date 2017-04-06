// 5-backpaking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct thing_s {
	int weight;
	int cost;
	float value;
} SThing;

typedef struct data_s {
	size_t n;
	size_t T;
	std::vector <SThing> things;
} SData;

void ReadDataFromStream(std::istream &inStream, SData &data)
{
	if (!(inStream >> data.n) || !(inStream >> data.T)) {
		throw std::logic_error("Wrong data");
	}
	std::vector <int> tmpVector { std::istream_iterator<int>(inStream), std::istream_iterator<int>() };
	if (tmpVector.size() != 2 * data.n) {
		throw std::logic_error("Wrong data");
	}
	data.things.resize(data.n);
	for (size_t i = 0; i < data.n; ++i) {
		data.things[i].weight = tmpVector[i];
		data.things[i].cost = tmpVector[data.n + i];
		data.things[i].value = data.things[i].cost / (float) data.things[i].weight;
	}
}

std::vector <SThing> SolveProblem(SData &data)
{
	if (data.n >= 8 * sizeof(int)) {
		throw std::length_error("To many things");
	}
	std::vector <SThing> result = {};
	//result.resize(data.n);
	std::sort(data.things.begin(), data.things.end(), [](const SThing &lhs, const SThing &rhs) {
		return lhs.value > rhs.value;
	});
	std::vector <bool> index;
	index.resize(data.n);
	std::vector <int> tailCost;
	tailCost.resize(data.n);
	tailCost[data.n - 1] = 0;
	int maxCost, sumCost = 0, sumWeight = 0;
	/*for (size_t i = data.n - 1; i > 0; --i) {
		tailCost[i - 1] = tailCost[i] + data.things[i].cost;
	}
	for (size_t i = 0; i < data.n; ++i) {
		// if 
		if (sumWeight + data.things[i].weight <= data.T) {
			index[i] = true;
			sumWeight += data.things[i].weight;
			sumCost += data.things[i].cost;
		}
		else {
			index[i] = false;
		}
	}*/
	maxCost = 0;
	std::vector <bool> maxIndex = index;
	unsigned long k = 0;
	k = 1 << data.n;
	do {
		--k;
		sumCost = 0;
		sumWeight = 0;
		for (size_t i = 0; i < data.n; ++i) {
			index[i] = (k >> i) & 1;
			if (index[i]) {
				sumCost += data.things[i].cost;
				sumWeight += data.things[i].weight;
			}
		}
		if (sumCost > maxCost && sumWeight <= data.T) {
			maxIndex = index;
			maxCost = sumCost;
		}
	} while (k > 0);

	// form result
	for (size_t i = 0; i < data.n; ++i) {
		if (maxIndex[i]) result.push_back(data.things[i]);
	}
	return result;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "Need 1 argument: file with data" << std::endl;
		return 1;
	}
	std::ifstream fIn(argv[1]);
	if (!fIn.is_open()) {
		std::cerr << "Can't open input file" << std::endl;
		return 1;
	}
	try
	{
		SData data;
		ReadDataFromStream(fIn, data);
		std::vector <SThing> result = SolveProblem(data);
		int cost = 0, weight = 0;
		for (auto &item : result) {
			cost += item.cost;
			weight += item.weight;
		}
		std::cout << cost << std::endl;
		std::clog << "Number of things = " << result.size() << std::endl;
		std::clog << "Weight of backpack = " << weight << " (max is " << data.T << " )" << std::endl;
		std::clog << "Cost of backpack = " << cost << std::endl;
	}
	catch (std::exception &ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
	}
    return 0;
}

