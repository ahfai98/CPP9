#include "PmergeMe.hpp"

void generateJacobsthalNumbers(int n, std::vector<int> &jacob)
{
	jacob.clear();
	jacob.push_back(0);
	jacob.push_back(1);
	while (true)
	{
		int next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		if (next > n)
			break;
		jacob.push_back(next);
	}
}

void generateJacobsthalOrder(int n, std::vector<int> &order)
{
	order.clear();
	if (n <= 0)
		return;
	order.push_back(1);
	if (n == 1)
		return;
	std::vector<int> jacob;
	generateJacobsthalNumbers(n, jacob);

	//start from 3 because already pushed 1
	for (size_t i = 3; i < jacob.size(); ++i)
	{
		int curr = jacob[i];
		int prev = jacob[i - 1];

		for (int j = curr; j > prev; --j)
		{
			if (j <= n && j > 1)
				order.push_back(j);
		}
	}
	//insert remaining numbers in descending order
	int last = jacob.back();
	for (int i = n; i > last; --i)
		order.push_back(i);
}

int boundedInsertVector(std::vector<Item> &mainChain, const Item &pendItem, const Item *boundItem)
{
	size_t upperBoundIndex = mainChain.size();
	if (boundItem != NULL)
	{
		for (size_t i = 0; i < mainChain.size(); ++i)
		{
			if (mainChain[i].unique_id == boundItem->unique_id)
			{
				upperBoundIndex = i;
				break;
			}
		}
	}
	size_t left = 0;
	size_t right = upperBoundIndex;
	int compareCount = 0;
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		++compareCount;
		if (ItemCompare()(mainChain[mid], pendItem))
			left = mid + 1;
		else
			right = mid;
	}
	mainChain.insert(mainChain.begin() + left, pendItem);
	return (compareCount);
}

void fordJohnsonVector(std::vector<Item> &arr, int &comparisonCount)
{
	size_t n = arr.size();
	if (n <= 1)
		return;
	std::vector<Item> mainChain;
	std::vector<Pairing> pairings;
	bool hasLeftover = (n % 2 == 1);
	Item leftoverPend;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		++comparisonCount;
		if (ItemCompare()(arr[i], arr[i + 1]))
		{
			mainChain.push_back(arr[i + 1]);
			pairings.push_back(Pairing(arr[i + 1], arr[i]));
		}
		else
		{
			mainChain.push_back(arr[i]);
			pairings.push_back(Pairing(arr[i], arr[i + 1]));
		}
	}
	if (hasLeftover)
		leftoverPend = arr[n - 1];

	//Recursive sort for main chain again
	fordJohnsonVector(mainChain, comparisonCount);
	//get new pendChain that matches with the previous pairings
	std::vector<Item> pendChain;
	for (size_t i = 0; i < mainChain.size(); ++i)
	{
		for (size_t j = 0; j < pairings.size(); ++j)
		{
			if (mainChain[i].unique_id == pairings[j].mainItem.unique_id)
			{
				pendChain.push_back(pairings[j].pendItem);
				break;
			}
		}
	}
	if (hasLeftover)
		pendChain.push_back(leftoverPend);
	//Get insertion order using Jacobsthal sequence
	std::vector<int> order;
	generateJacobsthalOrder((int)pendChain.size(), order);

	//make copy before insertion to keep track of original bounds
	std::vector<Item> mainChainCopy = mainChain;

	for (size_t k = 0; k < order.size(); ++k)
	{
		size_t idx = order[k] - 1; //index starts from 0
		if (idx < 0 || idx >= pendChain.size())
			continue;
		// Use bound reference from the mainChainCopy
		const Item *boundItem = NULL;
		if (idx < mainChainCopy.size())
			boundItem = &mainChainCopy[idx];
		comparisonCount += boundedInsertVector(mainChain, pendChain[idx], boundItem);
	}
	arr = mainChain;
}

int boundedInsertDeque(std::deque<Item> &mainChain, const Item &pendItem, const Item *boundItem)
{
	size_t upperBoundIndex = mainChain.size();
	if (boundItem != NULL)
	{
		for (size_t i = 0; i < mainChain.size(); ++i)
		{
			if (mainChain[i].unique_id == boundItem->unique_id)
			{
				upperBoundIndex = i;
				break;
			}
		}
	}
	size_t left = 0;
	size_t right = upperBoundIndex;
	int compareCount = 0;
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		++compareCount;
		if (ItemCompare()(mainChain[mid], pendItem))
			left = mid + 1;
		else
			right = mid;
	}
	mainChain.insert(mainChain.begin() + left, pendItem);
	return (compareCount);
}

void fordJohnsonDeque(std::deque<Item> &arr, int &comparisonCount)
{
	size_t n = arr.size();
	if (n <= 1)
		return;
	std::deque<Item> mainChain;
	std::deque<Pairing> pairings;
	bool hasLeftover = (n % 2 == 1);
	Item leftoverPend;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		++comparisonCount;
		if (ItemCompare()(arr[i], arr[i + 1]))
		{
			mainChain.push_back(arr[i + 1]);
			pairings.push_back(Pairing(arr[i + 1], arr[i]));
		}
		else
		{
			mainChain.push_back(arr[i]);
			pairings.push_back(Pairing(arr[i], arr[i + 1]));
		}
	}
	if (hasLeftover)
		leftoverPend = arr[n - 1];

	//Recursive sort for main chain again
	fordJohnsonDeque(mainChain, comparisonCount);
	//get new pendChain that matches with the previous pairings
	std::deque<Item> pendChain;
	for (size_t i = 0; i < mainChain.size(); ++i)
	{
		for (size_t j = 0; j < pairings.size(); ++j)
		{
			if (mainChain[i].unique_id == pairings[j].mainItem.unique_id)
			{
				pendChain.push_back(pairings[j].pendItem);
				break;
			}
		}
	}
	if (hasLeftover)
		pendChain.push_back(leftoverPend);
	//Get insertion order using Jacobsthal sequence
	std::vector<int> order;
	generateJacobsthalOrder((int)pendChain.size(), order);

	//make copy before insertion to keep track of original bounds
	std::deque<Item> mainChainCopy = mainChain;

	for (size_t k = 0; k < order.size(); ++k)
	{
		size_t idx = order[k] - 1; //index starts from 0
		if (idx < 0 || idx >= pendChain.size())
			continue;
		// Use bound reference from the mainChainCopy
		const Item *boundItem = NULL;
		if (idx < mainChainCopy.size())
			boundItem = &mainChainCopy[idx];
		comparisonCount += boundedInsertDeque(mainChain, pendChain[idx], boundItem);
	}
	arr = mainChain;
}
