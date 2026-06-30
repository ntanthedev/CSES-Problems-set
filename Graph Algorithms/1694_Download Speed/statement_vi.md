# 1694 - Tốc độ Tải xuống

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một mạng máy tính gồm $n$ máy tính và $m$ kết nối. Mỗi kết nối xác định tốc độ một máy tính có thể gửi dữ liệu đến một máy tính khác.

Kotivalo muốn tải xuống một số dữ liệu từ một máy chủ. Hỏi tốc độ tối đa anh ta có thể đạt được khi sử dụng các kết nối trong mạng là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng máy tính và kết nối. Các máy tính được đánh số $1,2,\dots,n$. Máy tính $1$ là máy chủ và máy tính $n$ là máy tính của Kotivalo.

Sau đó, có $m$ dòng mô tả các kết nối. Mỗi dòng chứa ba số nguyên $a$, $b$ và $c$: máy tính $a$ có thể gửi dữ liệu đến máy tính $b$ với tốc độ $c$.

# Kết quả

In ra một số nguyên: tốc độ tối đa Kotivalo có thể tải dữ liệu.

# Giới hạn

* $1 \le n \le 500$
* $1 \le m \le 1000$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3
```

Kết quả:

```cpp
6
```
