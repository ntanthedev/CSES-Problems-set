# 1689 - Hành trình của quân mã

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một vị trí bắt đầu của quân mã trên bàn cờ $8 \times 8$, nhiệm vụ của bạn là tìm một dãy các nước đi sao cho nó đi qua mỗi ô đúng một lần.

Tại mỗi nước đi, quân mã có thể di chuyển hai bước theo chiều ngang và một bước theo chiều dọc, hoặc một bước theo chiều ngang và hai bước theo chiều dọc.

# Dữ liệu vào

Dòng duy nhất chứa hai số nguyên $x$ và $y$: vị trí bắt đầu của quân mã.

# Kết quả

In ra một lưới thể hiện cách quân mã di chuyển (theo ví dụ). Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le x,y \le 8$

# Ví dụ

Dữ liệu vào:

```cpp
2 1
```

Kết quả:

```cpp
8 1 10 13 6 3 20 17 
11 14 7 2 19 16 23 4 
26 9 12 15 24 5 18 21 
49 58 25 28 51 22 33 30 
40 27 50 59 32 29 52 35 
57 48 41 44 37 34 31 62 
42 39 46 55 60 63 36 53 
47 56 43 38 45 54 61 64
```
