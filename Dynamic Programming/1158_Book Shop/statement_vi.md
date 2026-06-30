# 1158 - Book Shop

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn đang ở một hiệu sách bán $n$ cuốn sách khác nhau. Bạn biết giá và số trang của mỗi cuốn sách.

Bạn quyết định rằng tổng giá tiền mua sắm của bạn sẽ không vượt quá $x$. Hỏi số trang tối đa bạn có thể mua là bao nhiêu? Bạn chỉ có thể mua mỗi cuốn sách tối đa một lần.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $x$: số lượng sách và tổng giá tiền tối đa.

Dòng tiếp theo chứa $n$ số nguyên $h\_1,h\_2,\ldots,h\_n$: giá của mỗi cuốn sách.

Dòng cuối cùng chứa $n$ số nguyên $s\_1,s\_2,\ldots,s\_n$: số trang của mỗi cuốn sách.

# Kết quả

In ra một số nguyên: số trang tối đa.

# Giới hạn

* $1 \le n \le 1000$
* $1 \le x \le 10^5$
* $1 \le h\_i, s\_i \le 1000$

# Ví dụ

Input:

```cpp
4 10
4 8 5 3
5 12 8 1
```

Output:

```cpp
13
```

Giải thích: Bạn có thể mua sách 1 và 3. Tổng giá là $4+5=9$ và số trang là $5+8=13$.
