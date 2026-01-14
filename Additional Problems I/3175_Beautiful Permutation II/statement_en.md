# 3175 - Beautiful Permutation II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A permutation of integers $1,2,\ldots,n$ is called *beautiful* if there are no adjacent elements whose difference is $1$.

Given $n$, construct the lexicographically minimal beautiful permutation if such a permutation exists.

# Input

The only line contains an integer $n$.

# Output

Print the lexicographically minimal beautiful permutation of integers $1,2,\ldots,n$. If there is no such permutation, print "NO SOLUTION".

# Constraints

* $1 \le n \le 10^6$

# Example 1

Input:

```cpp
5
```

Output:

```cpp
1 3 5 2 4
```

# Example 2

Input:

```cpp
3
```

Output:

```cpp
NO SOLUTION
```