# 3139 - Hidden Permutation

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a hidden permutation $a\_1, a\_2,\dots, a\_n$ of integers $1, 2,\dots, n$. Your task is to find this permutation.

To do this, you can ask questions: you can choose two indices $i$ and $j$ and you will be told if $a\_i < a\_j$.

# Interaction

This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading a single integer $n$: the length of the permutation.

On your turn, you can print one of the following:

* "$?\ i\ j$", where $1 \le i, j \le n$: ask if $a\_i < a\_j$. The grader will return `YES` if $a\_i < a\_j$ and `NO` otherwise.
* "$!\ a\_1\ a\_2 \dots a\_n$": report that the hidden permutation is $a\_1, a\_2,\dots, a\_n$. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.

# Constraints

* $1 \le n \le 1000$
* you can ask at most $10^4$ questions of type $?$

# Example

```cpp
3
? 3 2
NO
? 3 1
YES
! 3 1 2
```

Explanation: The hidden permutation is $[3, 1, 2]$. The first question asks if $a\_3 < a\_2$ which is false, so the answer is `NO`. The second question asks if $a\_3 < a\_1$ which is true, so the answer is `YES`.