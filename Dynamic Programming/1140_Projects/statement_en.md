# 1140 - Projects

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ projects you can attend. For each project, you know its starting and ending days and the amount of money you would get as reward. You can only attend one project during a day.

What is the maximum amount of money you can earn?

# Input

The first input line contains an integer $n$: the number of projects.

After this, there are $n$ lines. Each such line has three integers $a\_i$, $b\_i$, and $p\_i$: the starting day, the ending day, and the reward.

# Output

Print one integer: the maximum amount of money you can earn.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a\_i \le b\_i \le 10^9$
* $1 \le p\_i \le 10^9$

# Example

Input:

```cpp
4
2 4 4
3 6 6
6 8 2
5 7 3
```

Output:

```cpp
7
```