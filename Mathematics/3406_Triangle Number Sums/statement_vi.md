# 3406 - Tổng Số Tam Giác

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một số tam giác là số nguyên dương có dạng $1+2+\dots+k$. Các số tam giác đầu tiên là $1$, $3$, $6$, $10$ và $15$.

Mọi số nguyên dương đều có thể biểu diễn thành tổng của các số tam giác. Ví dụ, $42=21+21$ và $1337=1326+10+1$.

Cho một số nguyên dương $n$, hãy xác định số lượng số tam giác nhỏ nhất có tổng bằng $n$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

Sau đó, mỗi dòng chứa một số nguyên dương $n$.

# Kết quả

Với mỗi bộ test, in ra số lượng số tam giác nhỏ nhất.

# Giới hạn

* $1 \le t \le 100$
* $1 \le n \le 10^{12}$

# Ví dụ

Dữ liệu vào:

```cpp
5
1
2
3
42
1337
```

Kết quả:

```cpp
1
2
1
2
3
```
