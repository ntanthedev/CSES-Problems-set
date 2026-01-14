# 3301 - Maximum Average Subarrays

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers. For each $i = 1, 2,\dots, n$, your task is to find the subarray ending at index $i$ with the largest average. If there are multiple subarrays with the largest average, you should find the longest one.

# Input

The first line has an integer $n$: the size of the array.

The next line has $n$ integers $x\_1, x\_2,\dots, x\_n$: the contents of the array.

# Output

Print $n$ integers: the length of the subarray ending at index $i$ with the largest average for each $i = 1, 2,\dots, n$.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^6$

# Example

Input:

```cpp
7
1 6 4 6 2 5 5
```

Output:

```cpp
1 1 2 1 4 1 2
```

*Explanation*: Consider $i = 5$. The averages of all subarrays ending at index $5$ are $\frac{1 + 6 + 4 + 6 + 2}{5} = 3.8$, $\frac{6 + 4 + 6 + 2}{4} = 4.5$, $\frac{4 + 6 + 2}{3} = 4$, $\frac{6 + 2}{2} = 4$ and $\frac{2}{1} = 2$. The largest average is $4.5$ and the length of the corresponding subarray is $4$.