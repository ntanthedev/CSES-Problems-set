# 3430 - Đường thẳng và truy vấn II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là xử lý hiệu quả các loại truy vấn sau:

1. Thêm một đường thẳng $ax+b$ có hiệu lực trong đoạn $[l,r]$
2. Tìm điểm lớn nhất trên bất kỳ đường thẳng đang có hiệu lực nào tại vị trí $x$

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng truy vấn.

$n$ dòng tiếp theo mô tả các truy vấn. Định dạng của mỗi dòng là "1 $a$ $b$ $l$ $r$" hoặc "2 $x$".

# Kết quả

In ra câu trả lời cho mỗi truy vấn loại 2. Nếu không có đường thẳng nào có hiệu lực, in ra `NO`.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $-10^9 \le a,b \le 10^9$
* $0 \le x \le 10^5$
* $0 \le l \le r \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
6
1 1 2 1 3
2 3
2 4
1 0 4 1 5
2 3
2 4
```

Kết quả:

```cpp
5
NO
5
4
```
