# 2084 - Monster Game I

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are playing a game that consists of $n$ levels. Each level has a monster. On levels $1,2,\dots,n-1$, you can either kill or escape the monster. However, on level $n$ you must kill the final monster to win the game.

Killing a monster takes $sf$ time where $s$ is the monster's strength and $f$ is your skill factor (lower skill factor is better). After killing a monster, you get a new skill factor. What is the minimum total time in which you can win the game?

# Input

The first input line has two integers $n$ and $x$: the number of levels and your initial skill factor.

The second line has $n$ integers $s\_1,s\_2,\dots,s\_n$: each monster's strength.

The third line has $n$ integers $f\_1,f\_2,\dots,f\_n$: your new skill factor after killing a monster.

# Output

Print one integer: the minimum total time to win the game.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x \le 10^6$
* $1 \le s\_1 \le s\_2 \le \dots \le s\_n \le 10^6$
* $x \ge f\_1 \ge f\_2 \ge \dots \ge f\_n \ge 1$

# Example

Input:

```cpp
5 100
20 30 30 50 90
90 60 20 20 10
```

Output:

```cpp
4800
```

Explanation: The best way to play is to kill the third and fifth monster.