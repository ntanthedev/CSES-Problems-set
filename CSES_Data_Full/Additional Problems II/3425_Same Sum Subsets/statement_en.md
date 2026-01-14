# 3425 - Same Sum Subsets

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given a set of $n$ positive integers, your task is to choose two disjoint subsets of the elements that have the same sum.

# Input

The first line has an integer $n$: the set size.

The second line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the set elements.

# Output

For both subsets, first print the size of the subset and then its contents. You can print any valid solution. If there is no solution, print `IMPOSSIBLE`.

# Constraints

* $3 \le n \le 40$
* $\sum\_{i=1}^{n} x\_i \le 2^{n}-2$

# Example

Input:

```cpp
6
1 2 3 5 7 8
```

Output:

```cpp
2
2 3
1
5
```

*Explanation*: The first subset is $\{2,3\}$ and the second subset is $\{5\}$.