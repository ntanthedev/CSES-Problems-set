# 3193 - Square Subsets

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an array of $n$ integers, count the number of subsets whose elements' product is a square number.

Also count the empty subset with product equal to one.

# Input

The first line has an integer $n$: the size of the array.

The next line has $n$ integers $x\_1, x\_2,\dots, x\_n$: the contents of the array.

# Output

Print one integer: the answer to the problem modulo $10^9 + 7$.

# Constraints

* $1 \le n \le 5000$
* $1 \le x\_i \le 5000$

# Example

Input:

```cpp
4
2 2 3 6
```

Output:

```cpp
4
```