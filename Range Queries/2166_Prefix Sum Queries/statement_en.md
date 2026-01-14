# 2166 - Prefix Sum Queries

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an array of $n$ integers, your task is to process $q$ queries of the following types:

1. update the value at position $k$ to $u$
2. what is the maximum prefix sum in range $[a,b]$?

Empty prefixes (with sum 0) are allowed.

# Input

The first input line has two integers $n$ and $q$: the number of values and queries.

The second line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the array values.

Finally, there are $q$ lines describing the queries. Each line has three integers: either "$1$ $k$ $u$" or "$2$ $a$ $b$".

# Output

Print the result of each query of type 2.

# Constraints

* $1 \le n,q \le 2 \cdot 10^5$
* $-10^9 \le x\_i, u \le 10^9$
* $1 \le k \le n$
* $1 \le a \le b \le n$

# Example

Input:

```cpp
8 4
1 2 -1 3 1 -5 1 4
2 2 6
1 4 -2
2 2 6
2 3 4
```

Output:

```cpp
5
2
0
```