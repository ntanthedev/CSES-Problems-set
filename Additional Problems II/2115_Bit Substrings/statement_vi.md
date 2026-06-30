# 2115 - Xâu bit con

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu bit độ dài $n$. Nhiệm vụ của bạn là với mỗi $k$ từ $0 \ldots n$, hãy tính số lượng xâu con không rỗng chứa chính xác $k$ số 1.

Ví dụ, nếu xâu là 101, ta có:

* 1 xâu con chứa 0 số 1: 0
* 4 xâu con chứa 1 số 1: 01, 1, 1, 10
* 1 xâu con chứa 2 số 1: 101
* 0 xâu con chứa 3 số 1

# Dữ liệu vào

Dòng duy nhất chứa một xâu nhị phân độ dài $n$.

# Kết quả

In ra $n+1$ giá trị như mô tả ở trên.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
101
```

Kết quả:

```cpp
1 4 1 0
```
