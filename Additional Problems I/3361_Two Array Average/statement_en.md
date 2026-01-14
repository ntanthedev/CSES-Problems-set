# 3361 - Two Array Average

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given two arrays of $n$ integers.

Your task is to select a nonempty prefix from both arrays such that the average of all selected numbers is as large as possible.

# Input

The first line has an integer $n$.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$: the numbers in the first array.

The third line has $n$ integers $b\_1,b\_2,\dots,b\_n$: the numbers in the second array.

# Output

Print two numbers: the prefix sizes.

Your answer is considered correct if the absolute or relative difference to the maximum average is at most $10^{-6}$.

# Constraints

* $1 \le n \le 10^5$
* $1 \le a\_i, b\_i \le 10^9$

# Example

Input:

```cpp
4
1 5 5 2
3 1 3 1
```

Output:

```cpp
3 1
```

Explanation: if you choose the prefixes $[1,5,5]$ and $[3]$, the average is $(1+5+5+3)/4=3.5$ which is the maximum possible average.