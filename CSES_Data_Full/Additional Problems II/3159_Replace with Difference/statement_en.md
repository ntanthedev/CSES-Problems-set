# 3159 - Replace with Difference

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers. You will perform $n-1$ operations on the array.

In one operation, you will choose two numbers $a$ and $b$ from the array, delete both of them from the array and add $|a - b|$ into the array.

Your task is to find a sequence of operations such that the last number remaining in the array is $0$.

# Input

The first line has an integer $n$: the length of the array.

The next line has $n$ integers $x\_1, x\_2,\dots, x\_n$: the contents of the array.

# Output

Print $n-1$ lines each containing two integers $a$ and $b$: the numbers chosen in the operations. You can print any valid solution.

If no solution exists, print only $-1$.

# Constraints

* $2 \le n \le 1000$
* $1 \le x\_i \le 1000$

# Example

Input:

```cpp
5
2 7 4 12 1
```

Output:

```cpp
2 12
7 10
4 1
3 3
```

*Explanation*: The array changes as follows:

* $[2, 7, 4, 12, 1] \rightarrow$ remove $2$ and $12$, add $10$
* $[7, 4, 1, 10] \rightarrow$ remove $7$ and $10$, add $3$
* $[4, 1, 3] \rightarrow$ remove $4$ and $1$, add $3$
* $[3, 3] \rightarrow$ remove $3$ and $3$, add $0$
* $[0]$: the final array