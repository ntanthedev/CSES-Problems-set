# 3218 - Knight Moves Queries

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a knight on an infinite chessboard. The rows and columns are $1$-indexed.

Your task is to efficiently process queries of the form: when the knight starts at position $(x,y)$, what is the minimum number of moves the knight needs to do to reach the top-left corner.

# Input

The first line has an integer $n$: the number of queries.

After this, there are $n$ lines. Each line has two integers $x$ and $y$: the knight position.

# Output

For each query, print the minimum number of moves.

# Constraints

* $1 \le n \le 10^5$
* $1 \le x, y \le 10^9$

# Example

Input:

```cpp
4
1 1
2 3
4 1
42 1337
```

Output:

```cpp
0
1
3
669
```