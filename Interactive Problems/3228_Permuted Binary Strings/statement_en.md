# 3228 - Permuted Binary Strings

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a hidden permutation $a\_1, a\_2,\dots, a\_n$ of integers $1, 2,\dots, n$. Your task is to find this permutation.

To do this, you can ask questions: you can choose a binary string $b\_1b\_2\dots b\_n$ and you will receive the binary string $b\_{a\_1}b\_{a\_2}\dots b\_{a\_n}$.

# Interaction

This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading a single integer $n$: the length of the permutation.

On your turn, you can print one of the following:

* "$?\ b\_1b\_2\dots b\_n$", where $b\_i\in\{0, 1\}$: The grader will return the binary string $b\_{a\_1}b\_{a\_2}\dots b\_{a\_n}$.
* "$!\ a\_1\ a\_2 \dots a\_n$": report that the hidden permutation is $a\_1, a\_2,\dots, a\_n$. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.

# Constraints

* $1 \le n \le 1000$
* you can ask at most $10$ questions of type $?$

# Example

```cpp
3
? 100
100
? 010
001
? 001
010
! 1 3 2
```

*Explanation*: The hidden permutation is $[1, 3, 2]$. In the first question $b\_1b\_2b\_3 = 100$ and the grader returns $b\_{a\_1}b\_{a\_2}b\_{a\_3} = b\_1b\_3b\_2 = 100$. In the second question $b\_1b\_2b\_3 = 010$ and the grader returns $b\_1b\_3b\_2 = 001$.