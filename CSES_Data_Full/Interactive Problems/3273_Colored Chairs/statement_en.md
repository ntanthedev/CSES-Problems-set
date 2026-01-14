# 3273 - Colored Chairs

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ chairs arranged in a circle. Each chair is either red or blue. The chairs are numbered $1, 2,\dots, n$; chairs $i$ and $i+1$ are next to each other for all $1 \le i \le n$. Here chair $n+1$ refers to chair $1$.

Your task is to find two chairs that have the same color and are next to each other.

To do this, you can ask questions: you can choose a chair and you will be told the color of that chair.

# Interaction

This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading a single integer $n$: the number of chairs.

On your turn, you can print one of the following:

* "$?\ i$", where $1 \le i \le n$: ask the color of chair $i$. The grader will return `R` or `B` for red or blue.
* "$!\ i$": report that chairs $i$ and $i+1$ have the same color. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.

# Constraints

* $3 \le n \le 2 \cdot 10^5$, $n$ is odd
* you can ask at most $20$ questions of type $?$

# Example

```cpp
5
? 1
R
? 2
B
? 3
B
! 2
```