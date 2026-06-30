# 1746 - Mô tả mảng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn biết rằng một mảng có $n$ số nguyên nằm giữa $1$ và $m$, và chênh lệch tuyệt đối giữa hai giá trị liền kề không vượt quá $1$.

Cho một mô tả về mảng trong đó một số giá trị có thể chưa biết, nhiệm vụ của bạn là đếm số lượng mảng phù hợp với mô tả.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước mảng và chặn trên cho mỗi giá trị.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng. Giá trị $0$ biểu thị một giá trị chưa biết.

# Kết quả

In ra một số nguyên: số lượng mảng modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 100$
* $0 \le x\_i \le m$

# Ví dụ

Dữ liệu vào:

```cpp
3 5
2 0 2
```

Kết quả:

```cpp
3
```

Giải thích: Các mảng $[2,1,2]$, $[2,2,2]$ và $[2,3,2]$ phù hợp với mô tả.
