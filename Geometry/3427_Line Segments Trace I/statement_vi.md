# 3427 - Vết đoạn thẳng I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ đoạn thẳng có các đầu mút có tọa độ nguyên. Tọa độ x bên trái của mỗi đoạn là $0$ và tọa độ x bên phải là $m$. Hệ số góc của mỗi đoạn thẳng là một số nguyên.

Với mỗi tọa độ x $0,1,\dots,m$, tìm điểm lớn nhất trên bất kỳ đoạn thẳng nào.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đoạn thẳng và tọa độ x lớn nhất.

$n$ dòng tiếp theo mô tả các đoạn thẳng. Mỗi dòng chứa hai số nguyên $y\_1$ và $y\_2$: có một đoạn thẳng giữa hai điểm $(0,y\_1)$ và $(m,y\_2)$.

# Kết quả

In ra $m+1$ số nguyên: các điểm lớn nhất tại $x=0,1,\dots,m$.

# Giới hạn

* $1 \le n, m \le 10^5$
* $0 \le y\_1,y\_2 \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 6
7 2
5 5
10 0
```

Kết quả:

```cpp
10 8 6 5 5 6
```
