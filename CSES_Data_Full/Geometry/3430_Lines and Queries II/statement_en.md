# 3430 - Lines and Queries II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Your task is to efficiently process the following types of queries:

1. Add a line $ax+b$ that is active in range $[l,r]$
2. Find the maximum point in any active line at position $x$

# Input

The first line has an integer $n$: the number of queries.

The following $n$ lines describe the queries. The format of each line is either "1 $a$ $b$ $l$ $r$" or "2 $x$".

# Output

Print the answer for each query of type 2. If no line is active, print `NO`.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $-10^9 \le a,b \le 10^9$
* $0 \le x \le 10^5$
* $0 \le l \le r \le 10^5$

# Example

Input:

```cpp
6
1 1 2 1 3
2 3
2 4
1 0 4 1 5
2 3
2 4
```

Output:

```cpp
5
NO
5
4
```