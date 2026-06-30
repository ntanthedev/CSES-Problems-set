# 3218 - Truy vấn nước đi của Quân mã

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một quân mã trên bàn cờ vô hạn. Các hàng và cột được đánh số bắt đầu từ $1$.

Nhiệm vụ của bạn là xử lý hiệu quả các truy vấn dạng: khi quân mã bắt đầu ở vị trí $(x,y)$, cần ít nhất bao nhiêu nước đi để quân mã đến được góc trên bên trái?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng truy vấn.

Sau đó là $n$ dòng. Mỗi dòng chứa hai số nguyên $x$ và $y$: vị trí của quân mã.

# Kết quả

Với mỗi truy vấn, in ra số nước đi ít nhất.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le x, y \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
1 1
2 3
4 1
42 1337
```

Kết quả:

```cpp
0
1
3
669
```
