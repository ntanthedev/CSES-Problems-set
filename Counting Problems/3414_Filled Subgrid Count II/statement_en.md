# 3414 - Filled Subgrid Count II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given a grid of letters. Your task is to calculate, for each letter, the number of *rectangular* subgrids whose each letter is the same.

# Input

The first line has two integers $n$ and $k$: the size of the grid and the number of letters. The letters are the first $k$ uppercase letters.

After this, there are $n$ lines that describe the grid. Each line has $n$ letters.

# Output

Print $k$ lines: for each letter, the number of subgrids.

# Constraints

* $1 \le n \le 3000$
* $1 \le k \le 26$

# Example

Input:

```cpp
5 3
ABBBC
BBBBC
BCAAA
AAAAA
AAAAA
```

Output:

```cpp
64
24
4
```