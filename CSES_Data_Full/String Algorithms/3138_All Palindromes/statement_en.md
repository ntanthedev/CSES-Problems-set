# 3138 - All Palindromes

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given a string, calculate for each position the length of the longest palindrome that ends at that position.

# Input

The only line contains a string of length $n$. Each character is one of a–z.

# Output

Print $n$ numbers: the length of each palindrome.

# Constraints

* $1 \le n \le 2 \cdot 10^5$

# Example

Input:

```cpp
ababbababaa
```

Output:

```cpp
1 1 3 3 2 4 6 8 5 5 2
```