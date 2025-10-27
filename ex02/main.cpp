#include "PmergeMe.hpp"
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cerrno>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: Invalid Arguments." << std::endl;
		std::cout << "Usage: ./PmergeMe [numbers]" << std::endl;
		return (1);
	}
	std::vector<Item> numVec;
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
		if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || val > INT_MAX)
		{
			std::cerr << "Error: number out of range '" << argv[i] << "'" << std::endl;
			return (1);
		}
		numVec.push_back(Item(static_cast<int>(val), i));
	}
	std::cout << "Before: ";
	for (size_t i = 0; i < numVec.size() && i < 10; ++i)
		std::cout << numVec[i].value << " ";
	if (numVec.size() > 10)
		std::cout << "[...]";
	std::cout << std::endl;
	int countVec = 0;
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
	std::cout << "Time to process a range of " << numVec.size()
			  << " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Comparison count (vector): " << countVec << std::endl;
	bool sorted = true;
	for (int i = 1; i < (int)numVec.size(); ++i)
	{
		if (numVec[i].value < numVec[i-1].value)
		{
			sorted = false;
			break;
		}
	}
	std::cout << "Is Sorted? " << (sorted ? "Yes" : "No") << std::endl;
	return (0);
}
