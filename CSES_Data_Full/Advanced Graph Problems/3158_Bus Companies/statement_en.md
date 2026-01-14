# 3158 - Bus Companies

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ cities and $m$ bus companies. Each bus company operates in specific cities and sells tickets for a specific price. Buying a ticket from a bus company allows you to travel between any two cities that the company operates in.

Determine the cost of the cheapest route from Syrjälä to every city.

# Input

The first line has two integers $n$ and $m$: the number of cities and bus companies. The cities are numbered $1,2,\dots,n$, and city $1$ is Syrjälä.

The next line has $m$ integers $c\_1, c\_2,\dots, c\_m$: the ticket costs for each bus company.

After that, there are $m$ pairs of lines describing the cities for each bus company.

The first line of each pair has a single integer $k$: the number of cities the bus company operates in.

The second line of each pair has $k$ distinct integers $a\_1, a\_2,\dots, a\_k$: the cities the bus company operates in.

You can assume that it is possible to travel from Syrjälä to all other cities.

# Output

Print $n$ integers: the cheapest route costs from Syrjälä to cities $1,2,\dots, n$.

# Constraints

* $1 \le n, m \le 10^5$
* $1 \le c \le 10^9$
* $2 \le k \le n$
* $1 \le a \le n$
* the sum of all $k$ is at most $2 \cdot 10^5$

# Example

Input:

```cpp
5 3
4 3 2
3
1 4 3
2
5 1
4
2 3 4 5
```

Output:

```cpp
0 5 4 4 3
```