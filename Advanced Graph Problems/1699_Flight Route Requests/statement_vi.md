# 1699 - Yêu Cầu Tuyến Bay

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố có sân bay nhưng không có kết nối chuyến bay nào. Bạn được cho $m$ yêu cầu về các tuyến đường cần có thể di chuyển được.

Nhiệm vụ của bạn là xác định số lượng tối thiểu các kết nối chuyến bay một chiều để có thể đáp ứng tất cả các yêu cầu.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và số lượng yêu cầu. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các yêu cầu. Mỗi dòng chứa hai số nguyên $a$ và $b$: cần có một tuyến đường từ thành phố $a$ đến thành phố $b$. Mỗi yêu cầu là duy nhất.

# Kết quả

In ra một số nguyên: số lượng tối thiểu các kết nối chuyến bay.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a, b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 2
2 3
2 4
3 1
3 4
```

Kết quả:

```cpp
4
```

Giải thích: Bạn có thể tạo các kết nối $1 \rightarrow 2$, $2 \rightarrow 3$, $2 \rightarrow 4$ và $3 \rightarrow 1$. Sau đó bạn cũng có thể bay từ thành phố $3$ đến thành phố $4$ sử dụng tuyến đường $3 \rightarrow 1 \rightarrow 2 \rightarrow 4$.
