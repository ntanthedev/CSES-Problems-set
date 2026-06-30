# 2180 - Coin Arrangement

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một lưới $2 \times n$ mà mỗi ô chứa một số lượng đồng xu nhất định. Tổng số đồng xu là $2n$.

Nhiệm vụ của bạn là sắp xếp các đồng xu sao cho mỗi ô chứa đúng một đồng xu. Mỗi lượt, bạn có thể chọn một đồng xu bất kỳ và di chuyển nó sang trái, phải, lên hoặc xuống một bước.

Hãy tìm số lượng bước di chuyển tối thiểu nếu bạn hành động tối ưu.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: chiều rộng của lưới.

Sau đó là hai dòng mô tả lưới. Mỗi dòng chứa $n$ số nguyên: số lượng đồng xu trong mỗi ô.

# Kết quả

In ra một số nguyên: số lượng bước di chuyển tối thiểu.

# Giới hạn

* $1 \le n \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
4
0 1 0 1
2 0 1 3
```

Kết quả:

```cpp
5
```
