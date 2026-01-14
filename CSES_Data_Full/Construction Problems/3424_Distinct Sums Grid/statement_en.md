# 3424 - Distinct Sums Grid

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Create an $n \times n$ grid that fulfills the following requirements:

1. Each integer $1 \dots n$ appears $n$ times in the grid.
2. If we create a set that consists of all sums in rows and columns, there are $2n$ distinct values.

# Input

The only line has an integer $n$.

# Output

Print a grid that fulfills the requirements. You can print any valid solution. If there are no solutions, print `IMPOSSIBLE`.

# Constraints

* $1 \le n \le 1000$

# Example

Input:

```cpp
5
```

Output:

```cpp
2 3 1 1 1 
1 5 5 3 3 
2 3 5 2 4 
5 4 5 4 1 
2 3 4 4 2
```

*Explanation*: Each integer $1 \dots 5$ appears $5$ times, and the sums in rows and columns are $\{8,11,12,14,15,16,17,18,19,20\}$.