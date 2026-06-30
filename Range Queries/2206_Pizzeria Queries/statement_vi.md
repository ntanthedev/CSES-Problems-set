# 2206 - Truy vấn tiệm pizza

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ tòa nhà trên một con phố, được đánh số $1,2,\dots,n$. Mỗi tòa nhà có một tiệm pizza và một căn hộ.

Giá pizza ở tòa nhà $k$ là $p\_k$. Nếu bạn đặt pizza từ tòa nhà $a$ đến tòa nhà $b$, giá của nó (bao gồm giao hàng) là $p\_a+|a-b|$.

Nhiệm vụ của bạn là xử lý hai loại truy vấn:

1. Giá pizza $p\_k$ ở tòa nhà $k$ thay đổi thành $x$.
2. Bạn đang ở tòa nhà $k$ và muốn đặt một chiếc pizza. Giá tối thiểu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng tòa nhà và số lượng truy vấn.

Dòng thứ hai chứa $n$ số nguyên $p\_1,p\_2,\dots,p\_n$: giá pizza ban đầu ở mỗi tòa nhà.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Mỗi dòng có dạng "1 $k$ $x$" hoặc "2 $k$".

# Kết quả

In ra câu trả lời cho mỗi truy vấn loại 2.

# Giới hạn

* $1 \le n,q \le 2 \cdot 10^5$
* $1 \le p\_i, x \le 10^9$
* $1 \le k \le n$

# Ví dụ

Dữ liệu vào:

```cpp
6 3
8 6 4 5 7 5
2 2
1 5 1
2 2
```

Kết quả:

```cpp
5
4
```
