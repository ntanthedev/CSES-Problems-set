# 1097 - Removal Game

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a list of $n$ numbers and two players who move alternately. On each move, a player removes either the first or last number from the list, and their score increases by that number. Both players try to maximize their scores.

What is the maximum possible score for the first player when both players play optimally?

# Input

The first input line contains an integer $n$: the size of the list.

The next line has $n$ integers $x\_1,x\_2,\ldots,x\_n$: the contents of the list.

# Output

Print the maximum possible score for the first player.

# Constraints

* $1 \le n \le 5000$
* $-10^9 \le x\_i \le 10^9$

# Example

Input:

```cpp
4
4 5 1 3
```

Output:

```cpp
8
```