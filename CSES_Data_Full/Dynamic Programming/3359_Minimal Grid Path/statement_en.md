# 3359 - Minimal Grid Path

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an $n \times n$ grid whose each square contains a letter.

You should move from the upper-left square to the lower-right square. You can only move right or down.

What is the lexicographically minimal string you can construct?

# Input

The first line has an integer $n$: the size of the grid.

After this, there are $n$ lines that describe the grid. Each line has $n$ letters between `A` and `Z`.

# Output

Print the lexicographically minimal string.

# Constraints

* $1 \le n \le 3000$

# Example

Input:

```cpp
4
AACA
BABC
ABDA
AACA
```

Output:

```cpp
AAABACA
```