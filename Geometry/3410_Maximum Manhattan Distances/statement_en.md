# 3410 - Maximum Manhattan Distances

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A set is initially empty and $n$ points are added to it. Calculate the maximum Manhattan distance of two points after each addition.

# Input

The first line has an integer $n$: the number of points.

The following $n$ lines describe the points. Each line has two integers $x$ and $y$. You can assume that each point is distinct.

# Output

After each addition, print the maximum distance.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $-10^9 \le x, y \le 10^9$

# Example

Input:

```cpp
5
1 1
3 2
2 4
2 1
4 5
```

Output:

```cpp
0
3
4
4
7
```