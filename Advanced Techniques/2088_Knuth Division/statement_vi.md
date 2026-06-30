# 2088 - Knuth Division

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số, nhiệm vụ của bạn là chia nó thành $n$ đoạn con, mỗi đoạn có đúng một phần tử.

Ở mỗi bước, bạn có thể chọn một đoạn con bất kỳ và tách nó thành hai đoạn con. Chi phí của bước đó là tổng các giá trị trong đoạn con được chọn.

Tổng chi phí tối thiểu nếu bạn hành động tối ưu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước mảng. Các phần tử của mảng được đánh số $1,2,\dots,n$.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: tổng chi phí tối thiểu.

# Giới hạn

* $1 \le n \le 5000$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
2 7 3 2 5
```

Kết quả:

```cpp
43
```
