# 1740 - Intersection Points

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given $n$ horizontal and vertical line segments, your task is to calculate the number of their intersection points.

You can assume that no parallel line segments intersect, and no endpoint of a line segment is an intersection point.

# Input

The first line has an integer $n$: the number of line segments.

Then there are $n$ lines describing the line segments. Each line has four integers: $x\_1$, $y\_1$, $x\_2$ and $y\_2$: a line segment begins at point $(x\_1,y\_1)$ and ends at point $(x\_2,y\_2)$.

# Output

Print the number of intersection points.

# Constraints

* $1 \le n \le 10^5$
* $-10^6 \le x\_1 \le x\_2 \le 10^6$
* $-10^6 \le y\_1 \le y\_2 \le 10^6$
* $(x\_1,y\_1) \neq (x\_2,y\_2)$

# Example

Input:

```cpp
3
2 3 7 3
3 1 3 5
6 2 6 6
```

Output:

```cpp
2
```