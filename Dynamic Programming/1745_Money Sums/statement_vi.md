# 1745 - Tổng tiền

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn có $n$ đồng xu với các mệnh giá nhất định. Nhiệm vụ của bạn là tìm tất cả các tổng tiền có thể tạo ra từ những đồng xu này.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng đồng xu.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: mệnh giá của các đồng xu.

# Kết quả

Đầu tiên, in ra số nguyên $k$: số lượng tổng tiền phân biệt. Sau đó, in tất cả các tổng có thể theo thứ tự tăng dần.

# Giới hạn

* $1 \le n \le 100$
* $1 \le x\_i \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
4
4 2 5 2
```

Kết quả:

```cpp
9
2 4 5 6 7 8 9 11 13
```
