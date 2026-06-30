# 1736 - Truy vấn đa thức

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là duy trì một mảng gồm $n$ giá trị và xử lý hiệu quả các loại truy vấn sau:

1. Tăng giá trị đầu tiên trong đoạn $[a,b]$ lên $1$, giá trị thứ hai lên $2$, giá trị thứ ba lên $3$, và cứ tiếp tục như vậy.
2. Tính tổng các giá trị trong đoạn $[a,b]$.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: kích thước của mảng và số lượng truy vấn.

Dòng tiếp theo chứa $n$ giá trị $t\_1,t\_2,\dots,t\_n$: nội dung ban đầu của mảng.

Cuối cùng là $q$ dòng mô tả các truy vấn. Định dạng của mỗi dòng là "1 $a$ $b$" hoặc "2 $a$ $b$".

# Kết quả

In ra câu trả lời cho mỗi truy vấn tính tổng.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le t\_i \le 10^6$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
4 2 3 1 7
2 1 5
1 1 5
2 1 5
```

Kết quả:

```cpp
17
32
```
