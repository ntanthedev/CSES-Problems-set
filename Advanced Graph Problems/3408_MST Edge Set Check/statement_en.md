# 3408 - MST Edge Set Check

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an undirected weighted graph and edge sets, determine for each set if the edges can be included in a minimum spanning tree.

# Input

The first line has three integers $n$, $m$ and $q$: the number of nodes, edges and edge sets. The nodes are numbered $1,2,\dots,n$.

The following $m$ lines describe the edges. Each line has three integers $a$, $b$, $w$: there is an edge between nodes $a$ and $b$ with weight $w$. The edges are numbered $1,2,\dots,m$ in the input order.

The following $2q$ lines describe the edge sets. For each set, the first line contains its size and the second line contains its edges. The total number of edges in all sets is at most $m$.

You can assume that the graph is connected and simple and each edge appears at most once in the graph.

# Output

For each edge set, print `YES` if the edges can be included in the minimum spanning tree and `NO` otherwise.

# Constraints

* $1 \le n \le 10^5$
* $1 \le m, q \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le w \le 10^9$

# Example

Input:

```cpp
5 6 4
1 2 4
1 3 2
2 4 2
3 4 1
3 5 3
4 5 3
3
2 3 4
1
1
2
2 6
2
5 6
```

Output:

```cpp
YES
NO
YES
NO
```