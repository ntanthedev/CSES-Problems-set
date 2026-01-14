# 3215 - Bouncing Ball Steps

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a ball at the top-left corner of an $n \times m$ grid. The rows of the grid are numbered $1,2,\dots,n$, and the columns are numbered $1,2,\dots,m$.

The ball is initially moving diagonally away from the top-left corner. At every step, it moves one cell. Whenever the ball hits the border of the grid, it changes its direction.

What is the location of the ball after $k$ steps and how many times has it changed direction?

# Input

The first line has an integer $t$: the number of tests.

After this, there are $t$ lines. Each line has three integers $n$, $m$ and $k$: the size of the grid and the number of steps.

# Output

For each test, print three integers: the location of the ball and the number of direction changes.

# Constraints

* $1 \le t \le 1000$
* $2 \le n,m \le 10^9$
* $0 \le k \le 10^{18}$

# Example

Input:

```cpp
6
3 4 0
3 4 1
3 4 2
3 4 3
3 4 4
42 1337 123456789
```

Output:

```cpp
1 1 0
2 2 0
3 3 1
2 4 2
1 3 3
34 300 3101295
```