# 1193 - Mê Cung

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một bản đồ của một mê cung, nhiệm vụ của bạn là tìm đường đi từ điểm xuất phát đến điểm kết thúc. Bạn có thể đi trái, phải, lên và xuống.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: chiều cao và chiều rộng của bản đồ.

Sau đó là $n$ dòng, mỗi dòng gồm $m$ ký tự mô tả mê cung. Mỗi ký tự là `.` (sàn), `#` (tường), `A` (điểm xuất phát) hoặc `B` (điểm kết thúc). Có đúng một ký tự `A` và một ký tự `B` trong dữ liệu vào.

# Kết quả

Đầu tiên in ra "YES" nếu có đường đi, và "NO" nếu không có.

Nếu có đường đi, in ra độ dài của đường đi ngắn nhất và mô tả của nó dưới dạng một xâu gồm các ký tự `L` (trái), `R` (phải), `U` (lên) và `D` (xuống). Bạn có thể in ra bất kỳ đường đi hợp lệ nào.

# Giới hạn

* $1 \le n,m \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
5 8
########
#.A#...#
#.##.#B#
#......#
########
```

Kết quả:

```cpp
YES
9
LDDRRRRRU
```
