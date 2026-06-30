# 2177 - Cạnh Liên Thông Mạnh

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị vô hướng, nhiệm vụ của bạn là chọn hướng cho mỗi cạnh sao cho đồ thị có hướng thu được là liên thông mạnh.

## Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và cạnh. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh giữa hai đỉnh $a$ và $b$.

Bạn có thể giả sử đồ thị là đơn, tức là có nhiều nhất một cạnh giữa hai đỉnh và mọi cạnh đều nối hai đỉnh phân biệt.

## Kết quả

In ra $m$ dòng mô tả hướng của các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh từ đỉnh $a$ đến đỉnh $b$. Bạn có thể in ra bất kỳ nghiệm đúng nào.

Nếu không có nghiệm, chỉ in ra `IMPOSSIBLE`.

## Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

## Ví dụ

Dữ liệu vào:

```cpp
3 3
1 2
1 3
2 3
```

Kết quả:

```cpp
1 2
2 3
3 1
```
