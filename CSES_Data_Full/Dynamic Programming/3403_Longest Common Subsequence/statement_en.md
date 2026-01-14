# 3403 - Longest Common Subsequence

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given two arrays of integers, find their longest common subsequence.

A subsequence is a sequence of array elements from left to right that can contain gaps. A common subsequence is a subsequence that appears in both arrays.

# Input

The first line has two integers $n$ and $m$: the sizes of the arrays.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$: the contents of the first array.

The third line has $m$ integers $b\_1,b\_2,\dots,b\_m$: the contents of the second array.

# Output

First print the length of the longest common subsequence.

After that, print an example of such a sequence. If there are several solutions, you can print any of them.

# Constraints

* $1 \le n,m \le 1000$
* $1 \le a\_i, b\_i \le 10^9$

# Example

Input:

```cpp
8 6
3 1 3 2 7 4 8 2
6 5 1 2 3 4
```

Output:

```cpp
3
1 2 4
```