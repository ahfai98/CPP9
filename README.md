# C++ Module 09 — 42KL

> Applying STL containers to three real algorithmic problems — Bitcoin price lookup, RPN expression evaluation, and Ford-Johnson merge-insert sort — with a strict constraint: each STL container used only once across the entire module.

## Overview

Module 09 is the culmination of the C++ series. Instead of isolated exercises that demonstrate one concept, each exercise is a self-contained program solving a real algorithmic problem. The constraint — that each STL container type (`std::map`, `std::stack`, `std::deque`, `std::vector`, …) may only appear in one exercise — forces you to think carefully about *which* container fits each problem, rather than defaulting to `std::vector` for everything.

The final exercise, `PmergeMe`, implements the Ford-Johnson merge-insert sort algorithm — one of the comparison-sort algorithms known to minimise the maximum number of comparisons in the worst case for small inputs.

## The Challenge

You must implement three programs that each choose a container deliberately:
- `ex00` needs key-lookup by date → `std::map` (sorted, `lower_bound` for closest-date search)
- `ex01` needs LIFO access for operator evaluation → `std::stack`
- `ex02` needs sorting with two different container types to compare performance → `std::deque` + `std::vector`

Each exercise also requires meaningful error handling for malformed input.

## Concepts Introduced

- **`std::map`**: an ordered key-value container with `O(log n)` lookup; `lower_bound()` returns an iterator to the first key ≥ the query, enabling "closest date" lookup
- **`std::stack`**: a LIFO adapter ideal for expression evaluation; `push`, `pop`, `top`
- **`std::deque`**: a double-ended queue with random access; efficient at both ends
- **Ford-Johnson (merge-insert) sort**: a comparison-sort algorithm that minimises the total number of comparisons by using a specific insertion order (Jacobsthal sequence) and binary search bounds
- **Jacobsthal sequence**: a number sequence used to derive the optimal insertion order in Ford-Johnson, keeping worst-case binary search comparisons constant across groups
- **Performance benchmarking**: measuring execution time with `std::clock` and comparing two container implementations of the same algorithm
- **Date parsing and validation**: strict input validation for ISO date format strings
- **RPN (Reverse Polish Notation)**: a postfix notation where operators follow their operands, evaluated with a stack

## Learning Outcomes

After completing this module you will have:
- Selected the right STL container for each problem based on its access pattern
- Implemented a lookup table using `std::map` with date-range searching
- Written a complete RPN calculator with proper error handling
- Implemented the Ford-Johnson merge-insert sort and understood why the Jacobsthal insertion order minimises comparisons
- Benchmarked two container implementations of the same algorithm and understood cache/allocation trade-offs
- Understood how the 42 constraint (one container per exercise) deepens understanding of container semantics

## Exercises

### ex00 — Bitcoin Exchange

Reads a historical BTC price database from `data.csv` and evaluates a user-provided ledger file of `date | amount` pairs. For each entry, finds the closest date in the database that is ≤ the given date using `std::map::lower_bound`, multiplies the BTC price by the amount, and prints the result.

```bash
./btc input.txt
```

```
# input.txt
2011-01-03 | 3
2022-03-29 | 1.5

# Output
2011-01-03 => 3 = 0.9  (3 BTC × $0.3 on that date)
2022-03-29 => 1.5 = 66848.1
```

Error cases: invalid date format, negative amount, amount > 1000, date before the database begins.

---

### ex01 — Reverse Polish Notation (RPN)

Evaluates a mathematical expression in postfix notation. Each token is either a number pushed onto a stack or an operator (`+`, `-`, `*`, `/`) that pops two operands, computes the result, and pushes it back. The final stack value is the answer.

```bash
./RPN "3 4 +"          # 7
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"   # 42
./RPN "1 2 * 2 / 2 * 2 4 - +"        # 0
./RPN "( 1 + 1 )"      # Error (no parentheses in RPN)
```

---

### ex02 — PmergeMe (Ford-Johnson Sort)

Sorts a sequence of positive integers using the Ford-Johnson merge-insert sort algorithm, implemented twice — once with `std::deque` and once with `std::vector` — then prints both results and their execution times.

**Ford-Johnson overview:**
1. Pair up elements; for each pair identify the larger (main) and smaller (pend).
2. Recursively sort the main chain by applying the algorithm to it.
3. Insert the pend elements into the sorted main chain using binary search, but in the order given by the Jacobsthal sequence — this order ensures each binary search uses the minimum possible comparisons.
4. Repeat until fully sorted.

```bash
./PmergeMe 3 5 9 7 4 1 8 2 6
# Before: 3 5 9 7 4 1 8 2 6
# After:  1 2 3 4 5 6 7 8 9
# Time to process a range of 9 elements with std::vector: 0.00031 us
# Time to process a range of 9 elements with std::deque:  0.00028 us
```

## How to Build

```bash
cd ex00 && make && ./btc input.txt
cd ex01 && make && ./RPN "5 1 2 + 4 * + 3 -"
cd ex02 && make && ./PmergeMe $(shuf -i 1-100 -n 20 | tr '\n' ' ')
```
