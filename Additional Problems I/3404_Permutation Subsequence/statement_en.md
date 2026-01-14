# 3404 - Permutation Subsequence

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given two arrays which are permutations, find their longest common subsequence.

A subsequence is a sequence of array elements from left to right that can contain gaps. A common subsequence is a subsequence that appears in both arrays.

# Input

The first line has two integers $n$ and $m$: the sizes of the arrays.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$: the contents of the first array.

The third line has $m$ integers $b\_1,b\_2,\dots,b\_m$: the contents of the second array.

# Output

First print the length of the longest common subsequence.

After that, an example of such a sequence. If there are several solutions, you can print any of them.

# Constraints

* $1 \le n,m \le 2 \cdot 10^5$
* $1 \le a\_i \le n$
* $1 \le b\_i \le m$

# Example

Input:

```cpp
8 6
3 1 2 8 5 7 6 4
6 5 1 2 3 4
```

Output:

```cpp
3
1 2 4
```