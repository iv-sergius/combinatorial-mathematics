// 6-decoding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*
Сложность алгоритма O(n) -- он линейный. Ограничение в длину входной стоки 100
призвано скорее ограничить максимальное значение
*/
unsigned long long getDecodeN(const std::string &str)
{
	/*decodeN[i] Number of decoding if string begin with str[i] */
	std::array<unsigned long long, 101> decodeN;
	decodeN.fill(0);
	decodeN[str.length()] = 1;
	decodeN[str.length() - 1] = str[str.length() - 1] != '0';
	for (size_t i = str.length() - 2; i < 101; --i) { //
		if (str[i] == '0') {
			decodeN[i] = 0;
		} else if (str[i] == '1' || (str[i] == '2' && str[i + 1] <= '6' )) {
			decodeN[i] = decodeN[i + 1] + decodeN[i + 2];
		} else {
			decodeN[i] = decodeN[i + 1];
		}
	}
	return decodeN[0];
}

int main(int argc, char *argv[])
{
	std::ofstream fOut("test.txt");
	fOut << "Hi";
	fOut.close();
	if (argc != 2) {
		std::cerr << "Need 1 argument: file with data" << std::endl;
		return 1;
	}
	std::ifstream fIn(argv[1]);
	if (!fIn.is_open()) {
		std::cerr << "Can't open input file" << std::endl;
		return 1;
	}
	std::string inputStr;
	if (!std::getline(fIn, inputStr)) {
		std::cerr << "Can't read line from file" << std::endl;
		return 1;
	}
	if (inputStr.length() > 100) {
		std::cerr << "To long string" << std::endl;
		return 1;
	}
	fIn.close();
	std::cout << "Total variants of decoding = " << getDecodeN(inputStr) << std::endl;
	return 0;
}
