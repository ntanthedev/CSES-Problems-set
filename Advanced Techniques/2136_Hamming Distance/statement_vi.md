# 2136 - Khoảng Cách Hamming

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Khoảng cách Hamming giữa hai xâu $a$ và $b$ có cùng độ dài là số vị trí mà hai xâu khác nhau.

Bạn được cho $n$ xâu nhị phân, mỗi xâu có độ dài $k$ và nhiệm vụ của bạn là tính khoảng cách Hamming nhỏ nhất giữa hai xâu bất kỳ.

# Dữ liệu vào

Dòng đầu tiên gồm hai số nguyên $n$ và $k$: số lượng xâu nhị phân và độ dài của chúng.

Sau đó là $n$ dòng, mỗi dòng gồm một xâu nhị phân độ dài $k$.

# Kết quả

In ra khoảng cách Hamming nhỏ nhất giữa hai xâu.

# Giới hạn

* $2 \le n \le 2 \cdot 10^4$
* $1 \le k \le 30$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
110111
001000
100001
101000
101110
```

Kết quả:

```cpp
1
```

Giải thích: Các xâu `101000` và `001000` chỉ khác nhau ở vị trí đầu tiên.
