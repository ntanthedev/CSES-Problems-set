# 1728 - Inversion Probability

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

An array has $n$ integers $x\_1,x\_2,\dots,x\_n$, and each of them has been randomly chosen between $1$ and $r\_i$. An inversion is a pair $(a,b)$ where $a<b$ and $x\_a>x\_b$.

What is the expected number of inversions in the array?

# Input

The first input line contains an integer $n$: the size of the array.

The second line contains $n$ integers $r\_1,r\_2,\dots,r\_n$: the range of possible values for each array position.

# Output

Print the expected number of inversions rounded to six decimal places (rounding half to even).

# Constraints

* $1 \le n \le 100$
* $1 \le r\_i \le 100$

# Example

Input:

```cpp
3
5 2 7
```

Output:

```cpp
1.057143
```