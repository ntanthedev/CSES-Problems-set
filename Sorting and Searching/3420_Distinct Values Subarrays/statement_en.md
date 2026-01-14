# 3420 - Distinct Values Subarrays

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an array of $n$ integers, count the number of subarrays where each element is distinct.

# Input

The first line has an integer $n$: the array size.

The second line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the array contents.

# Output

Print the number of subarrays with distinct elements.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Example

Input:

```cpp
4
1 2 1 3
```

Output:

```cpp
8
```

*Explanation*: The subarrays are $[1]$ (two times), $[2]$, $[3]$, $[1,2]$, $[1,3]$, $[2,1]$ and $[2,1,3]$.