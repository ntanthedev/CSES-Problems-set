# 3226 - Subarray Sum Queries II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers and $q$ queries. In each query, your task is to calculate the maximum subarray sum in the range $[a,b]$.

Empty subarrays (with sum $0$) are allowed.

# Input

The first line contains two integers $n$ and $q$: the number of elements and the number of queries.

Then there are $n$ integers $x\_1,x\_2,\ldots,x\_n$: the contents of the array.

Finally there are $q$ lines that describe the queries. Each line has two integers $a$ and $b$.

# Output

Print the answer for each query.

# Constraints

* $1 \le n, q\le 2 \cdot 10^5$
* $-10^9 \le x\_i \le 10^9$
* $1 \le a \le b \le n$

# Example

Input:

```cpp
8 4
2 5 1 -2 3 -1 -7 1
2 4
2 5
6 7
4 8
```

Output:

```cpp
6
7
0
3
```