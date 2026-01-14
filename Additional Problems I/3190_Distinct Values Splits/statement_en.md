# 3190 - Distinct Values Splits

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers. Your task is to count the number of ways to split the array into continuous segments such that all segments consists of distinct values.

# Input

The first line has an integers $n$: the size of the array.

The next line has $n$ integers $x\_1, x\_2,\dots, x\_n$: the contents of the array.

# Output

Print one integer: the answer to the problem modulo $10^9 + 7$.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
4
1 2 1 3
```

Output:

```cpp
6
```

*Explanation*: There are six valid splits:

* $[1], [2], [1], [3]$
* $[1], [2], [1, 3]$
* $[1], [2, 1], [3]$
* $[1], [2, 1, 3]$
* $[1, 2], [1], [3]$
* $[1, 2], [1, 3]$