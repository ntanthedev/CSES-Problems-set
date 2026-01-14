# 1670 - Swap Game

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given a $3 \times 3$ grid containing the numbers $1,2,\dots,9$. Your task is to perform a sequence of moves so that the grid will look like this:
$$\begin{matrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9 \\
\end{matrix}$$
On each move, you can swap the numbers in any two adjacent squares (horizontally or vertically). What is the minimum number of moves required?

# Input

The input has three lines, and each of them has three integers.

# Output

Print one integer: the minimum number of moves.

# Example

Input:

```cpp
2 1 3
7 5 9
8 4 6
```

Output:

```cpp
4
```