# 2132 - Dãy tăng dần II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Bạn muốn biến đổi mảng sao cho nó là dãy tăng dần, tức là mỗi phần tử ít nhất phải lớn bằng phần tử trước đó.

Trong mỗi lượt, bạn có thể tăng hoặc giảm giá trị của bất kỳ phần tử nào đi một. Hỏi số lượt tối thiểu cần thực hiện là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Sau đó, dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

# Kết quả

In ra số lượt tối thiểu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
3 8 5 6 5
```

Kết quả:

```cpp
4
```
