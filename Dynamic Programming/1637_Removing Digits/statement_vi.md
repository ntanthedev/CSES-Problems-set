# 1637 - Xóa chữ số

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một số nguyên $n$. Ở mỗi bước, bạn có thể trừ đi một chữ số bất kỳ của số đó.

Cần ít nhất bao nhiêu bước để số đó trở thành $0$?

# Dữ liệu vào

Dòng duy nhất chứa số nguyên $n$.

# Kết quả

In ra một số nguyên: số bước tối thiểu.

# Giới hạn

* $1 \le n \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
27
```

Kết quả:

```cpp
5
```

Giải thích: Một cách tối ưu là $27 \rightarrow 20 \rightarrow 18 \rightarrow 10 \rightarrow 9 \rightarrow 0$.
