#include "PmergeMe.hpp"
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <cmath>

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

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: Invalid Arguments." << std::endl;
		std::cout << "Usage: ./PmergeMe [numbers]" << std::endl;
		return (1);
	}
	std::vector<Item> numVec;
	std::deque<Item> numDeq;
	for (int i = 1; i < argc; ++i)
	{
		char *endptr;
		errno = 0;
		long val = std::strtol(argv[i], &endptr, 10);
		if (*endptr != '\0')
		{
			std::cerr << "Error: invalid number '" << argv[i] << "'" << std::endl;
			return (1);
		}
		if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || val > INT_MAX || val < 0)
		{
			std::cerr << "Error: number out of range '" << argv[i] << "'" << std::endl;
			return (1);
		}
		numVec.push_back(Item(static_cast<int>(val), i));
		numDeq.push_back(Item(static_cast<int>(val), i));
	}
	std::cout << "Before: ";
	for (size_t i = 0; i < numVec.size() && i < 10; ++i)
		std::cout << numVec[i].value << " ";
	if (numVec.size() > 10)
		std::cout << "[...]";
	std::cout << std::endl;
	int countVec = 0;
	int countDeq = 0;
	clock_t startVec = clock();
	fordJohnsonVector(numVec, countVec);
	clock_t endVec = clock();
	double vecTime = (double)(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;
	std::cout << "After (vector): ";
	for (size_t i = 0; i < numVec.size() && i < 10; ++i)
		std::cout << numVec[i].value << " ";
	if (numVec.size() > 10)
		std::cout << "[...]";
	std::cout <<std::endl;
	clock_t startDeq = clock();
	fordJohnsonDeque(numDeq, countDeq);
	clock_t endDeq = clock();
	double deqTime = (double)(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;
	std::cout << "After (deque): ";
	for (size_t i = 0; i < numDeq.size() && i < 10; ++i)
		std::cout << numDeq[i].value << " ";
	if (numDeq.size() > 10)
		std::cout << "[...]";
	std::cout <<std::endl;
	std::cout << "Time to process a range of " << numVec.size()
			  << " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Comparison count (vector): " << countVec << std::endl;
	std::cout << "Time to process a range of " << numDeq.size()
			  << " elements with std::deque : " << deqTime << " us" << std::endl;
	std::cout << "Comparison count (deque): " << countDeq << std::endl;
	bool sorted = true;
	for (size_t i = 1; i < numVec.size(); ++i)
	{
		if (numVec[i].value < numVec[i-1].value)
		{
			sorted = false;
			break;
		}
	}
	std::cout << "Is Sorted? " << (sorted ? "Yes" : "No") << std::endl;
	std::cout << "Max Comparison Count Allowed is " << F((int)numVec.size()) << std::endl;
	return (0);
}
