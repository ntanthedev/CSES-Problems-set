# 3163 - Range Interval Queries (Truy vấn Khoảng Trên Đoạn)

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng $x$ gồm $n$ số nguyên, nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: có bao nhiêu chỉ số $i$ thỏa mãn $a \le i \le b$ và $c \le x\_i \le d$?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng phần tử và số truy vấn.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các giá trị của mảng.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa bốn số nguyên $a$, $b$, $c$ và $d$: có bao nhiêu chỉ số $i$ thỏa mãn $a \le i \le b$ và $c \le x\_i \le d$?

# Kết quả

In ra kết quả của mỗi truy vấn.

# Giới hạn

* $1 \le n,q \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$
* $1 \le a \le b \le n$
* $1 \le c \le d \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8 4
3 2 4 5 1 1 5 3
2 4 2 4
5 6 2 9
1 8 1 5
3 3 4 4
```

Kết quả:

```cpp
2
0
8
1
```
