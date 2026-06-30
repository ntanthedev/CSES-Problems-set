# 2185 - Bội số nguyên tố

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $k$ số nguyên tố phân biệt $a\_1,a\_2,\ldots,a\_k$ và một số nguyên $n$.

Nhiệm vụ của bạn là đếm xem có bao nhiêu số trong $n$ số nguyên dương đầu tiên
chia hết cho ít nhất một trong các số nguyên tố đã cho.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$.

Dòng thứ hai chứa $k$ số nguyên tố $a\_1,a\_2,\ldots,a\_k$.

# Kết quả

In ra một số nguyên: số lượng số trong khoảng $1,2,\ldots,n$ chia hết cho ít nhất
một trong các số nguyên tố.

# Giới hạn

* $1 \le n \le 10^{18}$
* $1 \le k \le 20$
* $2 \le a\_i \le n$

# Ví dụ

Dữ liệu vào:

```cpp
20 2
2 5
```

Kết quả:

```cpp
12
```

Giải thích: $12$ số đó là $2,4,5,6,8,10,12,14,15,16,18,20$.
