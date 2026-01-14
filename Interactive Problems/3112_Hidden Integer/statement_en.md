# 3112 - Hidden Integer

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a hidden integer $x$. Your task is to find the value of $x$.

To do this, you can ask questions: you can choose an integer $y$ and you will be told if $y < x$.

# Interaction

This is an interactive problem. Your code will interact with the grader using standard input and output. You can start asking questions right away.

On your turn, you can print one of the following:

* "$?\ y$", where $1 \le y \le 10^9$: ask if $y < x$. The grader will return `YES` if $y < x$ and `NO` otherwise.
* "$!\ x$": report that the hidden integer is $x$. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.

# Constraints

* $1 \le x \le 10^9$
* you can ask at most $30$ questions of type $?$

# Example

```cpp
? 3
YES
? 6
YES
? 7
NO
! 7
```