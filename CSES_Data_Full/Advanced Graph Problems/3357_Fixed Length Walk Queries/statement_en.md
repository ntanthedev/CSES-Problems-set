# 3357 - Fixed Length Walk Queries

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an undirected graph with $n$ nodes and $m$ edges. The graph is simple and connected.

You start at a specific node, and on each turn
you must move through an edge to another node.

Your task is to answer $q$ queries of the form: "is it possible to start at node $a$ and end up on node $b$ after exactly $x$ turns?"

# Input

The first line contains three integers $n$, $m$ and $q$:
the number of nodes, edges and queries. The nodes are numbered $1,2,\dots,n$.

After this, there are $m$ lines which describe the edges. Each line contains two integers $a$ and $b$: there is an edge between nodes $a$ and $b$.

Finally, there are $q$ lines, each describing a query.
Each line contains three integers $a$, $b$ and $x$.

# Output

For each query, print the answer (`YES` or `NO`) on its own line.

# Constraints

* $2 \le n \le 2500$
* $1 \le m \le 5000$
* $1 \le q \le 10^5$
* $0 \le x \le 10^9$

# Example

Input:

```cpp
4 5 6
1 2
2 3
1 3
2 4
3 4
1 2 2
1 4 1
1 4 5
2 2 1
2 2 2
3 4 8
```

Output:

```cpp
YES
NO
YES
NO
YES
YES
```

*Explanation*:

* In query 1, a possible route is $1 \rightarrow 3 \rightarrow 2$.
* In query 3, a possible route is $1 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 4$.
* In query 6, a possible route is $3 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 4$.