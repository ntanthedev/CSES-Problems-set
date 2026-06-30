# 1709 - Lưới xu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một lưới $n \times n$ mà mỗi ô vuông hoặc để trống hoặc có một đồng xu. Trong mỗi lượt, bạn có thể loại bỏ tất cả các đồng xu trong một hàng hoặc một cột.

Hỏi số lượt tối thiểu để lưới trống là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của lưới. Các hàng và cột được đánh số $1,2,\dots,n$.

Sau đó, có $n$ dòng mô tả lưới. Mỗi dòng có $n$ ký tự: mỗi ký tự là `.` (trống) hoặc `o` (đồng xu).

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượt tối thiểu. Sau đó, in ra $k$ dòng mô tả các lượt.

Trên mỗi dòng, đầu tiên in $1$ (hàng) hoặc $2$ (cột), và sau đó là số của hàng hoặc cột. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le n \le 100$

# Ví dụ

Dữ liệu vào:

```cpp
3
..o
o.o
...
```

Kết quả:

```cpp
2
1 2
2 3
```
