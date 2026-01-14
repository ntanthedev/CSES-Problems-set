# 1652 - Forest Queries

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an $n \times n$ grid representing the map of a forest. Each square is either empty or contains a tree. The upper-left square has coordinates $(1,1)$, and the lower-right square has coordinates $(n,n)$.

Your task is to process $q$ queries of the form: how many trees are inside a given rectangle in the forest?

# Input

The first input line has two integers $n$ and $q$: the size of the forest and the number of queries.

Then, there are $n$ lines describing the forest. Each line has $n$ characters: `.` is an empty square and `*` is a tree.

Finally, there are $q$ lines describing the queries. Each line has four integers $y\_1$, $x\_1$, $y\_2$, $x\_2$ corresponding to the corners of a rectangle.

# Output

Print the number of trees inside each rectangle.

# Constraints

* $1 \le n \le 1000$
* $1 \le q \le 2 \cdot 10^5$
* $1 \le y\_1 \le y\_2 \le n$
* $1 \le x\_1 \le x\_2 \le n$

# Example

Input:

```cpp
4 3
.*..
*.**
**..
****
2 2 3 4
3 1 3 1
1 1 2 2
```

Output:

```cpp
3
1
2
```