# 1647 - Static Range Minimum Queries

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: giá trị nhỏ nhất trong đoạn $[a,b]$ là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng giá trị và số truy vấn.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các giá trị của mảng.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$: giá trị nhỏ nhất trong đoạn $[a,b]$ là bao nhiêu?

# Kết quả

In ra kết quả của mỗi truy vấn.

# Giới hạn

* $1 \le n,q \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
8 4
3 2 4 5 1 1 5 3
2 4
5 6
1 8
3 3
```

Kết quả:

```cpp
2
1
1
4
```
