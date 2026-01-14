# 3192 - K Subset Xors

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers. Consider the xors of all $2^n$ subsets of the array (including the empty subset with xor equal to zero).

Your task is to find the $k$ smallest subset xors.

# Input

The first line has two integers $n$ and $k$: the size of the array and the number of subset xors $k$.

The next line has $n$ integers $x\_1, x\_2,\dots, x\_n$: the contents of the array.

# Output

Print $k$ integers: the $k$ smallest subset xors in increasing order.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le k \le \min(2^n, 2 \cdot 10^5)$
* $0 \le x\_i \le 10^9$

# Example

Input:

```cpp
4 9
3 5 14 8
```

Output:

```cpp
0 0 3 3 5 5 6 6 8
```