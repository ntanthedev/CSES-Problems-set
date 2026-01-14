# 3305 - K th Highest Score

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There were $n$ coders from Finland and $n$ coders from Sweden in a programming contest. It turned out that after the contest, each coder had a distinct score.

Your task is to find the $k$-th highest score in the contest.

To do this, you can ask questions: you can choose a country (Finland or Sweden) and an integer $i$ and you will be told the $i$-th highest score for the chosen country.

# Interaction

This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading two integers $n$ and $k$.

On your turn, you can print one of the following:

* "$\mathrm{F}\ i$", where $1 \le i \le n$: ask the $i$-th highest score for Finland.
* "$\mathrm{S}\ i$", where $1 \le i \le n$: ask the $i$-th highest score for Sweden.
* "$!\ s$": report that the $k$-th highest score is $s$. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.

# Constraints

* $1 \le n \le 10^5$
* $1 \le k \le 2n$
* each score is between $1$ and $10^9$
* you can ask at most $100$ queries of the first two types in total

# Example

```cpp
3 1
F 1
9
S 1
8
! 9
```

*Explanation*: The scores for Finland are $[9, 4, 3]$ and the scores for Sweden are $[8, 6, 1]$. Since $k = 1$, the task is to find the highest score overall, which in this case is $9$.