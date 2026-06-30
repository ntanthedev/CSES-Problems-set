# 1728 - Inversion Probability

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một mảng có $n$ số nguyên $x\_1,x\_2,\dots,x\_n$, mỗi số được chọn ngẫu nhiên từ $1$ đến $r\_i$. Một nghịch thế (inversion) là một cặp $(a,b)$ thỏa $a<b$ và $x\_a>x\_b$.

Tính số nghịch thế kỳ vọng trong mảng?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Dòng thứ hai chứa $n$ số nguyên $r\_1,r\_2,\dots,r\_n$: khoảng giá trị có thể có cho mỗi vị trí trong mảng.

# Kết quả

In ra số nghịch thế kỳ vọng làm tròn đến sáu chữ số thập phân (làm tròn nửa đến chẵn).

# Giới hạn

* $1 \le n \le 100$
* $1 \le r\_i \le 100$

# Ví dụ

Dữ liệu vào:

```cpp
3
5 2 7
```

Kết quả:

```cpp
1.057143
```
