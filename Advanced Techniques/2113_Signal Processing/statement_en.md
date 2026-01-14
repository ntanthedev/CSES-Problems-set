# 2113 - Signal Processing

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given two integer sequences: a signal and a mask. Your task is to process the signal by moving the mask through the signal from left to right. At each mask position calculate the sum of products of aligned signal and mask values in the part where the signal and the mask overlap.

# Input

The first input line consists of two integers $n$ and $m$: the length of the signal and the length of the mask.

The next line consists of $n$ integers $a\_1,a\_2,\ldots,a\_n$ defining the signal.

The last line consists of $m$ integers $b\_1,b\_2,\ldots,b\_m$ defining the mask.

# Output

Print $n+m-1$ integers: the sum of products of aligned values at each mask position from left to right.

# Constraints

* $1 \le n,m \le 2 \cdot 10^5$
* $1 \le a\_i,b\_i \le 100$

# Example

Input:

```cpp
5 3
1 3 2 1 4
1 2 3
```

Output:

```cpp
3 11 13 10 16 9 4
```

Explanation: For example, at the second mask position the sum of aligned products is $2 \cdot 1 + 3 \cdot 3 = 11$.