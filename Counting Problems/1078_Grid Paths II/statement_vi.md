# 1078 - Grid Paths II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một lưới $n \times n$ có ô trên cùng bên trái là $(1,1)$ và ô dưới cùng bên phải là $(n,n)$.

Nhiệm vụ của bạn là đi từ ô trên cùng bên trái đến ô dưới cùng bên phải. Mỗi bước bạn có thể di chuyển một ô sang phải hoặc xuống dưới. Ngoài ra, có $m$ bẫy trong lưới. Bạn không thể đi vào ô có bẫy.

Tổng số đường đi có thể là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước lưới và số lượng bẫy.

Sau đó là $m$ dòng mô tả các bẫy. Mỗi dòng chứa hai số nguyên $y$ và $x$: vị trí của một bẫy.

Bạn có thể giả sử không có bẫy nào ở ô trên cùng bên trái và ô dưới cùng bên phải.

# Kết quả

In ra số đường đi modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 10^6$
* $1 \le m \le 1000$
* $1 \le y,x \le n$

# Ví dụ

Input:

```cpp
3 1
2 2
```

Output:

```cpp
2
```
