# 1631 - Reading Books

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ books, and Kotivalo and Justiina are going to read them all. For each book, you know the time it takes to read it.

They both read each book from beginning to end, and they cannot read a book at the same time. What is the minimum total time required?

# Input

The first input line has an integer $n$: the number of books.

The second line has $n$ integers $t\_1,t\_2,\dots,t\_n$: the time required to read each book.

# Output

Print one integer: the minimum total time.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le t\_i \le 10^9$

# Example

Input:

```cpp
3
2 8 3
```

Output:

```cpp
16
```