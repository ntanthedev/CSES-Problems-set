# 1741 - Diện Tích Hình Chữ Nhật

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n$ hình chữ nhật, nhiệm vụ của bạn là xác định tổng diện tích phần hợp của chúng.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng hình chữ nhật.

Sau đó là $n$ dòng mô tả các hình chữ nhật. Mỗi dòng chứa bốn số nguyên $x\_1$, $y\_1$, $x\_2$ và $y\_2$: một hình chữ nhật bắt đầu tại điểm $(x\_1,y\_1)$ và kết thúc tại điểm $(x\_2,y\_2)$.

# Kết quả

In ra tổng diện tích được phủ bởi các hình chữ nhật.

# Giới hạn

* $1 \le n \le 10^5$
* $-10^6 \le x\_1 < x\_2 \le 10^6$
* $-10^6 \le y\_1 < y\_2 \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
3
1 3 4 5
3 1 7 4
5 3 8 6
```

Kết quả:

```cpp
24
```
