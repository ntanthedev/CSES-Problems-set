# 3426 - Trượt Cửa Sổ XOR

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là tính phép XOR bit của từng cửa sổ gồm $k$ phần tử, từ trái sang phải.

Trong bài toán này, dữ liệu đầu vào lớn và được tạo ra bằng một bộ sinh.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số lượng phần tử và kích thước cửa sổ.

Dòng tiếp theo chứa bốn số nguyên $x$, $a$, $b$ và $c$: các tham số của bộ sinh. Dữ liệu được sinh như sau:

* $x\_1=x$
* $x\_i=(ax\_{i-1}+b) \bmod c$ với $i=2,3,\dots,n$

# Kết quả

In ra xor của tất cả các giá trị XOR của các cửa sổ.

# Giới hạn

* $1 \le k \le n \le 10^7$
* $0 \le x, a, b \le 10^9$
* $1 \le c \le 10^9$

# Ví dụ

Input:

```cpp
8 5
3 7 1 11
```

Output:

```cpp
0
```

**Giải thích:** Mảng đầu vào là $[3,0,1,8,2,4,7,6]$. Các cửa sổ là $[3,0,1,8,2]$, $[0,1,8,2,4]$, $[1,8,2,4,7]$ và $[8,2,4,7,6]$, và giá trị XOR của chúng lần lượt là $8$, $15$, $8$ và $15$. Do đó, đáp án là $8 \oplus 15 \oplus 8 \oplus 15 = 0$.
