# 3149 - Thu Thập Đồng Xu Trên Cây II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây gồm $n$ nút. Một số nút có chứa một đồng xu.

Nhiệm vụ của bạn là trả lời $q$ truy vấn có dạng: độ dài ngắn nhất của một đường đi từ đỉnh $a$ đến đỉnh $b$ đi qua tất cả các đỉnh có đồng xu là bao nhiêu?

## Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng nút và số truy vấn. Các nút được đánh số $1, 2, \dots, n$.

Dòng thứ hai chứa $n$ số nguyên $c\_1, c\_2,\dots, c\_n$. Nếu $c\_i = 1$, nút $i$ có một đồng xu. Nếu $c\_i = 0$, nút $i$ không có đồng xu. Bạn có thể giả sử có ít nhất một nút có đồng xu.

Sau đó có $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh giữa hai nút $a$ và $b$.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$: nút bắt đầu và nút kết thúc.

## Kết quả

In ra $q$ số nguyên: câu trả lời cho các truy vấn.

## Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le a, b \le n$

## Ví dụ

Dữ liệu vào:

```cpp
5 4
1 0 0 1 0
2 4
2 3
1 3
3 5
1 5
3 2
4 4
5 5
```

Kết quả:

```cpp
6
5
6
8
```
