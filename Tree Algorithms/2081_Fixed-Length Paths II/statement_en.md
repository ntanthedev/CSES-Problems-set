# 2081 - Fixed Length Paths II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given a tree of $n$ nodes, your task is to count the number of distinct paths that have at least $k\_1$ and at most $k\_2$ edges.

# Input

The first input line contains three integers $n$, $k\_1$ and $k\_2$: the number of nodes and the path lengths. The nodes are numbered $1,2,\ldots,n$.

Then there are $n-1$ lines describing the edges. Each line contains two integers $a$ and $b$: there is an edge between nodes $a$ and $b$.

# Output

Print one integer: the number of paths.

# Constraints

* $1 \le k\_1 \le k\_2 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5 2 3
1 2
2 3
3 4
3 5
```

Output:

```cpp
6
```