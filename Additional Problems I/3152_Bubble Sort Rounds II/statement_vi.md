# 3152 - Vòng lặp sắp xếp nổi bọt II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Sắp xếp nổi bọt (bubble sort) là một thuật toán sắp xếp gồm một số vòng lặp. Ở mỗi vòng lặp, thuật toán duyệt mảng từ trái sang phải và đổi chỗ bất kỳ cặp phần tử kề nhau nào đang sai thứ tự.

Cho một mảng gồm $n$ số nguyên, hãy tìm nội dung của mảng sau $k$ vòng lặp sắp xếp nổi bọt.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: kích thước mảng và số vòng lặp.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

In ra $n$ số nguyên: nội dung của mảng sau $k$ vòng lặp.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $0 \le k \le 10^9$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 2
3 2 4 1 4
```

Kết quả:

```cpp
2 1 3 4 4
```
