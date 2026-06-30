# 3227 - Trượt Cửa Sổ Quảng Cáo

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một hàng rào gồm $n$ tấm ván dọc. Chiều rộng mỗi tấm ván là 1 và chiều cao có thể khác nhau.

Bạn muốn gắn một tấm biển quảng cáo hình chữ nhật lên hàng rào. Nhiệm vụ của bạn là tính diện tích lớn nhất của một tấm biển như vậy trong từng cửa sổ gồm $k$ tấm ván dọc, từ trái sang phải.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: chiều rộng của hàng rào và kích thước cửa sổ.

Sau đó là $n$ số nguyên $x\_1, x\_2, \dots, x\_n$: chiều cao của mỗi tấm ván.

# Kết quả

In ra $n - k + 1$ số nguyên: diện tích lớn nhất của các tấm biển quảng cáo.

# Giới hạn

* $1 \le k \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Input:

```cpp
8 3
4 1 5 3 3 2 4 1
```

Output:

```cpp
5 6 9 6 6 4
```
