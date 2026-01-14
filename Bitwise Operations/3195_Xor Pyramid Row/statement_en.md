# 3195 - Xor Pyramid Row

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Consider a xor pyramid where each number is the xor of lower-left and lower-right numbers. Here is an example pyramid:
![](382652cc16953396bbaeeabf0e98daec74a4bda09afb8db8da0e67870205fc76)
Given the bottom row of the pyramid, your task is to find the numbers on the $k$-th row from the top.

# Input

The first line has two integers $n$ and $k$: the size of the pyramid and the given row.

The next line has $n$ integers $a\_1,a\_2,\dots,a\_n$: the bottom row of the pyramid.

# Output

Print $k$ integers: the numbers on the $k$-th row from the top.

# Constraints

* $1 \le k \le n \le 2 \cdot 10^5$
* $1 \le a\_i \le 10^9$

# Example

Input:

```cpp
8 5
2 10 5 12 9 5 1 5
```

Output:

```cpp
1 10 5 1 8
```