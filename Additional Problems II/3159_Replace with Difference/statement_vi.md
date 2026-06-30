# 3159 - Thay thế bằng Hiệu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Bạn sẽ thực hiện $n-1$ thao tác trên mảng.

Trong một thao tác, bạn chọn hai số $a$ và $b$ từ mảng, xóa cả hai khỏi mảng và thêm $|a - b|$ vào mảng.

Nhiệm vụ của bạn là tìm một dãy thao tác sao cho số cuối cùng còn lại trong mảng là $0$.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: độ dài của mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: các phần tử của mảng.

# Kết quả

In ra $n-1$ dòng, mỗi dòng chứa hai số nguyên $a$ và $b$: các số được chọn trong thao tác. Bạn có thể in ra bất kỳ nghiệm nào hợp lệ.

Nếu không có nghiệm, chỉ in ra $-1$.

# Giới hạn

* $2 \le n \le 1000$
* $1 \le x\_i \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
5
2 7 4 12 1
```

Kết quả:

```cpp
2 12
7 10
4 1
3 3
```

*Giải thích*: Mảng biến đổi như sau:

* $[2, 7, 4, 12, 1] \rightarrow$ xóa $2$ và $12$, thêm $10$
* $[7, 4, 1, 10] \rightarrow$ xóa $7$ và $10$, thêm $3$
* $[4, 1, 3] \rightarrow$ xóa $4$ và $1$, thêm $3$
* $[3, 3] \rightarrow$ xóa $3$ và $3$, thêm $0$
* $[0]$: mảng cuối cùng
