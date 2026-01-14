# 3409 - MST Edge Cost

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an undirected weighted graph, determine for each edge the minimum spanning tree cost if the edge must be included in the spanning tree.

# Input

The first line has two integers $n$ and $m$: the number of nodes and edges. The nodes are numbered $1,2,\dots,n$.

The following $m$ lines describe the edges. Each line has three integers $a$, $b$, $w$: there is an edge between nodes $a$ and $b$ with weight $w$.

You can assume that the graph is connected and simple and each edge appears at most once in the graph.

# Output

For each edge in the input order, print the minimum spanning tree cost when the edge is included.

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le w \le 10^9$

# Example

Input:

```cpp
5 6
1 2 4
1 3 2
2 4 2
3 4 1
3 5 4
4 5 3
```

Output:

```cpp
10
8
8
8
9
8
```