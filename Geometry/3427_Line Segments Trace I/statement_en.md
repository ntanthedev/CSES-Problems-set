# 3427 - Line Segments Trace I

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ line segments whose endpoints have integer coordinates. The left x-coordinate of each segment is $0$ and the right x-coordinate is $m$. The slope of each segment is an integer.

For each x-coordinate $0,1,\dots,m$, find the maximum point in any line segment.

# Input

The first line has two integers $n$ and $m$: the number of line segments and the maximum x-coordinate.

The next $n$ lines describe the line segments. Each line has two integers $y\_1$ and $y\_2$: there is a line segment between points $(0,y\_1)$ and $(m,y\_2)$.

# Output

Print $m+1$ integers: the maximum points for $x=0,1,\dots,m$.

# Constraints

* $1 \le n, m \le 10^5$
* $0 \le y\_1,y\_2 \le 10^9$

# Example

Input:

```cpp
4 5
1 6
7 2
5 5
10 0
```

Output:

```cpp
10 8 6 5 5 6
```