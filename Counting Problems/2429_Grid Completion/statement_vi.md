# 2429 - Hoàn thiện lưới

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tạo một lưới $n \times n$ mà mỗi hàng và mỗi cột có đúng một ký tự A và B. Một số ký tự đã được đặt trước. Có bao nhiêu cách để hoàn thiện lưới?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của lưới.

Sau đó, có $n$ dòng mô tả lưới. Mỗi dòng có $n$ ký tự: `.` nghĩa là ô trống, còn `A` và `B` thể hiện các ký tự đã được đặt trước.

Bạn có thể giả sử mỗi hàng và mỗi cột có tối đa một ký tự A và B.

# Kết quả

In ra một số nguyên: số cách lấy modulo $10^9+7$.

# Giới hạn

* $2 \le n \le 500$

# Ví dụ

Dữ liệu vào:

```cpp
5
.....
..AB.
.....
B....
...A.
```

Kết quả:

```cpp
16
```
