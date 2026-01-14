# 1748 - Increasing Subsequence II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an array of $n$ integers, your task is to calculate the number of increasing subsequences it contains. If two subsequences have the same values but in different positions in the array, they are counted separately.

# Input

The first input line has an integer $n$: the size of the array.

The second line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the contents of the array.

# Output

Print one integer: the number of increasing subsequences modulo $10^9+7$.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
3
2 1 3
```

Output:

```cpp
5
```

Explanation: The increasing subsequences are $[2]$, $[1]$, $[3]$, $[2,3]$ and $[1,3]$.