# 3154 - System of Linear Equations

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given $n\cdot(m+1)$ coefficients $a\_{i,j}$ and $b\_i$ which form the following $n$ linear equations:

* $a\_{1,1}x\_1 + a\_{1,2}x\_2 + \dots + a\_{1,m}x\_m = b\_1 \pmod {10^9 + 7}$
* $a\_{2,1}x\_1 + a\_{2,2}x\_2 + \dots + a\_{2,m}x\_m = b\_2 \pmod {10^9 + 7}$
* $\dots$
* $a\_{n,1}x\_1 + a\_{n,2}x\_2 + \dots + a\_{n,m}x\_m = b\_n \pmod {10^9 + 7}$

Your task is to find any $m$ integers $x\_1, x\_2, \dots, x\_m$ that satisfy the given equations.

# Input

The first line has two integers $n$ and $m$: the number of equations and variables.

The next $n$ lines each have $m+1$ integers $a\_{i,1}, a\_{i,2}, \dots, a\_{i,m}, b\_i$: the coefficients of the $i$-th equation.

# Output

Print $m$ integers $x\_1, x\_2,\dots, x\_m$: the values of the variables that satisfy the equations. The values must also satisfy $0 \le x\_i < 10^9 + 7$. You can print any valid solution. If no solution exists print only $-1$.

# Constraints

* $1 \le n, m \le 500$
* $0 \le a\_{i,j}, b\_i < 10^9 + 7$

# Example

Input:

```cpp
3 3
2 0 1 7
1 2 0 0
1 3 1 2
```

Output:

```cpp
2 1000000006 3
```