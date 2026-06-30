# 3402 - Cặp Chi phí Tối thiểu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, xét việc ghép $k$ cặp. Mỗi số có thể xuất hiện trong nhiều nhất một cặp, và chi phí của một cặp $(a,b)$ là $|a-b|$. Chi phí của một cách ghép cặp là tổng chi phí của tất cả các cặp.

Tính chi phí tối thiểu của các cách ghép cặp với $k=1,2,\dots,\lfloor n/2 \rfloor$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên: kích thước của mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các phần tử của mảng.

# Kết quả

In ra $\lfloor n/2 \rfloor$ số nguyên: chi phí tối thiểu của các cách ghép cặp.

# Giới hạn

* $2 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8
3 1 2 7 9 3 4 7
```

Kết quả:

```cpp
0 0 1 6
```

*Giải thích*: Các cách ghép cặp chi phí tối thiểu có thể là $[(3,3)]$, $[(3,3),(7,7)]$, $[(1,2),(3,3),(7,7)]$ và $[(1,2),(3,3),(4,7),(7,9)]$.
