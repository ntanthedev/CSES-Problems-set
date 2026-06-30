# 3428 - Vết đoạn thẳng II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ đoạn thẳng có các đầu mút có tọa độ nguyên. Mỗi tọa độ x nằm giữa $0$ và $m$. Hệ số góc của mỗi đoạn thẳng là một số nguyên.

Với mỗi tọa độ x $0,1,\dots,m$, tìm điểm lớn nhất trên bất kỳ đoạn thẳng nào. Nếu không có đoạn thẳng nào tại một điểm nào đó, giá trị lớn nhất là $-1$.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đoạn thẳng và tọa độ x lớn nhất.

$n$ dòng tiếp theo mô tả các đoạn thẳng. Mỗi dòng chứa bốn số nguyên $x\_1$, $y\_1$, $x\_2$ và $y\_2$: có một đoạn thẳng giữa hai điểm $(x\_1,y\_1)$ và $(x\_2,y\_2)$.

# Kết quả

In ra $m+1$ số nguyên: các điểm lớn nhất tại $x=0,1,\dots,m$.

# Giới hạn

* $1 \le n, m \le 10^5$
* $0 \le x\_1 < x\_2 \le m$
* $0 \le y\_1,y\_2 \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 1 3 3
1 2 4 2
2 4 5 7
2 8 5 2
```

Kết quả:

```cpp
-1 2 8 6 6 7
```
