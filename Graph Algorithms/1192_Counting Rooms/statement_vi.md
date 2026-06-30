# 1192 - Đếm Phòng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một bản đồ của một tòa nhà, nhiệm vụ của bạn là đếm số lượng phòng trong đó. Kích thước bản đồ là $n \times m$ ô vuông, mỗi ô là sàn hoặc tường. Bạn có thể đi trái, phải, lên và xuống qua các ô sàn.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: chiều cao và chiều rộng của bản đồ.

Sau đó là $n$ dòng, mỗi dòng gồm $m$ ký tự mô tả bản đồ. Mỗi ký tự là `.` (sàn) hoặc `#` (tường).

# Kết quả

In ra một số nguyên: số lượng phòng.

# Giới hạn

* $1 \le n,m \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
5 8
########
#..#...# 
####.#.#
#..#...#
########
```

Kết quả:

```cpp
3
```
