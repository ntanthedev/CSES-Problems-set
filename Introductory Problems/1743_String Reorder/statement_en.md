# 1743 - String Reorder

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Your task is to reorder the characters of a string so that no two adjacent characters are the same. What is the lexicographically minimal such string?

# Input

The only line has a string of length $n$ consisting of characters A–Z.

# Output

Print the lexicographically minimal reordered string where no two adjacent characters are the same. If it is not possible to create such a string, print $-1$.

# Constraints

* $1 \le n \le 10^6$

# Example

Input:

```cpp
HATTIVATTI
```

Output:

```cpp
AHATITITVT
```