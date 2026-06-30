# 1742 - Đường Đi Robot

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một mô tả về đường đi của robot. Robot bắt đầu tại điểm $(0,0)$ và thực hiện $n$ câu lệnh. Mỗi câu lệnh di chuyển robot một khoảng cách nào đó lên trên, xuống dưới, sang trái hoặc sang phải.

Robot sẽ dừng lại khi nó đã thực hiện tất cả các câu lệnh, hoặc ngay lập tức khi nó quay lại một điểm mà nó đã đi qua trước đó. Nhiệm vụ của bạn là tính tổng khoảng cách robot di chuyển.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng câu lệnh.

Sau đó là $n$ dòng mô tả các câu lệnh. Mỗi dòng chứa một ký tự $d$ và một số nguyên $x$: robot di chuyển khoảng cách $x$ theo hướng $d$. Mỗi hướng là U (lên trên), D (xuống dưới), L (sang trái), hoặc R (sang phải).

# Kết quả

In ra tổng khoảng cách robot di chuyển.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le x \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
5
U 2
R 3
D 1
L 5
U 2
```

Kết quả:

```cpp
9
```
