# 3358 - Split into Two Paths

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an acyclic directed graph with $n$ nodes and $m$ edges.

Determine whether two paths can be formed in the graph such that each node of the graph appears in exactly one of the paths. Note that all edges of the graph do not need to appear in the paths.

# Input

The first line has two integers $n$ and $m$: the number of nodes and the number of edges. The nodes are numbered $1, 2, \dots, n$.

After this, there are $m$ lines which describe the edges.
Each line has two integers $a$ and $b$: there is an edge in the graph from node $a$ to node $b$.

# Output

First print the line `YES` if the paths can be formed, or `NO` otherwise.

If the paths can be formed, print them on the following two lines.

At the beginning of both lines, print the amount of nodes in the path and then the nodes of the path in order. There must be an edge in the graph between subsequent nodes. One of the paths may contain zero nodes.

If there exist multiple solutions, you can print any solution.

# Constraints

* $2 \le n \le 2\cdot10^5$
* $0 \le m \le 5\cdot 10^5$

# Example 1

Input:

```cpp
5 4
1 2
1 4
3 4
4 5
```

Output:

```cpp
YES
2 1 2
3 3 4 5
```

# Example 2

Input:

```cpp
5 4
1 2
1 3
1 4
1 5
```

Output:

```cpp
NO
```