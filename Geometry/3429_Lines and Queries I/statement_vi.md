# 3429 - Đường thẳng và truy vấn I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là xử lý hiệu quả các loại truy vấn sau:

1. Thêm một đường thẳng $ax+b$
2. Tìm điểm lớn nhất trên bất kỳ đường thẳng nào tại vị trí $x$

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng truy vấn.

$n$ dòng tiếp theo mô tả các truy vấn. Định dạng của mỗi dòng là "1 $a$ $b$" hoặc "2 $x$".

Bạn có thể giả sử truy vấn đầu tiên là loại 1.

# Kết quả

In ra câu trả lời cho mỗi truy vấn loại 2.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $-10^9 \le a,b \le 10^9$
* $0 \le x \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
6
1 1 2
2 1
2 3
1 0 4
2 1
2 3
```

Kết quả:

```cpp
3
5
4
5
```
