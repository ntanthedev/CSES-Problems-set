# 3406 - Triangle Number Sums

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A triangle number is a positive integer of the form $1+2+\dots+k$. The first triangle numbers are $1$, $3$, $6$, $10$ and $15$.

Every positive integer can be represented as a sum of triangle numbers. For example, $42=21+21$ and $1337=1326+10+1$.

Given a positive integer $n$, determine the smallest number of triangle numbers that sum to $n$.

# Input

The first line has an integer $t$: the number of tests.

After that, each line has a positive integer $n$.

# Output

For each test, print the smallest number of triangle numbers.

# Constraints

* $1 \le t \le 100$
* $1 \le n \le 10^{12}$

# Example

Input:

```cpp
5
1
2
3
42
1337
```

Output:

```cpp
1
2
1
2
3
```