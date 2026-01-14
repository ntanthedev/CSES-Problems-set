# 3214 - Water Containers Queries

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are two water containers: container $A$ has volume $a$ and container $B$ has volume $b$. You want to measure $x$ units of water using the containers.

Initially both containers are empty. On each move, you can fill a container, empty a container or move water from a container to another container. When you move water, you must always fill or empty at least one container. After the moves, container $A$ must have $x$ units of water.

Your task is to efficiently check if it is possible to measure the water in several cases.

# Input

The first line has integer $n$: the number of tests.

After this, there are $n$ lines. Each line has three integers $a$, $b$ and $x$.

# Output

For each test, print YES if it is possible to measure the water and NO otherwise.

# Constraints

* $1 \le n \le 1000$
* $1 \le a, b, x \le 10^9$

# Example

Input:

```cpp
7
5 3 4
1 1 1
1 1 2
2 2 1
123 456 42
1000 999 123
1000 998 123
```

Output:

```cpp
YES
YES
NO
NO
YES
YES
NO
```