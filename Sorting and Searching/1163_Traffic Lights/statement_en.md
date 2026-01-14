# 1163 - Traffic Lights

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a street of length $x$ whose positions are numbered $0,1,\ldots,x$. Initially there are no traffic lights, but $n$ sets of traffic lights are added to the street one after another.

Your task is to calculate the length of the longest passage without traffic lights after each addition.

# Input

The first input line contains two integers $x$ and $n$: the length of the street and the number of sets of traffic lights.

Then, the next line contains $n$ integers $p\_1,p\_2,\ldots,p\_n$: the position of each set of traffic lights. Each position is distinct.

# Output

Print the length of the longest passage without traffic lights after each addition.

# Constraints

* $1 \le x \le 10^9$
* $1 \le n \le 2 \cdot 10^5$
* $0 < p\_i < x$

# Example

Input:

```cpp
8 3
3 6 2
```

Output:

```cpp
5 3 3
```