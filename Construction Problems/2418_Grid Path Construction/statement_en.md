# 2418 - Grid Path Construction

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an $n \times m$ grid and two squares $a=(y\_1,x\_1)$ and $b=(y\_2,x\_2)$, create a path from $a$ to $b$ that visits each square exactly once.

For example, here is a path from $a=(1,3)$ to $b=(3,6)$ in a $4 \times 7$ grid:
![](944079e41a17eca6debb54a7d4da8f9124232206a1d80256432e8a2715c00055)

# Input

The first input line has an integer $t$: the number of tests.

After this, there are $t$ lines that describe the tests. Each line has six integers $n$, $m$, $y\_1$, $x\_1$, $y\_2$ and $x\_2$.

In all tests $1 \le y\_1,y\_2 \le n$ and $1 \le x\_1,x\_2 \le m$. In addition, $y\_1 \neq y\_2$ or $x\_1 \neq x\_2$.

# Output

Print YES, if it is possible to construct a path, and NO otherwise.

If there is a path, also print its description which consists of characters `U` (up), `D` (down), `L` (left) and `R` (right). If there are several paths, you can print any of them.

# Constraints

* $1 \le t \le 100$
* $1 \le n \le 50$
* $1 \le m \le 50$

# Example

Input:

```cpp
5
1 3 1 1 1 3
1 3 1 2 1 3
2 2 1 1 2 2
2 2 1 1 2 1
4 7 1 3 3 6
```

Output:

```cpp
YES
RR
NO
NO
YES
RDL
YES
RRRRDDDLLLLLLUUURDDRURDRURD
```