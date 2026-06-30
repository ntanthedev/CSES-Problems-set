# 3233 - All Subarray Xors

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là tìm tất cả các số nguyên là tổng xor trong một đoạn con nào đó.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các phần tử của mảng.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượng số nguyên phân biệt là tổng xor trong một đoạn con nào đó.

Sau đó in ra $k$ số nguyên: các tổng xor theo thứ tự tăng dần.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $0 \le x\_i \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
4
5 1 5 9
```

Kết quả:

```cpp
7
1 4 5 8 9 12 13
```
