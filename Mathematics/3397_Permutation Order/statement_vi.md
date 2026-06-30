# 3397 - Thứ Tự Hoán Vị

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Gọi $p(n,k)$ là hoán vị thứ $k$ (theo thứ tự từ điển) của $1 \dots n$. Ví dụ, $p(4,1)=[1,2,3,4]$ và $p(4,2)=[1,2,4,3]$.

Nhiệm vụ của bạn là xử lý hai loại truy vấn:

1. Cho $n$ và $k$, tìm $p(n,k)$
2. Cho $n$ và $p(n,k)$, tìm $k$

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

Mỗi bộ test có dạng "1 $n$ $k$" hoặc "2 $n$ $p(n,k)$".

# Kết quả

Với mỗi bộ test, in ra kết quả theo như ví dụ.

# Giới hạn

* $1 \le t \le 1000$
* $1 \le n \le 20$
* $1 \le k \le n!$

# Ví dụ

Dữ liệu vào:

```cpp
6
1 4 1
1 4 2
2 4 1 2 3 4
2 4 1 2 4 3
1 5 42
2 5 2 4 5 3 1
```

Kết quả:

```cpp
1 2 3 4
1 2 4 3
1
2
2 4 5 3 1
42
```
