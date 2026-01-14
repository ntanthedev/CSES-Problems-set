# 1697 - Chess Tournament

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There will be a chess tournament of $n$ players. Each player has announced the number of games they want to play.

Each pair of players can play at most one game. Your task is to determine which games will be played so that everybody will be happy.

# Input

The first input line has an integer $n$: the number of players. The players are numbered $1,2,\dots,n$.

The next line has $n$ integers $x\_1,x\_2,\dots,x\_n$: for each player, the number of games they want to play.

# Output

First print an integer $k$: the number of games. Then, print $k$ lines describing the games. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

# Constraints

* $1 \le n \le 10^5$
* $\sum\_{i=1}^{n} x\_i \le 2 \cdot 10^5$

# Example

Input:

```cpp
5
1 3 2 0 2
```

Output:

```cpp
4
1 2
2 3
2 5
3 5
```