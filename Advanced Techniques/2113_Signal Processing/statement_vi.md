# 2113 - Xử Lý Tín Hiệu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho hai dãy số nguyên: một tín hiệu và một mặt nạ. Nhiệm vụ của bạn là xử lý tín hiệu bằng cách di chuyển mặt nạ qua tín hiệu từ trái sang phải. Tại mỗi vị trí của mặt nạ, hãy tính tổng các tích của các giá trị tín hiệu và mặt nạ được căn chỉnh trong phần mà tín hiệu và mặt nạ chồng lên nhau.

# Dữ liệu vào

Dòng đầu tiên gồm hai số nguyên $n$ và $m$: độ dài của tín hiệu và độ dài của mặt nạ.

Dòng tiếp theo gồm $n$ số nguyên $a\_1,a\_2,\ldots,a\_n$ xác định tín hiệu.

Dòng cuối cùng gồm $m$ số nguyên $b\_1,b\_2,\ldots,b\_m$ xác định mặt nạ.

# Kết quả

In ra $n+m-1$ số nguyên: tổng các tích của các giá trị được căn chỉnh tại mỗi vị trí mặt nạ từ trái sang phải.

# Giới hạn

* $1 \le n,m \le 2 \cdot 10^5$
* $1 \le a\_i,b\_i \le 100$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
1 3 2 1 4
1 2 3
```

Kết quả:

```cpp
3 11 13 10 16 9 4
```

Giải thích: Ví dụ, tại vị trí mặt nạ thứ hai, tổng các tích được căn chỉnh là $2 \cdot 1 + 3 \cdot 3 = 11$.
