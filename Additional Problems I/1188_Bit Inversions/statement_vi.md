# 1188 - Đảo Bit

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu bit gồm $n$ bit. Sau đó, có một số thao tác đảo ngược một bit cho trước. Nhiệm vụ của bạn là báo cáo, sau mỗi thao tác, độ dài của xâu con dài nhất mà mọi bit đều giống nhau.

# Dữ liệu vào

Dòng đầu tiên chứa một xâu bit gồm $n$ bit. Các bit được đánh số $1,2,\ldots,n$.

Dòng tiếp theo chứa số nguyên $m$: số lượng thao tác.

Dòng cuối cùng chứa $m$ số nguyên $x\_1,x\_2,\ldots,x\_m$ mô tả các thao tác.

# Kết quả

Sau mỗi thao tác, in ra độ dài của xâu con dài nhất mà mọi bit đều giống nhau.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le x\_i \le n$

# Ví dụ

Dữ liệu vào:

```cpp
001011
3
3 2 5
```

Kết quả:

```cpp
4 2 3
```

Giải thích: Xâu bit lần lượt trở thành `000011`, sau đó `010011`, và cuối cùng `010001`.
