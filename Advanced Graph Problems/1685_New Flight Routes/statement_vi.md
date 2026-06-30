# 1685 - Tuyến Bay Mới

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ kết nối chuyến bay giữa chúng. Nhiệm vụ của bạn là thêm các chuyến bay mới sao cho có thể đi từ bất kỳ thành phố nào đến bất kỳ thành phố nào khác. Số lượng chuyến bay mới tối thiểu cần thêm là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và chuyến bay. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các chuyến bay. Mỗi dòng có hai số nguyên $a$ và $b$: có một chuyến bay từ thành phố $a$ đến thành phố $b$. Tất cả các chuyến bay đều là chuyến bay một chiều.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượng chuyến bay mới cần thêm. Sau đó, in ra $k$ dòng mô tả các chuyến bay mới. Bạn có thể in bất kỳ lời giải hợp lệ nào.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 2
2 3
3 1
1 4
3 4
```

Kết quả:

```cpp
1
4 2
```
