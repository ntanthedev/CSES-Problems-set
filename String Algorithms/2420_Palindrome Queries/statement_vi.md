# 2420 - Truy vấn Palindrome

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu gồm $n$ ký tự trong khoảng a–z. Các vị trí của xâu được đánh chỉ số $1,2,\dots,n$.

Nhiệm vụ của bạn là xử lý $m$ thao tác thuộc các loại sau:

1. Thay đổi ký tự tại vị trí $k$ thành $x$
2. Kiểm tra xem xâu con từ vị trí $a$ đến vị trí $b$ có phải là palindrome hay không

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: độ dài của xâu và số lượng thao tác.

Dòng tiếp theo chứa một xâu gồm $n$ ký tự.

Cuối cùng, có $m$ dòng mô tả các thao tác. Mỗi dòng có dạng "1 $k$ $x$" hoặc "2 $a$ $b$".

# Kết quả

Với mỗi thao tác loại 2, in ra YES nếu xâu con là palindrome và NO nếu ngược lại.

# Giới hạn

* $1 \le n, m \le 2 \cdot 10^5$
* $1 \le k \le n$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
7 5
aybabtu
2 3 5
1 3 x
2 3 5
1 5 x
2 3 5
```

Kết quả:

```cpp
YES
NO
YES
```
