# 3401 - Stick Difference

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given $n$ sticks with lengths $a\_1,a\_2,\dots,a\_n$.
You must make exactly $k$ cuts to the sticks, so that
the number of sticks becomes $n + k$.

After making the cuts, the difference between the length of the longest and shortest sticks should be as small as possible. Your task is to compute the smallest possible difference for all amounts $k=1,2,\dots,m$.

The cuts must keep the lengths of the sticks positive integers. You may assume that the sticks can be cut $m$ times.

# Input

The first line contains two integers $n,m$: the number of sticks and the maximum number of cuts.

The second line contains $n$ integers $a\_1,a\_2,\dots,a\_n$:
the lengths of the sticks.

# Output

Print one line with $m$ integers: the smallest possible difference if exactly $k=1,2,\dots,m$ cuts are made.

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a\_i \le 10^9$

# Example

Input:

```cpp
3 3
7 3 2
```

Output:

```cpp
2 1 2
```

*Explanation*: When $k=1$, you can cut the first stick into two sticks of lengths $3$ and $4$. After this, the stick lengths are $[3,4,3,2]$ and the maximum difference is $2$.