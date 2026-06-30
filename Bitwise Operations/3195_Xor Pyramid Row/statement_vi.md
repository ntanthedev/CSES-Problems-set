# 3195 - Xor Pyramid Row

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một kim tự tháp xor trong đó mỗi số là xor của số ở dưới bên trái và dưới bên phải. Dưới đây là một ví dụ về kim tự tháp:
![](382652cc16953396bbaeeabf0e98daec74a4bda09afb8db8da0e67870205fc76)
Cho hàng dưới cùng của kim tự tháp, nhiệm vụ của bạn là tìm các số trên hàng thứ $k$ tính từ trên xuống.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: kích thước của kim tự tháp và chỉ số hàng.

Dòng tiếp theo chứa $n$ số nguyên $a\_1,a\_2,\dots,a\_n$: hàng dưới cùng của kim tự tháp.

# Kết quả

In ra $k$ số nguyên: các số trên hàng thứ $k$ tính từ trên xuống.

# Giới hạn

* $1 \le k \le n \le 2 \cdot 10^5$
* $1 \le a\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8 5
2 10 5 12 9 5 1 5
```

Kết quả:

```cpp
1 10 5 1 8
```
