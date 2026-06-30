# 2419 - Đỉnh tháp xor

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một tháp xor, trong đó mỗi số là xor của số ở dưới-trái và dưới-phải. Dưới đây là một ví dụ về tháp:
![](382652cc16953396bbaeeabf0e98daec74a4bda09afb8db8da0e67870205fc76)
Cho hàng dưới cùng của tháp, nhiệm vụ của bạn là tìm số ở đỉnh.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của tháp.

Dòng tiếp theo chứa $n$ số nguyên $a\_1,a\_2,\dots,a\_n$: hàng dưới cùng của tháp.

# Kết quả

In ra một số nguyên: số ở đỉnh tháp.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8
2 10 5 12 9 5 1 5
```

Kết quả:

```cpp
9
```
