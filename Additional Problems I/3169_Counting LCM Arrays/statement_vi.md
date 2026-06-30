# 3169 - Đếm mảng LCM

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho hai số nguyên $n$ và $k$, nhiệm vụ của bạn là đếm số lượng mảng $a\_1, a\_2,\dots, a\_n$ gồm các số nguyên dương thỏa mãn $\operatorname{lcm}(a\_i, a\_{i+1}) = k$ với mọi $1 \le i < n$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

$t$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $n$ và $k$: độ dài của mảng và giá trị lcm.

# Kết quả

In ra $t$ số nguyên: kết quả của mỗi bộ test modulo $10^9 + 7$.

# Giới hạn

* $1 \le t \le 1000$
* $2 \le n \le 10^9$
* $1 \le k \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3
3 4
4 6
1337 42
```

Kết quả:

```cpp
11
64
602746233
```

*Giải thích*: Các mảng cho bộ test đầu tiên là $[1, 4, 1]$, $[1, 4, 2]$, $[1, 4, 4]$, $[2, 4, 1]$, $[2, 4, 2]$, $[2, 4, 4]$, $[4, 1, 4]$, $[4, 2, 4]$, $[4, 4, 1]$, $[4, 4, 2]$ và $[4, 4, 4]$.
