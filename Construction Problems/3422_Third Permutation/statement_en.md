# 3422 - Third Permutation

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given two permutations $a$ and $b$ such that $a\_i \neq b\_i$ in every position. Create a third permutation $c$ such that $a\_i \neq c\_i$ and $b\_i \neq c\_i$ in every position.

# Input

The first line has an integer $n$: the permutation size.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$.

The third line has $n$ integers $b\_1,b\_2,\dots,b\_n$.

# Output

Print $n$ integers $c\_1,c\_2,\dots,c\_n$. You can print any valid solution. If there are no solutions, print `IMPOSSIBLE`.

# Constraints

* $2 \le n \le 10^5$

# Example

Input:

```cpp
5
1 3 2 5 4
4 1 3 2 5
```

Output:

```cpp
3 2 5 4 1
```