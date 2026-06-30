# 1148 - Maximum Building II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho bản đồ một khu rừng, trong đó một số ô trống và một số ô có cây.

Bạn muốn đặt một tòa nhà hình chữ nhật trong khu rừng sao cho không cần phải chặt cây nào. Với mỗi kích thước tòa nhà, nhiệm vụ của bạn là tính số cách bạn có thể thực hiện điều này.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước của khu rừng.

Sau đó, khu rừng được mô tả. Mỗi ô là trống (`.`) hoặc có cây (`*`).

# Kết quả

In ra $n$ dòng, mỗi dòng chứa $m$ số nguyên.

# Giới hạn

* $1 \le n,m \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
4 7
...*.*.
.*.....
.......
......*
```

Kết quả:

```cpp
24 17 13 9 6 3 1 
16 9 7 5 3 1 0 
9 3 2 1 0 0 0 
3 0 0 0 0 0 0
```

*Giải thích*: Ví dụ, có $5$ vị trí khả dĩ cho một tòa nhà kích thước $2 \times 4$.
