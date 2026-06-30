# 3403 - Dãy con chung dài nhất

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho hai mảng số nguyên, tìm dãy con chung dài nhất của chúng.

Một dãy con là một dãy các phần tử của mảng từ trái sang phải có thể bỏ qua một số phần tử. Một dãy con chung là một dãy con xuất hiện trong cả hai mảng.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước của hai mảng.

Dòng thứ hai chứa $n$ số nguyên $a\_1,a\_2,\dots,a\_n$: nội dung của mảng thứ nhất.

Dòng thứ ba chứa $m$ số nguyên $b\_1,b\_2,\dots,b\_m$: nội dung của mảng thứ hai.

# Kết quả

Đầu tiên in ra độ dài của dãy con chung dài nhất.

Sau đó, in ra một ví dụ của dãy con đó. Nếu có nhiều lời giải, bạn có thể in ra bất kỳ lời giải nào.

# Giới hạn

* $1 \le n,m \le 1000$
* $1 \le a\_i, b\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8 6
3 1 3 2 7 4 8 2
6 5 1 2 3 4
```

Kết quả:

```cpp
3
1 2 4
```
