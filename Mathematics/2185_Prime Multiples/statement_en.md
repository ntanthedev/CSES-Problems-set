# 2185 - Prime Multiples

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given $k$ distinct prime numbers $a\_1,a\_2,\ldots,a\_k$ and an integer $n$.

Your task is to calculate how many of the first $n$ positive integers are divisible by at least one of the given prime numbers.

# Input

The first input line has two integers $n$ and $k$.

The second line has $k$ prime numbers $a\_1,a\_2,\ldots,a\_k$.

# Output

Print one integer: the number integers within the interval $1,2,\ldots,n$ that are divisible by at least one of the prime numbers.

# Constraints

* $1 \le n \le 10^{18}$
* $1 \le k \le 20$
* $2 \le a\_i \le n$

# Example

Input:

```cpp
20 2
2 5
```

Output:

```cpp
12
```

Explanation: the $12$ numbers are $2,4,5,6,8,10,12,14,15,16,18,20$.