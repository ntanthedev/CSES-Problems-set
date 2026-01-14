# 3304 - Visible Buildings Queries

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ buildings in a row numbered $1, 2,\dots, n$ from left to right. You are standing to the left of the first building. You can see a building if it is taller than all buildings to its left.

Your task is to process $q$ queries: If only buildings in range $[a, b]$ existed, how many buildings would you see?

# Input

The first line has two integers $n$ and $q$: the number of buildings and queries.

The second line has $n$ integers $h\_1, h\_2, \dots, h\_n$: the heights of the buildings.

Finally, there are $q$ lines describing the queries. Each line has two integers $a$ and $b$.

# Output

For each query, print one integer: the number of visible buildings.

# Constraints

* $1 \le n \le 10^5$
* $1 \le q \le 2 \cdot 10^5$
* $1 \le h\_i \le 10^9$
* $1 \le a \le b \le n$

# Example

Input:

```cpp
5 3
4 1 2 2 3
1 5
2 5
3 4
```

Output:

```cpp
1
3
1
```