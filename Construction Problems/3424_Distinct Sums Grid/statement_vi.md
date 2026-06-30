# 3424 - Lưới tổng phân biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Hãy tạo một lưới $n \times n$ thỏa mãn các yêu cầu sau:

1. Mỗi số nguyên $1 \dots n$ xuất hiện $n$ lần trong lưới.
2. Nếu tạo một tập hợp gồm tất cả các tổng trên các hàng và cột, có $2n$ giá trị phân biệt.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$.

# Kết quả

In ra một lưới thỏa mãn các yêu cầu. Bạn có thể in ra bất kỳ phương án hợp lệ nào. Nếu không có lời giải, in ra `IMPOSSIBLE`.

# Giới hạn

* $1 \le n \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
5
```

Kết quả:

```cpp
2 3 1 1 1 
1 5 5 3 3 
2 3 5 2 4 
5 4 5 4 1 
2 3 4 4 2
```

*Giải thích*: Mỗi số nguyên $1 \dots 5$ xuất hiện $5$ lần, và các tổng trên các hàng và cột là $\{8,11,12,14,15,16,17,18,19,20\}$.
