# 2214 - Inverse Inversions

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Your task is to create a permutation of numbers $1,2,\dots,n$ that has exactly $k$ inversions.

An inversion is a pair $(a,b)$ where $a<b$ and $p\_a>p\_b$ where $p\_i$ denotes the number at position $i$ in the permutation.

# Input

The only input line has two integers $n$ and $k$.

# Output

Print a line that contains the permutation. You can print any valid solution.

# Constraints

* $1 \le n \le 10^6$
* $0 \le k \le \frac{n(n-1)}{2}$

# Example

Input:

```cpp
5 4
```

Output:

```cpp
1 5 2 4 3
```