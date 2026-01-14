# 1644 - Maximum Subarray Sum II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an array of $n$ integers, your task is to find the maximum sum of values in a contiguous subarray with length between $a$ and $b$.

# Input

The first input line has three integers $n$, $a$ and $b$: the size of the array and the minimum and maximum subarray length.

The second line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the array values.

# Output

Print one integer: the maximum subarray sum.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a \le b \le n$
* $-10^9 \le x\_i \le 10^9$

# Example

Input:

```cpp
8 1 2
-1 3 -2 5 3 -5 2 2
```

Output:

```cpp
8
```