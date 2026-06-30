# 3425 - Tập con cùng Tổng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một tập hợp gồm $n$ số nguyên dương, nhiệm vụ của bạn là chọn hai tập con rời nhau của các phần tử có cùng tổng.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước của tập hợp.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các phần tử của tập hợp.

# Kết quả

Với mỗi tập con, in ra kích thước của tập con và sau đó là các phần tử của nó. Bạn có thể in ra bất kỳ nghiệm nào hợp lệ. Nếu không có nghiệm, in ra `IMPOSSIBLE`.

# Giới hạn

* $3 \le n \le 40$
* $\sum\_{i=1}^{n} x\_i \le 2^{n}-2$

# Ví dụ

Dữ liệu vào:

```cpp
6
1 2 3 5 7 8
```

Kết quả:

```cpp
2
2 3
1
5
```

*Giải thích*: Tập con thứ nhất là $\{2,3\}$ và tập con thứ hai là $\{5\}$.
