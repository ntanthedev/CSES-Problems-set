# 3419 - Mex Grid Construction

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Your task is to construct an $n \times n$ grid where each square has the smallest nonnegative integer that does not appear to the left on the same row or above on the same column.

# Input

The only line has an integer $n$.

# Output

Print the grid according to the example.

# Constraints

* $1 \le n \le 100$

# Example

Input:

```cpp
5
```

Output:

```cpp
0 1 2 3 4
1 0 3 2 5
2 3 0 1 6
3 2 1 0 7
4 5 6 7 0
```