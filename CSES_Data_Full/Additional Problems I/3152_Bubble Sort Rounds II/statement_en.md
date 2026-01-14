# 3152 - Bubble Sort Rounds II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Bubble sort is a sorting algorithm that consists of a number of rounds. On each round the algorithm scans the array from left to right and swaps any adjacent elements that are in the wrong order.

Given an array of $n$ integers, find out the contents of the array after $k$ bubble sort rounds.

# Input

The first line has two integers $n$ and $k$: the array size and the number of rounds.

The next line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the array contents.

# Output

Print $n$ integers: the contents of the array after $k$ rounds.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $0 \le k \le 10^9$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
5 2
3 2 4 1 4
```

Output:

```cpp
2 1 3 4 4
```