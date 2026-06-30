# 2165 - Tháp Hà Nội

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Trò chơi Tháp Hà Nội gồm ba cọc (trái, giữa và phải) và $n$ đĩa tròn với các kích thước khác nhau. Ban đầu, cọc trái có tất cả các đĩa, theo thứ tự kích thước tăng dần từ trên xuống dưới.

Mục tiêu là di chuyển tất cả các đĩa sang cọc phải sử dụng cọc giữa. Mỗi lần di chuyển bạn có thể di chuyển đĩa trên cùng từ một cọc sang một cọc khác. Ngoài ra, không được đặt đĩa lớn hơn lên trên đĩa nhỏ hơn.

Nhiệm vụ của bạn là tìm một giải pháp với số lần di chuyển ít nhất.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$: số lượng đĩa.

# Kết quả

Đầu tiên in một số nguyên $k$: số lần di chuyển ít nhất.

Sau đó, in $k$ dòng mô tả các lần di chuyển. Mỗi dòng gồm hai số nguyên $a$ và $b$: bạn di chuyển một đĩa từ cọc $a$ sang cọc $b$.

# Giới hạn

* $1 \le n \le 16$

# Ví dụ

Dữ liệu vào:

```cpp
2
```

Kết quả:

```cpp
3
1 2
1 3
2 3
```
