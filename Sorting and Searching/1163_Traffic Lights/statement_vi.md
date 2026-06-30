# 1163 - Đèn Giao Thông

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một con đường dài $x$ với các vị trí được đánh số $0,1,\ldots,x$. Ban đầu không có đèn giao thông nào, nhưng $n$ bộ đèn giao thông được thêm vào con đường lần lượt từng cái một.

Nhiệm vụ của bạn là tính độ dài đoạn đường dài nhất không có đèn giao thông sau mỗi lần thêm.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $x$ và $n$: độ dài con đường và số lượng bộ đèn giao thông.

Sau đó, dòng tiếp theo chứa $n$ số nguyên $p\_1,p\_2,\ldots,p\_n$: vị trí của mỗi bộ đèn giao thông. Mỗi vị trí là phân biệt.

# Kết quả

In ra độ dài đoạn đường dài nhất không có đèn giao thông sau mỗi lần thêm.

# Giới hạn

* $1 \le x \le 10^9$
* $1 \le n \le 2 \cdot 10^5$
* $0 < p\_i < x$

# Ví dụ

Input:

```cpp
8 3
3 6 2
```

Output:

```cpp
5 3 3
```
