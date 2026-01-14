# 3157 - Collecting Numbers Distribution

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array that contains each number between $1 \dots n$ exactly once. You collect the numbers in increasing order from $1$ to $n$. On each round, you traverse the array from left to right and collect as many consecutive numbers as possible, starting from the smallest number that has not been collected yet.

Your task is to determine, for each $k=1,2,\dots,n$, the number of arrays that require exactly $k$ rounds to collect all the numbers.

# Input

The only line has an integer $n$.

# Output

Print $n$ numbers: for each $k=1,2,\dots,n$, the answer modulo $10^9+7$.

# Constraints

* $1 \le n \le 5000$

# Example

Input:

```cpp
3
```

Output:

```cpp
1
4
1
```

*Explanation*: The arrays are $[1,2,3]$ ($1$ round), $[1,3,2]$ ($2$ rounds), $[2,1,3]$ ($2$ rounds), $[2,3,1]$ ($2$ rounds), $[3,1,2]$ ($2$ rounds), and $[3,2,1]$ ($3$ rounds).