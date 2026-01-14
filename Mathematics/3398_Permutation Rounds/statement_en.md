# 3398 - Permutation Rounds

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a sorted array $[1,2,\dots,n]$ and a permutation $p\_1,p\_2,\dots,p\_n$. On each round, all elements move according to the permutation: the element at position $i$ moves to position $p\_i$.

After how many rounds is the array sorted again for the first time?

# Input

The first line has an integer $n$.

The next line contains $n$ integers $p\_1,p\_2,\dots,p\_n$.

# Output

Print the number of rounds modulo $10^9+7$.

# Constraints

* $1 \le n \le 2 \cdot 10^5$

# Example

Input:

```cpp
8
5 3 2 6 4 1 8 7
```

Output:

```cpp
4
```

*Explanation*: The array changes as follows after the rounds:

* Round 1: $[6,3,2,5,1,4,8,7]$
* Round 2: $[4,2,3,1,6,5,7,8]$
* Round 3: $[5,3,2,6,4,1,8,7]$
* Round 4: $[1,2,3,4,5,6,7,8]$