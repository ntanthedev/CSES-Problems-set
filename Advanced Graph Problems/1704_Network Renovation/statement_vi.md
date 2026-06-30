# 1704 - Nâng Cấp Mạng Lưới

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Mạng lưới của Syrjälä gồm $n$ máy tính và $n-1$ kết nối giữa chúng. Có thể gửi dữ liệu giữa hai máy tính bất kỳ.

Tuy nhiên, nếu bất kỳ kết nối nào bị đứt, sẽ không còn khả năng gửi dữ liệu giữa một số máy tính với nhau. Nhiệm vụ của bạn là thêm số lượng kết nối mới tối thiểu sao cho vẫn có thể gửi dữ liệu giữa hai máy tính bất kỳ ngay cả khi một kết nối bất kỳ bị đứt.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng máy tính. Các máy tính được đánh số $1,2,\dots,n$.

Sau đó là $n-1$ dòng mô tả các kết nối. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một kết nối giữa máy tính $a$ và $b$.

# Kết quả

Đầu tiên in một số nguyên $k$: số lượng kết nối mới tối thiểu. Sau đó, in $k$ dòng mô tả các kết nối. Bạn có thể in ra bất kỳ lời giải hợp lệ nào.

# Giới hạn

* $3 \le n \le 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 2
1 3
3 4
3 5
```

Kết quả:

```cpp
2
2 4
4 5
```
