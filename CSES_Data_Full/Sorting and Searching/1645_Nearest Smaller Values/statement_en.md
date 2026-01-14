# 1645 - Nearest Smaller Values

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an array of $n$ integers, your task is to find for each array position the nearest position to its left having a smaller value.

# Input

The first input line has an integer $n$: the size of the array.

The second line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the array values.

# Output

Print $n$ integers: for each array position the nearest position with a smaller value. If there is no such position, print $0$.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
8
2 5 1 4 8 3 2 5
```

Output:

```cpp
0 1 0 3 4 3 3 7
```