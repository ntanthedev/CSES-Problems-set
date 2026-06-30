# 3301 - Maximum Average Subarrays

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Với mỗi $i = 1, 2,\dots, n$, nhiệm vụ của bạn là tìm đoạn con kết thúc tại chỉ số $i$ có giá trị trung bình lớn nhất. Nếu có nhiều đoạn con có giá trị trung bình lớn nhất, bạn cần tìm đoạn dài nhất.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước của mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: nội dung của mảng.

# Kết quả

In ra $n$ số nguyên: độ dài của đoạn con kết thúc tại chỉ số $i$ có giá trị trung bình lớn nhất với mỗi $i = 1, 2,\dots, n$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
7
1 6 4 6 2 5 5
```

Kết quả:

```cpp
1 1 2 1 4 1 2
```

*Giải thích*: Xét $i = 5$. Giá trị trung bình của tất cả các đoạn con kết thúc tại chỉ số $5$ lần lượt là $\frac{1 + 6 + 4 + 6 + 2}{5} = 3.8$, $\frac{6 + 4 + 6 + 2}{4} = 4.5$, $\frac{4 + 6 + 2}{3} = 4$, $\frac{6 + 2}{2} = 4$ và $\frac{2}{1} = 2$. Giá trị trung bình lớn nhất là $4.5$ và độ dài của đoạn con tương ứng là $4$.
