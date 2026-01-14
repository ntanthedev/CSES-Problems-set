# 3311 - Grid Coloring I

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an $n\times m$ grid where each cell contains one character `A`, `B`, `C` or `D`.

For each cell, you must change the character to `A`, `B`, `C` or `D`. The new character must be different from the old one.

Your task is to change the characters in every cell such that no two adjacent cells have the same character.

# Input

The first line has two integers $n$ and $m$: the number of rows and columns.

The next $n$ lines each have $m$ characters: the description of the grid.

# Output

Print $n$ lines each with $m$ characters: the description of the final grid.

You may print any valid solution.

If no solution exists, just print `IMPOSSIBLE`.

# Constraints

* $1 \le n, m \le 500$

# Example

Input:

```cpp
3 4
AAAA
BBBB
CCDD
```

Output:

```cpp
CDCD
DCDC
ABAB
```