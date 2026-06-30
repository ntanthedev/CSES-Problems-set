# 1707 - Chu Trình Nhỏ Nhất

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị vô hướng, nhiệm vụ của bạn là xác định *chu trình nhỏ nhất* của nó, tức là độ dài của chu trình ngắn nhất.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và cạnh. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh giữa đỉnh $a$ và $b$.

Bạn có thể giả định rằng có nhiều nhất một cạnh giữa hai đỉnh bất kỳ.

# Kết quả

In một số nguyên: chu trình nhỏ nhất của đồ thị. Nếu không có chu trình nào, in $-1$.

# Giới hạn

* $1 \le n \le 2500$
* $1 \le m \le 5000$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
1 2
1 3
2 4
2 5
3 4
4 5
```

Kết quả:

```cpp
3
```
