# 3150 - Tổng các giá trị phân biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng $x\_1,x\_2,\dots,x\_n$. Gọi $d(a,b)$ là số lượng giá trị phân biệt trong đoạn con $x\_a,x\_{a+1},\dots,x\_b$.

Nhiệm vụ của bạn là tính tổng $\sum\_{a=1}^n \sum\_{b=a}^n d(a,b)$, tức là tổng các $d(a,b)$ trên tất cả các đoạn con.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: tổng cần tìm.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 2 3 1 1
```

Kết quả:

```cpp
29
```

*Giải thích*: Trong mảng này, $6$ đoạn con có $1$ giá trị phân biệt, $4$ đoạn con có $2$ giá trị phân biệt và $5$ đoạn con có $3$ giá trị phân biệt. Vậy tổng là $6\cdot1+4\cdot2+5\cdot3=29$.
