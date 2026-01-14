# 3169 - Counting LCM Arrays

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given two integers $n$ and $k$, your task is to count the number of arrays $a\_1, a\_2,\dots, a\_n$ of positive integers where $\operatorname{lcm}(a\_i, a\_{i+1}) = k$ for all $1 \le i < n$.

# Input

The first line has an integer $t$: the number of test cases.

The next $t$ lines have two integers $n$ and $k$: the length of the array and the value of lcm.

# Output

Print $t$ integers: the answer to each test case modulo $10^9 + 7$.

# Constraints

* $1 \le t \le 1000$
* $2 \le n \le 10^9$
* $1 \le k \le 10^9$

# Example

Input:

```cpp
3
3 4
4 6
1337 42
```

Output:

```cpp
11
64
602746233
```

*Explanation*: The arrays for the first test case are $[1, 4, 1]$, $[1, 4, 2]$, $[1, 4, 4]$, $[2, 4, 1]$, $[2, 4, 2]$, $[2, 4, 4]$, $[4, 1, 4]$, $[4, 2, 4]$, $[4, 4, 1]$, $[4, 4, 2]$ and $[4, 4, 4]$.