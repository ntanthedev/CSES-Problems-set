# 2174 - Xóa chữ số II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một số nguyên $n$. Trong mỗi bước, bạn có thể trừ khỏi nó bất kỳ số có một chữ số nào xuất hiện trong nó.

Hỏi cần ít nhất bao nhiêu bước để số đó trở thành $0$?

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$.

# Kết quả

In ra một số nguyên: số bước tối thiểu.

# Giới hạn

* $1 \le n \le 10^{18}$

# Ví dụ

Dữ liệu vào:

```cpp
27
```

Kết quả:

```cpp
5
```

*Giải thích*: Một phương án tối ưu là $27 \rightarrow 20 \rightarrow 18 \rightarrow 10 \rightarrow 9 \rightarrow 0$.
