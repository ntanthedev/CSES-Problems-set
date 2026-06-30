# 3151 - Vòng lặp sắp xếp nổi bọt I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Sắp xếp nổi bọt (bubble sort) là một thuật toán sắp xếp gồm một số vòng lặp. Ở mỗi vòng lặp, thuật toán duyệt mảng từ trái sang phải và đổi chỗ bất kỳ cặp phần tử kề nhau nào đang sai thứ tự.

Cho một mảng gồm $n$ số nguyên, hãy tính số vòng lặp sắp xếp nổi bọt cần để sắp xếp mảng.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: số vòng lặp cần thiết.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
3 2 4 1 4
```

Kết quả:

```cpp
3
```

*Giải thích*: Sắp xếp nổi bọt cần ba vòng lặp để sắp xếp mảng này. Nội dung mảng sau mỗi vòng lặp là $[2,3,1,4,4]$, $[2,1,3,4,4]$, và $[1,2,3,4,4]$.
