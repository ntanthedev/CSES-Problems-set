# 3308 - Tô Màu Đồ Thị

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị đơn gồm $n$ đỉnh và $m$ cạnh. Nhiệm vụ của bạn là sử dụng số lượng màu ít nhất có thể để tô màu mỗi đỉnh sao cho không có cạnh nào nối hai đỉnh cùng màu.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và cạnh. Các đỉnh được đánh số $1, 2,\dots, n$.

Sau đó là $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối hai đỉnh $a$ và $b$.

# Kết quả

Đầu tiên, in ra một số nguyên $k$: số lượng màu tối thiểu.

Sau đó, in ra $n$ số nguyên $c\_1, c\_2,\dots, c\_n$: màu sắc của các đỉnh. Các màu phải thỏa mãn $1 \le c\_i \le k$.

Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le n \le 16$
* $0 \le m \le \frac{n(n-1)}{2}$

# Ví dụ

Dữ liệu vào:

```cpp
4 4
1 2
2 3
3 4
4 1
```

Kết quả:

```cpp
2
1 2 1 2
```
