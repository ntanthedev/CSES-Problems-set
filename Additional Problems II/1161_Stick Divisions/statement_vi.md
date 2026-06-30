# 1161 - Stick Divisions

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn có một thanh gỗ độ dài $x$ và bạn muốn chia nó thành $n$ thanh gỗ nhỏ, với độ dài cho trước, có tổng độ dài bằng $x$.

Mỗi bước, bạn có thể lấy một thanh gỗ bất kỳ và chia nó thành hai thanh gỗ. Chi phí của thao tác này là độ dài của thanh gỗ ban đầu.

Hỏi chi phí tối thiểu cần thiết để tạo ra các thanh gỗ là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $x$ và $n$: độ dài của thanh gỗ ban đầu và số lượng thanh gỗ trong phép chia.

Dòng thứ hai chứa $n$ số nguyên $d\_1,d\_2,\ldots,d\_n$: độ dài của mỗi thanh gỗ trong phép chia.

# Kết quả

In ra một số nguyên: chi phí tối thiểu của phép chia.

# Giới hạn

* $1 \le x \le 10^9$
* $1 \le n \le 2 \cdot 10^5$
* $\sum d\_i = x$

# Ví dụ

Dữ liệu vào:

```cpp
8 3
2 3 3
```

Kết quả:

```cpp
13
```

*Giải thích*: Đầu tiên bạn chia thanh gỗ độ dài $8$ thành hai thanh độ dài $3$ và $5$ (chi phí $8$). Sau đó, bạn chia thanh gỗ độ dài $5$ thành hai thanh độ dài $2$ và $3$ (chi phí $5$). Tổng chi phí là $8+5=13$.
