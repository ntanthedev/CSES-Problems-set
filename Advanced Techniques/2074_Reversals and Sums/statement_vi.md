# 2074 - Reversals and Sums

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, bạn phải xử lý các thao tác sau:

1. đảo ngược một đoạn con
2. tính tổng các giá trị trong một đoạn con

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước mảng và số lượng thao tác. Các phần tử mảng được đánh số $1,2,\dots,n$.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

Cuối cùng, có $m$ dòng mô tả các thao tác. Mỗi dòng chứa ba số nguyên $t$, $a$ và $b$. Nếu $t=1$, bạn cần đảo ngược đoạn con từ $a$ đến $b$. Nếu $t=2$, bạn cần tính tổng các giá trị từ $a$ đến $b$.

# Kết quả

In ra kết quả cho mỗi thao tác có $t=2$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le m \le 10^5$
* $0 \le x\_i \le 10^9$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
8 3
2 1 3 4 5 3 4 4
2 2 4
1 3 6
2 2 4
```

Kết quả:

```cpp
8
9
```
