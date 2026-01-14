# 3219 - Sliding Window Mex

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers. Your task is to calculate the mex of each window of $k$ elements, from left to right.

The mex is the smallest nonnegative integer that does not appear in the array. For example, the mex for $[3,1,4,3,0,5]$ is $2$.

# Input

The first line contains two integers $n$ and $k$: the number of elements and the size of the window.

Then there are $n$ integers $x\_1,x\_2,\ldots,x\_n$: the contents of the array.

# Output

Print $n-k+1$ values: the mex values.

# Constraints

* $1 \le k \le n \le 2 \cdot 10^5$
* $0 \le x\_i \le 10^9$

# Example

Input:

```cpp
8 3
1 2 1 0 5 1 1 0
```

Output:

```cpp
0 3 2 2 0 2
```