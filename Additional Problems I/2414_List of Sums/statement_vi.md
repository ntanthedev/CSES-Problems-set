# 2414 - Danh sách Tổng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Danh sách $A$ gồm $n$ số nguyên dương, và danh sách $B$ chứa tổng của mọi cặp phần tử trong danh sách $A$.

Ví dụ, nếu $A=[1,2,3]$, thì $B=[3,4,5]$, và nếu $A=[1,3,3,3]$, thì $B=[4,4,4,6,6,6]$.

Cho danh sách $B$, nhiệm vụ của bạn là khôi phục lại danh sách $A$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của danh sách $A$.

Dòng tiếp theo chứa $\frac{n(n-1)}{2}$ số nguyên: nội dung của danh sách $B$.

Bạn có thể giả sử rằng tồn tại một danh sách $A$ tương ứng với đầu vào và mỗi giá trị trong $A$ nằm giữa $1 \dots k$.

# Kết quả

In ra $n$ số nguyên: nội dung của danh sách $A$.

Bạn có thể in các giá trị theo bất kỳ thứ tự nào. Nếu có nhiều hơn một nghiệm, bạn có thể in ra bất kỳ nghiệm nào.

# Giới hạn

* $3 \le n \le 100$
* $1 \le k \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
4 4 4 6 6 6
```

Kết quả:

```cpp
1 3 3 3
```

*Giải thích*: Trong trường hợp này, danh sách $A$ có thể là $[1,3,3,3]$ hoặc $[2,2,2,4]$ và cả hai nghiệm đều được chấp nhận.
