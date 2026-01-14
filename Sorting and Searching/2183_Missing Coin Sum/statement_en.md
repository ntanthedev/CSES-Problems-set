# 2183 - Missing Coin Sum

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You have $n$ coins with positive integer values. What is the smallest sum you cannot create using a subset of the coins?

# Input

The first line has an integer $n$: the number of coins.

The second line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the value of each coin.

# Output

Print one integer: the smallest coin sum.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
5
2 9 1 2 7
```

Output:

```cpp
6
```