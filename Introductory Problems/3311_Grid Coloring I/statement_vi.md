# 3311 - Grid Coloring I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một lưới $n\times m$, mỗi ô chứa một ký tự `A`, `B`, `C` hoặc `D`.

Với mỗi ô, bạn phải đổi ký tự đó thành `A`, `B`, `C` hoặc `D`. Ký tự mới phải khác ký tự cũ.

Nhiệm vụ của bạn là đổi ký tự trong mọi ô sao cho không có hai ô kề nhau nào có cùng ký tự.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số hàng và số cột.

$n$ dòng tiếp theo, mỗi dòng chứa $m$ ký tự: mô tả lưới ban đầu.

# Kết quả

In ra $n$ dòng, mỗi dòng $m$ ký tự: mô tả lưới cuối cùng.

Bạn có thể in ra bất kỳ lời giải hợp lệ nào.

Nếu không có lời giải, chỉ cần in ra `IMPOSSIBLE`.

# Giới hạn

* $1 \le n, m \le 500$

# Ví dụ

Dữ liệu vào:

```cpp
3 4
AAAA
BBBB
CCDD
```

Kết quả:

```cpp
CDCD
DCDC
ABAB
```
