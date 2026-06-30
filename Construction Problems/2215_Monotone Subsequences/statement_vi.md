# 2215 - Dãy con đơn điệu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tạo một hoán vị của các số $1,2,\dots,n$ có độ dài dãy con đơn điệu dài nhất bằng chính xác $k$ phần tử.

Một dãy con đơn điệu là dãy con tăng hoặc giảm. Ví dụ, một số dãy con đơn điệu trong $[2,1,4,5,3]$ là $[2,4,5]$ và $[4,3]$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng. Mỗi dòng chứa hai số nguyên $n$ và $k$.

# Kết quả

Với mỗi bộ test, in ra một dòng chứa hoán vị. Bạn có thể in ra bất kỳ phương án hợp lệ nào. Nếu không có lời giải, in ra `IMPOSSIBLE`.

# Giới hạn

* $1 \le t \le 1000$
* $1 \le k \le n \le 100$

# Ví dụ

Dữ liệu vào:

```cpp
3
5 3
5 2
7 7
```

Kết quả:

```cpp
2 1 4 5 3
IMPOSSIBLE
1 2 3 4 5 6 7
```
