# 3428 - Line Segments Trace II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ line segments whose endpoints have integer coordinates. Each x-coordinate is between $0$ and $m$. The slope of each segment is an integer.

For each x-coordinate $0,1,\dots,m$, find the maximum point in any line segment. If there is no segment at some point, the maximum is $-1$.

# Input

The first line has two integers $n$ and $m$: the number of line segments and the maximum x-coordinate.

The next $n$ lines describe the line segments. Each line has four integers $x\_1$, $y\_1$, $x\_2$ and $y\_2$: there is a line segment between points $(x\_1,y\_1)$ and $(x\_2,y\_2)$.

# Output

Print $m+1$ integers: the maximum points for $x=0,1,\dots,m$.

# Constraints

* $1 \le n, m \le 10^5$
* $0 \le x\_1 < x\_2 \le m$
* $0 \le y\_1,y\_2 \le 10^9$

# Example

Input:

```cpp
4 5
1 1 3 3
1 2 4 2
2 4 5 7
2 8 5 2
```

Output:

```cpp
-1 2 8 6 6 7
```