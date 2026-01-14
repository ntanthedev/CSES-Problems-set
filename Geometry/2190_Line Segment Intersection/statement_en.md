# 2190 - Line Segment Intersection

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are two line segments: the first goes through the points $(x\_1,y\_1)$ and $(x\_2,y\_2)$, and the second goes through the points $(x\_3,y\_3)$ and $(x\_4,y\_4)$.

Your task is to determine if the line segments intersect, i.e., they have at least one common point.

# Input

The first input line has an integer $t$: the number of tests.

After this, there are $t$ lines that describe the tests. Each line has eight integers $x\_1$, $y\_1$, $x\_2$, $y\_2$, $x\_3$, $y\_3$, $x\_4$ and $y\_4$.

# Output

For each test, print "YES" if the line segments intersect and "NO" otherwise.

# Constraints

* $1 \le t \le 10^5$
* $-10^9 \le x\_1, y\_1, x\_2, y\_2, x\_3, y\_3, x\_4, y\_4 \le 10^9$
* $(x\_1,y\_1) \neq (x\_2,y\_2)$
* $(x\_3,y\_3) \neq (x\_4,y\_4)$

# Example

Input:

```cpp
5
1 1 5 3 1 2 4 3
1 1 5 3 1 1 4 3
1 1 5 3 2 3 4 1
1 1 5 3 2 4 4 1
1 1 5 3 3 2 7 4
```

Output:

```cpp
NO
YES
YES
YES
YES
```