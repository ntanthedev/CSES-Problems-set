# 3312 - Tô màu Lưới II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một lưới $n\times m$ mà mỗi ô chứa một ký tự `A`, `B` hoặc `C`.

Với mỗi ô, bạn phải đổi ký tự thành `A`, `B` hoặc `C`. Ký tự mới phải khác ký tự cũ.

Nhiệm vụ của bạn là đổi các ký tự trong mọi ô sao cho không có hai ô kề nhau nào có cùng ký tự.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số hàng và số cột.

$n$ dòng tiếp theo, mỗi dòng chứa $m$ ký tự: mô tả của lưới.

# Kết quả

In ra $n$ dòng, mỗi dòng $m$ ký tự: mô tả của lưới cuối cùng.

Bạn có thể in ra bất kỳ nghiệm nào hợp lệ.

Nếu không có nghiệm, chỉ in ra `IMPOSSIBLE`.

# Giới hạn

* $1 \le n, m \le 500$

# Ví dụ

Dữ liệu vào:

```cpp
3 4
AAAA
CCBB
ABCA
```

Kết quả:

```cpp
BCBC
ABCA
CABC
```
