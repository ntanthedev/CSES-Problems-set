# 3161 - GCD Subsets

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers. Your task is to calculate the number of non-empty subsets whose elements' greatest common divisor is equal to $k$ for each $k = 1,\dots, n$.

# Input

The first line has an integer $n$: the size of the array.

The next line has $n$ integers $x\_1, x\_2,\dots, x\_n$: the contents of the array.

# Output

Print $n$ integers as specified above modulo $10^9 + 7$.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le n$

# Example

Input:

```cpp
5
5 4 4 2 3
```

Output:

```cpp
22 4 1 3 1
```