# 2133 - Kết Nối Động

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một đồ thị vô hướng gồm $n$ đỉnh và $m$ cạnh. Có hai loại sự kiện có thể xảy ra:

1. Một cạnh mới được tạo ra giữa hai đỉnh $a$ và $b$.
2. Một cạnh hiện có giữa hai đỉnh $a$ và $b$ bị xóa bỏ.

Nhiệm vụ của bạn là báo cáo số lượng thành phần liên thông sau mỗi sự kiện.

# Dữ liệu vào

Dòng đầu tiên gồm ba số nguyên $n$, $m$ và $k$: số lượng đỉnh, cạnh và sự kiện.

Sau đó là $m$ dòng mô tả các cạnh. Mỗi dòng gồm hai số nguyên $a$ và $b$: có một cạnh giữa hai đỉnh $a$ và $b$. Có tối đa một cạnh giữa bất kỳ cặp đỉnh nào.

Tiếp theo là $k$ dòng mô tả các sự kiện. Mỗi dòng có dạng "$t$ $a$ $b$" với $t$ là 1 (tạo cạnh mới) hoặc 2 (xóa cạnh). Một cạnh mới luôn được tạo ra giữa hai đỉnh chưa có cạnh nối giữa chúng, và chỉ các cạnh hiện có mới có thể bị xóa.

# Kết quả

In ra $k+1$ số nguyên: đầu tiên là số lượng thành phần liên thông trước sự kiện đầu tiên, và sau đó là số lượng thành phần liên thông mới sau mỗi sự kiện.

# Giới hạn

* $2 \le n \le 10^5$
* $1 \le m,k \le 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3 3
1 4
2 3
3 5
1 2 5
2 3 5
1 1 2
```

Kết quả:

```cpp
2 2 2 1
```
