# 3140 - Inversion Sorting

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a hidden permutation $a\_1, a\_2,\dots, a\_n$ of integers $1, 2,\dots, n$. Your task is to sort the permutation by reversing subarrays.

On each turn, you can reverse a subarray of the permutation. After that, you will be reported the number of inversions in the permutation. If the number of inversions is $0$ (i.e., the permutation is sorted), you win.

# Interaction

This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading a single integer $n$: the length of the permutation.

On your turn, print two integers $i$ and $j$: reverse the subarray between indices $i$ and $j$.

After this, the next input line has a single integer: the number of inversions after the operation. If the number is $0$, you win and your program must terminate after this.

# Constraints

* $1\leq n\leq 1000$
* you can make at most $4n$ operations

# Example

```cpp
3
1 2
1
2 3
0
```

*Explanation*: Here the initial permutation is $[3,1,2]$. After the first operation the permutation is $[1,3,2]$ and the number of inversions is $1$. After the second operation the permutation is $[1,2,3]$ and the number of inversions is $0$.