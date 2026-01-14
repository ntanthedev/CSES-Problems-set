# 1074 - Stick Lengths

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ sticks with some lengths. Your task is to modify the sticks so that each stick has the same length.

You can either lengthen and shorten each stick. Both operations cost $x$ where $x$ is the difference between the new and original length.

What is the minimum total cost?

# Input

The first input line contains an integer $n$: the number of sticks.

Then there are $n$ integers: $p\_1,p\_2,\ldots,p\_n$: the lengths of the sticks.

# Output

Print one integer: the minimum total cost.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le p\_i \le 10^9$

# Example

Input:

```cpp
5
2 3 1 5 2
```

Output:

```cpp
5
```