# 1628 - Meet in the Middle

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ numbers. In how many ways can you choose a subset of the numbers with sum $x$?

# Input

The first input line has two numbers $n$ and $x$: the array size and the required sum.

The second line has $n$ integers $t\_1,t\_2,\dots,t\_n$: the numbers in the array.

# Output

Print the number of ways you can create the sum $x$.

# Constraints

* $1 \le n \le 40$
* $1 \le x \le 10^9$
* $1 \le t\_i \le 10^9$

# Example

Input:

```cpp
4 5
1 2 3 2
```

Output:

```cpp
3
```