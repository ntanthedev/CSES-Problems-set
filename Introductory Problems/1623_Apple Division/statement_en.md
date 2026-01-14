# 1623 - Apple Division

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ apples with known weights. Your task is to divide the apples into two groups so that the difference between the weights of the groups is minimal.

# Input

The first input line has an integer $n$: the number of apples.

The next line has $n$ integers $p\_1,p\_2,\dots,p\_n$: the weight of each apple.

# Output

Print one integer: the minimum difference between the weights of the groups.

# Constraints

* $1 \le n \le 20$
* $1 \le p\_i \le 10^9$

# Example

Input:

```cpp
5
3 2 7 4 1
```

Output:

```cpp
1
```

Explanation: Group 1 has weights 2, 3 and 4 (total weight 9), and group 2 has weights 1 and 7 (total weight 8).