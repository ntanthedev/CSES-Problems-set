# 3216 - Bouncing Ball Cycle

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a ball at the top-left corner of an $n \times m$ grid. The rows of the grid are numbered $1,2,\dots,n$, and the columns are numbered $1,2,\dots,m$.

The ball is initially moving diagonally away from the top-left corner. At every step, it moves one cell. Whenever the ball hits the border of the grid, it changes its direction.

After how many steps has the ball reached its initial location again? What is the number of distinct cells it has visited?

# Input

The first line has an integer $t$: the number of tests.

After this, there are $t$ lines. Each line has two integers $n$, $m$: the size of the grid.

# Output

For each test, print two integers: the number of steps and the number of visited cells.

# Constraints

* $1 \le t \le 1000$
* $2 \le n,m \le 10^9$

# Example

Input:

```cpp
4
3 4
2 2
19 18
42 1337
```

Output:

```cpp
12 6
2 2
612 171
109552 28077
```