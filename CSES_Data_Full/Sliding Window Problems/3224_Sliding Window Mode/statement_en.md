# 3224 - Sliding Window Mode

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers. Your task is to calculate the mode each window of $k$ elements, from left to right.

The mode is the most frequent element in an array. If there are several possible modes, choose the smallest of them.

# Input

The first line contains two integers $n$ and $k$: the number of elements and the size of the window.

Then there are $n$ integers $x\_1,x\_2,\ldots,x\_n$: the contents of the array.

# Output

Print $n-k+1$ values: the modes.

# Constraints

* $1 \le k \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
8 3
1 2 3 2 5 2 4 4
```

Output:

```cpp
1 2 2 2 2 4
```