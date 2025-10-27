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

/*Example txt
Original array
1 2 3 4 5 6 7 8 9 9 9 8 8 7 7

============================================
Level 1

main1 2, 4, 6, 8(1), 9(1), 9(3), 8(3)

pend1 1, 3, 5, 7(1), 9(2), 8(2) 7(2), 7(3)

Store pairing for Level1

2,1
4,3
6,5
8(1),7(1)
9(1),9(2)
9(3),8(2)
8(3),7(2)
8(3),7(3)
============================================
Level 2
main1 is split again into main2 and pend2.

main2 4, 8(1), 9(1)

pend2 2, 6, 9(3), 8(3)

Store pairing for Level2
4,2
8(1),6
9(1),9(3)
============================================
Level 3

main3 8(1)

pend3 4, 9(1)

Store pairing for Level3

8(1),4

main3 only has 1 number, use the algo to insert pend3 numbers into main3
using Bounded Binary Search and insertion order of jacobsthal sequence

main3 becomes 4, 8(1), 9(1)

Return to level 2 with new main3
=======================================
main3 4, 8(1), 9(1)

Create the matching new pend2 using the pairing stored previously.
new pend2 is 2, 6, 9(3), 8(3)

insert pend2 elements into main3

Return to level1 with new main3
=====================================
new main3 is 2 4 6 8(1) 8(3) 9(1) 9(3)

repeat the same steps to get the new pend1 elements
and insert the elements into the main3 to get final result

1 2 3 4 5 6 7 7 7 8 8 8 9 9 9


======================================================
Bounded Binary Search in Jacobsthal and also Descending Order
Jacobsthal can help find the order to maximise the efficiency of insertion.

Binary Search Total Worst Case Comparison count is the same
for 2 to 3 (2 comparison)
4 to 7 (3 comparison)
8 to 15 (4 comparison)
16 to 31 (5 comparison)

Example:
b1 a1 a2 a3 a4 a5 a6 a7 a8

b2 b3 b4 b5 b6 b7 b8
===============================
First insertion
b2 is 2 comparisons

b3 is 2 comparisons

b4 is 3 comparisons

b5 is 3 comparisons

b6 is 3 comparisons

b7 is 3 comparisons

b8 is 4 comparisons
=============================
Insert with the least comparisons first, so b2 and b3
why b3 first? because inserting by descending order decreases
the search range by 1.

b1 a1 a2 a3 a4 a5 a6 a7 a8

inserting b3 you do comparison for only b1 a1 a2 (2 comparisons)
after inserting b3 you get b1 b3 a1 a2 a3
then insert b2 you do comparison for only b1 b3 a1 (2 comparison) with a2 excluded

inserting b2 you do comparison for b1 a1 (2 comparison)
then insert b3 you do comparison for b1 b2 a1 a2(3 comparison) which is worse

by inserting in descending order, your bound decreases by 1, while the inserted number increases it by 1,
so you get constant comparison counts which is the most efficient.
inserting in ascending order, your bound increase by 1, while the inserted number increases it by 1 as well
so your range of search increases by 2.


after inserting b2 and b3,
the main chain is now b1 b2 b3 a1 a2 a3 a4 a5 a6 a7 a8
pend chain is b4 to b8

First insertion 
b4 is 3 comparisons

b5 is 3 comparisons

b6 is 4 comparisons

after inserting b4 and b5,
main chain is now b1 b2 b3 b4 b5 a1 a2 a3 a4 a5 a6 a7 a8

first insertion 
b6 to b11 is 4 comparison
b12 is 5 comparison

repeat the same steps of Jacobsthal insertion and in descending order
*/
