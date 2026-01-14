# 3151 - Bubble Sort Rounds I

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Bubble sort is a sorting algorithm that consists of a number of rounds. On each round the algorithm scans the array from left to right and swaps any adjacent elements that are in the wrong order.

Given an array of $n$ integers, calculate the number of bubble sort rounds needed to sort the array.

# Input

The first line has an integer $n$: the array size.

The next line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the array contents.

# Output

Print one integer: the number of rounds.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
5
3 2 4 1 4
```

Output:

```cpp
3
```

*Explanation*: Bubble sort needs three rounds to sort this array. The array contents after each round are $[2,3,1,4,4]$, $[2,1,3,4,4]$, and $[1,2,3,4,4]$.