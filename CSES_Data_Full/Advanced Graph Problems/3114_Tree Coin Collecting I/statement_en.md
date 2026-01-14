# 3114 - Tree Coin Collecting I

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given a tree with $n$ nodes. Some nodes contain a coin.

Your task is to answer $q$ queries of the form: what is the shortest length of a path from node $a$ to node $b$ that visits a node with a coin?

# Input

The first line contains two integers $n$ and $q$: the number of nodes and queries. The nodes are numbered $1, 2, \dots, n$.

The second line contains $n$ integers $c\_1, c\_2,\dots, c\_n$. If $c\_i = 1$, node $i$ has a coin. If $c\_i = 0$, node $i$ doesn't have a coin. You can assume at least one node has a coin.

Then there are $n-1$ lines describing the edges. Each line contains two integers $a$ and $b$: there is an edge between nodes $a$ and $b$.

Finally, there are $q$ lines describing the queries. Each line contains two integers $a$ and $b$: the start and end nodes.

# Output

Print $q$ integers: the answers to the queries.

# Constraints

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le a, b \le n$

# Example

Input:

```cpp
5 4
1 0 0 1 0
2 4
2 3
1 3
3 5
1 5
3 2
4 4
5 5
```

Output:

```cpp
2
3
0
4
```