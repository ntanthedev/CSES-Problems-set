# 3225 - Inverse Suffix Array

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given a suffix array of a string, your task is to reconstruct the string.

The suffix array of a string of length $n$ is a permutation of numbers $1,2,\dots,n$ that presents the lexicographical order of the suffixes.

# Input

The first line has an integer $n$: the length of the string.

The next line has $n$ integers: the suffix array.

# Output

Print a string that corresponds to the suffix array. The string must consist of characters a–z. If there are several possible strings, you can print any of them.

If no string corresponds to the suffix array, print $-1$.

# Constraints

* $1 \le n \le 10^5$

# Example

Input:

```cpp
7
4 1 3 5 6 7 2
```

Output:

```cpp
aybabtu
```