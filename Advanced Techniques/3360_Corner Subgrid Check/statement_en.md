# 3360 - Corner Subgrid Check

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given a grid of letters. Your task is to find subgrids whose height and width is at least two and all the corners have the same letter.

For each letter, check if there is a valid subgrid whose corners have that letter.

# Input

The first line has two integers $n$ and $k$: the size of the grid and the number of letters. The letters are the first $k$ uppercase letters.

After this, there are $n$ lines that describe the grid. Each line has $n$ letters.

# Output

Print $k$ lines: for each letter, `YES` if there is a valid subgrid and `NO` otherwise.

# Constraints

* $1 \le n \le 3000$
* $1 \le k \le 26$

# Example

Input:

```cpp
4 5
AAAA
CBBC
CBBE
AAAA
```

Output:

```cpp
YES
YES
NO
NO
NO
```