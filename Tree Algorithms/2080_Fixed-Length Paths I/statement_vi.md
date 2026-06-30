# 2080 - Đường đi độ dài cố định I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây gồm $n$ đỉnh, nhiệm vụ của bạn là đếm số lượng đường đi phân biệt có chính xác $k$ cạnh.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số lượng đỉnh và độ dài đường đi. Các đỉnh được đánh số $1,2,\ldots,n$.

Sau đó là $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối giữa đỉnh $a$ và đỉnh $b$.

# Kết quả

In ra một số nguyên: số lượng đường đi.

# Giới hạn

* $1 \le k \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 2
1 2
2 3
3 4
3 5
```

Kết quả:

```cpp
4
```
