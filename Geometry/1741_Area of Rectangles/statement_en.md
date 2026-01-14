# 1741 - Area of Rectangles

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given $n$ rectangles, your task is to determine the total area of their union.

# Input

The first line has an integer $n$: the number of rectangles.

After that, there are $n$ lines describing the rectangles. Each line has four integers $x\_1$, $y\_1$, $x\_2$ and $y\_2$: a rectangle begins at point $(x\_1,y\_1)$ and ends at point $(x\_2,y\_2)$.

# Output

Print the total area covered by the rectangles.

# Constraints

* $1 \le n \le 10^5$
* $-10^6 \le x\_1 < x\_2 \le 10^6$
* $-10^6 \le y\_1 < y\_2 \le 10^6$

# Example

Input:

```cpp
3
1 3 4 5
3 1 7 4
5 3 8 6
```

Output:

```cpp
24
```