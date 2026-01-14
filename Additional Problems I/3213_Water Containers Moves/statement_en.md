# 3213 - Water Containers Moves

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are two water containers: container $A$ has volume $a$ and container $B$ has volume $b$. Your want to measure $x$ units of water using the containers.

Initially both containers are empty. On each move, you can fill a container, empty a container or move water from a container to another container. When you move water, you must always fill or empty at least one container. After the moves, container $A$ must have $x$ units of water.

Find a sequence of moves where the total amount of moved water is minimum or state that it is impossible to measure the water.

# Input

The only line has three integers $a$, $b$ and $x$.

# Output

First print two integers $n$ and $m$: the number of moves and the total amount of water moved. After that print a sequence of $n$ moves. Each move must move at least one unit of water and be one of the following:

* `FILL A`: fill container $A$
* `FILL B`: fill container $B$
* `EMPTY A`: empty container $A$
* `EMPTY B`: empty container $B$
* `MOVE A B`: move water from container $A$ to container $B$
* `MOVE B A`: move water from container $B$ to container $A$

If it is not possible to measure the water, only print $-1$.

# Constraints

* $1 \le a, b, x \le 1000$

# Example

Input:

```cpp
5 3 4
```

Output:

```cpp
6 19
FILL A
MOVE A B
EMPTY B
MOVE A B
FILL A
MOVE A B
```