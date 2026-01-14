# 2189 - Point Location Test

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a line that goes through the points $p\_1=(x\_1,y\_1)$ and $p\_2=(x\_2,y\_2)$. There is also a point $p\_3=(x\_3,y\_3)$.

Your task is to determine whether $p\_3$ is located on the left or right side of the line or if it touches the line when we are looking from $p\_1$ to $p\_2$.

# Input

The first input line has an integer $t$: the number of tests.

After this, there are $t$ lines that describe the tests. Each line has six integers: $x\_1$, $y\_1$, $x\_2$, $y\_2$, $x\_3$ and $y\_3$.

# Output

For each test, print "LEFT", "RIGHT" or "TOUCH".

# Constraints

* $1 \le t \le 10^5$
* $-10^9 \le x\_1, y\_1, x\_2, y\_2, x\_3, y\_3 \le 10^9$
* $x\_1 \neq x\_2$ or $y\_1 \neq y\_2$

# Example

Input:

```cpp
3
1 1 5 3 2 3
1 1 5 3 4 1
1 1 5 3 3 2
```

Output:

```cpp
LEFT
RIGHT
TOUCH
```