#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>

struct Item
{
	long value;
	int unique_id;

	Item(): value(0), unique_id(0){}
	Item(long v, int id): value(v), unique_id(id){}
};

struct Pairing
{
	Item mainItem;
	Item pendItem;

	Pairing(const Item &main, const Item &pend) : mainItem(main), pendItem(pend){}
};

struct ItemCompare
{
	bool operator()(const Item &a, const Item &b) const
	{
		return a.value < b.value;
	}
};

void fordJohnsonVector(std::vector<Item> &arr, int &comparisonCount);
int boundedInsertVector(std::vector<Item> &mainChain, const Item &pendItem, const Item *boundItem);
void fordJohnsonDeque(std::deque<Item> &arr, int &comparisonCount);
int boundedInsertDeque(std::deque<Item> &mainChain, const Item &pendItem, const Item *boundItem);
void generateJacobsthalNumbers(int n, std::vector<int> &jacob);
void generateJacobsthalOrder(int n, std::vector<int> &order);

#endif
