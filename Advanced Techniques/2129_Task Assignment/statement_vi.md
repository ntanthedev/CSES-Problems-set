# 2129 - Phân Công Công Việc

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một công ty có $n$ nhân viên và $n$ công việc cần được thực hiện. Chúng ta biết chi phí thực hiện mỗi công việc đối với từng nhân viên. Mỗi nhân viên nên được phân công đúng một công việc. Hãy tìm tổng chi phí nhỏ nhất nếu phân công công việc một cách tối ưu và cách phân công tương ứng.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng nhân viên và số lượng công việc cần thực hiện.

Sau đó, có $n$ dòng, mỗi dòng gồm $n$ số nguyên. Dòng thứ $i$ gồm các số nguyên $c\_{i1},c\_{i2},\ldots,c\_{in}$: chi phí của mỗi công việc khi được giao cho nhân viên thứ $i$.

# Kết quả

Đầu tiên, in ra tổng chi phí nhỏ nhất.

Sau đó, in $n$ dòng, mỗi dòng gồm hai số nguyên $a$ và $b$: bạn phân công công việc thứ $b$ cho nhân viên thứ $a$.

Nếu có nhiều cách, bạn có thể in ra bất kỳ cách nào.

# Giới hạn

* $1 \le n \le 200$
* $1 \le c\_{ij} \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
4
17 8 16 9
7 15 12 19
6 9 10 11
14 7 13 10
```

Kết quả:

```cpp
33
1 4
2 1
3 3
4 2
```

Giải thích: Tổng chi phí nhỏ nhất là $33$. Chúng ta có thể đạt được điều này bằng cách phân công nhân viên 1 làm công việc 4, nhân viên 2 làm công việc 1, nhân viên 3 làm công việc 3 và nhân viên 4 làm công việc 2. Chi phí tương ứng là $9 + 7 + 10 + 7 = 33$.
