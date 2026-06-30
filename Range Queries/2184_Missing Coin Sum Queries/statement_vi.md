# 2184 - Truy vấn tổng tiền xu bị thiếu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn có $n$ đồng xu với giá trị nguyên dương. Các đồng xu được đánh số $1,2,\dots,n$.

Nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: "nếu bạn có thể sử dụng các đồng xu $a \dots b$, tổng nhỏ nhất không thể tạo ra là bao nhiêu?"

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng đồng xu và số lượng truy vấn.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: giá trị của mỗi đồng xu.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai giá trị $a$ và $b$: bạn có thể sử dụng các đồng xu $a \dots b$.

# Kết quả

In ra câu trả lời cho mỗi truy vấn.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
2 9 1 2 7
2 4
4 4
1 5
```

Kết quả:

```cpp
4
1
6
```

Giải thích: Đầu tiên bạn có thể sử dụng các đồng xu $[9,1,2]$, sau đó là các đồng xu $[2]$ và cuối cùng là các đồng xu $[2,9,1,2,7]$.
