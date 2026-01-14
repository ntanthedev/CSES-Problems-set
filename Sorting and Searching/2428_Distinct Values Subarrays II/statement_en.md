# 2428 - Distinct Values Subarrays II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an array of $n$ integers, your task is to calculate the number of subarrays that have at most $k$ distinct values.

# Input

The first input line has two integers $n$ and $k$.

The next line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the contents of the array.

# Output

Print one integer: the number of subarrays.

# Constraints

* $1 \le k \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
5 2
1 2 3 1 1
```

Output:

```cpp
10
```