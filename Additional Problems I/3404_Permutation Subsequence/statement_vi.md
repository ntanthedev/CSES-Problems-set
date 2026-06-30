# 3404 - Permutation Subsequence

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho hai mảng là các hoán vị, hãy tìm dãy con chung dài nhất của chúng.

Một dãy con là một dãy các phần tử của mảng từ trái sang phải có thể chứa khoảng trống. Một dãy con chung là dãy con xuất hiện trong cả hai mảng.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước của hai mảng.

Dòng thứ hai chứa $n$ số nguyên $a\_1,a\_2,\dots,a\_n$: nội dung của mảng thứ nhất.

Dòng thứ ba chứa $m$ số nguyên $b\_1,b\_2,\dots,b\_m$: nội dung của mảng thứ hai.

# Kết quả

Đầu tiên in ra độ dài của dãy con chung dài nhất.

Sau đó, in ra một ví dụ của dãy con đó. Nếu có nhiều nghiệm, bạn có thể in ra bất kỳ nghiệm nào.

# Giới hạn

* $1 \le n,m \le 2 \cdot 10^5$
* $1 \le a\_i \le n$
* $1 \le b\_i \le m$

# Ví dụ

Dữ liệu vào:

```cpp
8 6
3 1 2 8 5 7 6 4
6 5 1 2 3 4
```

Kết quả:

```cpp
3
1 2 4
```
