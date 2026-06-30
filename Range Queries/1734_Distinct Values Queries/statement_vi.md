# 1734 - Truy vấn giá trị phân biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một mảng gồm $n$ số nguyên và $q$ truy vấn có dạng: có bao nhiêu giá trị phân biệt trong đoạn $[a,b]$?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: kích thước mảng và số lượng truy vấn.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các giá trị của mảng.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$.

# Kết quả

Với mỗi truy vấn, in ra số lượng giá trị phân biệt trong đoạn.

# Giới hạn

* $1 \le n,q \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
3 2 3 1 2
1 3
2 4
1 5
```

Kết quả:

```cpp
2
3
3
```
