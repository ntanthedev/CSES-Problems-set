# 1159 - Book Shop II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn đang ở một hiệu sách bán $n$ cuốn sách khác nhau. Bạn biết giá, số trang và số lượng bản sao của mỗi cuốn sách.

Bạn đã quyết định rằng tổng giá mua sẽ không vượt quá $x$. Hỏi số trang tối đa bạn có thể mua là bao nhiêu? Bạn có thể mua nhiều bản sao của cùng một cuốn sách.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $x$: số lượng sách và tổng giá tối đa.

Dòng tiếp theo chứa $n$ số nguyên $h\_1,h\_2,\ldots,h\_n$: giá của mỗi cuốn sách.

Dòng tiếp theo chứa $n$ số nguyên $s\_1,s\_2,\ldots,s\_n$: số trang của mỗi cuốn sách.

Dòng cuối cùng chứa $n$ số nguyên $k\_1,k\_2,\ldots,k\_n$: số lượng bản sao của mỗi cuốn sách.

# Kết quả

In ra một số nguyên: số trang tối đa.

# Giới hạn

* $1 \le n \le 100$
* $1 \le x \le 10^5$
* $1 \le h\_i, s\_i, k\_i \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
3 10
2 6 3
8 5 4
3 5 2
```

Kết quả:

```cpp
28
```

Giải thích: Bạn có thể mua ba bản sao của sách 1 và một bản sao của sách 3. Tổng giá là $3 \cdot 2 + 3 = 9$ và tổng số trang là $3 \cdot 8 + 4 = 28$.
