#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <cmath>    // for log2, ceil

// Function to calculate theoretical max comparisons
int F(int n)
{
	int sum = 0;
	for (int k = 1; k <= n; ++k)
	{
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(log2(value)));
	}
	return sum;
}

// Utility: print first 10 elements of a container
template <typename Container>
void printFirst10(const Container &c)
{
	std::cout << " ";
	for (size_t i = 0; i < c.size() && i < 10; ++i)
	{
		std::cout << c[i].value << (i + 1 < c.size() && i + 1 < 10 ? " " : "");
	}
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<Item> arr;

	// Parse and validate inputs
	for (int i = 1; i < argc; ++i)
	{
		std::string token(argv[i]);
		for (size_t j = 0; j < token.size(); ++j)
		{
			if (!isdigit(token[j]))
			{
				std::cerr << "Error" << std::endl;
				return 1;
			}
		}
		long val = std::atol(argv[i]);
		if (val < 0 || val > 2147483647L)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		arr.push_back(Item(val, i));
	}

	// Print Before
	std::cout << "Before: ";
	printFirst10(arr);

	int maxComparisonsAllowed = F(static_cast<int>(arr.size()));

	// --- Vector version ---
	int comparisonVec = 0;
	std::vector<Item> vecArr = arr;

	fordJohnsonVector(arr, comparisonVec);
	std::cout << "After (vector):";
	printFirst10(vecArr);

	std::cout << "Comparison count (vector): " << comparisonVec << std::endl;

	if (comparisonVec > maxComparisonsAllowed)
		std::cout << "Vector exceeded max comparisons (" << comparisonVec
				  << " > " << maxComparisonsAllowed << ")" << std::endl;

	std::cout << "Max Comparison Count allowed is " << maxComparisonsAllowed << std::endl;
	return 0;
}
