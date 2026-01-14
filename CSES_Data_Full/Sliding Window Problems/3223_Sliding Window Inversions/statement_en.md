# 3223 - Sliding Window Inversions

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers. Your task is to calculate the number of inversions in each window of $k$ elements, from left to right.

An inversion is a pair of elements where the left element is larger than the right element.

# Input

The first line contains two integers $n$ and $k$: the number of elements and the size of the window.

Then there are $n$ integers $x\_1,x\_2,\ldots,x\_n$: the contents of the array.

# Output

Print $n-k+1$ values: the numbers of inversions.

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
0 1 1 1 2 0
```