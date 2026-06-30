# 2217 - Thu Thập Số II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng chứa mỗi số từ $1 \dots n$ đúng một lần. Nhiệm vụ của bạn là thu thập các số từ $1$ đến $n$ theo thứ tự tăng dần.

Trong mỗi lượt, bạn đi qua mảng từ trái sang phải và thu thập càng nhiều số càng tốt.

Cho $m$ thao tác đổi chỗ hai số trong mảng, nhiệm vụ của bạn là báo cáo số lượt sau mỗi thao tác.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước mảng và số thao tác.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các số trong mảng.

Cuối cùng, có $m$ dòng mô tả các thao tác. Mỗi dòng chứa hai số nguyên $a$ và $b$: các số tại vị trí $a$ và $b$ được đổi chỗ cho nhau.

# Kết quả

In ra $m$ số nguyên: số lượt sau mỗi lần đổi chỗ.

# Giới hạn

* $1 \le n, m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
4 2 1 5 3
2 3
1 5
2 3
```

Kết quả:

```cpp
2
3
4
```
