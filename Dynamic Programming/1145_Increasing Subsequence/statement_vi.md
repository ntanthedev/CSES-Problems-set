# 1145 - Increasing Subsequence

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là xác định dãy con tăng dài nhất trong mảng, tức là dãy con dài nhất mà mỗi phần tử đều lớn hơn phần tử trước đó.

Dãy con là một dãy có thể được tạo ra từ mảng bằng cách xóa đi một số phần tử mà không thay đổi thứ tự của các phần tử còn lại.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Sau đó là $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

# Kết quả

In ra độ dài của dãy con tăng dài nhất.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Input:

```cpp
8
7 3 5 3 6 2 9 8
```

Output:

```cpp
4
```
