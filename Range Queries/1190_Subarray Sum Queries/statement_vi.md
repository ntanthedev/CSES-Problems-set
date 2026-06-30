# 1190 - Subarray Sum Queries

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Một số giá trị của mảng sẽ được cập nhật, và sau mỗi lần cập nhật, nhiệm vụ của bạn là báo cáo tổng đoạn con lớn nhất trong mảng.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước của mảng và số lần cập nhật. Mảng được đánh chỉ số $1,2,\ldots,n$.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung ban đầu của mảng.

Sau đó là $m$ dòng mô tả các thay đổi. Mỗi dòng chứa hai số nguyên $k$ và $x$: giá trị tại vị trí $k$ trở thành $x$.

# Kết quả

Sau mỗi lần cập nhật, in ra tổng đoạn con lớn nhất. Các đoạn con rỗng (có tổng $0$) được cho phép.

# Giới hạn

* $1 \le n, m \le 2 \cdot 10^5$
* $-10^9 \le x\_i \le 10^9$
* $1 \le k \le n$
* $-10^9 \le x \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
1 2 -3 5 -1
2 6
3 1
2 -2
```

Kết quả:

```cpp
9
13
6
```
