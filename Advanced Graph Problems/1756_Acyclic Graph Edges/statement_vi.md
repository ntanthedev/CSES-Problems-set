# 1756 - Đồ Thị Vô Hướng Định Hướng Phi Chu Trình

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị vô hướng, nhiệm vụ của bạn là chọn một hướng cho mỗi cạnh sao cho đồ thị có hướng thu được là phi chu trình (không có chu trình).

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và cạnh. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$ phân biệt: có một cạnh giữa đỉnh $a$ và $b$.

# Kết quả

In $m$ dòng mô tả hướng của các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh từ đỉnh $a$ đến đỉnh $b$. Bạn có thể in ra bất kỳ lời giải hợp lệ nào.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
3 3
1 2
2 3
3 1
```

Kết quả:

```cpp
1 2
3 2
3 1
```
