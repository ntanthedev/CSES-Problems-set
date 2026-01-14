# 3355 - Sum of Four Squares

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A well known result in number theory is that every non-negative integer can be represented as the sum of four squares of non-negative integers.

You are given a non-negative integer $n$. Your task is to find four non-negative integers $a$, $b$, $c$ and $d$ such that $n = a^2 + b^2 + c^2 + d^2$.

# Input

The first line has an integer $t$: the number of test cases.

Each of the next $t$ lines has an integer $n$.

# Output

For each test case, print four non-negative integers $a$, $b$, $c$ and $d$ that satisfy $n = a^2 + b^2 + c^2 + d^2$.

# Constraints

* $1 \le t \le 1000$
* $0 \le n \le 10^7$
* the sum of all $n$ is at most $10^7$

# Example

Input:

```cpp
3
5
30
322266
```

Output:

```cpp
2 1 0 0
1 2 3 4
314 159 265 358
```