# 3307 - Nearest Campsites II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một khu cắm trại được biểu diễn dưới dạng một lưới, trong đó mỗi ô có thể chứa một điểm cắm trại thuộc loại đã đặt trước hoặc tự do. Khoảng cách giữa hai ô $(x\_1, y\_1)$ và $(x\_2, y\_2)$ là khoảng cách Manhattan $|x\_1 - x\_2| + |y\_1 - y\_2|$.

Nhiệm vụ của bạn là tìm khoảng cách từ mỗi điểm cắm trại tự do đến điểm cắm trại đã đặt trước gần nhất.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng điểm cắm trại đã đặt trước và tự do.

$n$ dòng tiếp theo mô tả vị trí của các điểm cắm trại đã đặt trước. Mỗi dòng chứa hai số nguyên $x$ và $y$.

$m$ dòng tiếp theo mô tả vị trí của các điểm cắm trại tự do. Mỗi dòng chứa hai số nguyên $x$ và $y$.

Bạn có thể giả sử rằng mỗi ô chứa nhiều nhất một điểm cắm trại.

# Kết quả

In ra $m$ số nguyên: khoảng cách từ mỗi điểm cắm trại tự do đến điểm cắm trại đã đặt trước gần nhất, theo thứ tự đầu vào.

# Giới hạn

* $1 \le n, m \le 10^5$
* $1 \le x, y \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
4 2
1 1
5 2
2 6
4 7
1 3
7 5
```

Kết quả:

```cpp
2 5
```

*Giải thích*: Hình vẽ sau đây minh họa bản đồ của khu cắm trại:

![](45b7b852bdf48b322f1483feefeabeda616551cec6714a282481c84e32a748d5)

Khoảng cách từ điểm cắm trại tự do thứ nhất (bên trái) đến điểm cắm trại đã đặt trước gần nhất là $2$, và khoảng cách từ điểm cắm trại tự do thứ hai (bên phải) đến điểm cắm trại đã đặt trước gần nhất là $5$.
