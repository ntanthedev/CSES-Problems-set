# 1620 - Máy Móc Trong Nhà Máy

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một nhà máy có $n$ máy móc có thể được sử dụng để sản xuất sản phẩm. Mục tiêu của bạn là sản xuất tổng cộng $t$ sản phẩm.

Với mỗi máy, bạn biết số giây cần thiết để sản xuất một sản phẩm. Các máy có thể hoạt động đồng thời, và bạn có thể tự do quyết định lịch trình của chúng.

Hỏi thời gian ngắn nhất cần thiết để sản xuất $t$ sản phẩm là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $t$: số lượng máy móc và số lượng sản phẩm.

Dòng tiếp theo chứa $n$ số nguyên $k\_1,k\_2,\dots,k\_n$: thời gian cần thiết để sản xuất một sản phẩm bằng mỗi máy.

# Kết quả

In ra một số nguyên: thời gian tối thiểu cần thiết để sản xuất $t$ sản phẩm.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le t \le 10^9$
* $1 \le k\_i \le 10^9$

# Ví dụ

Input:

```cpp
3 7
3 2 5
```

Output:

```cpp
8
```

Giải thích: Máy 1 sản xuất hai sản phẩm, máy 2 sản xuất bốn sản phẩm và máy 3 sản xuất một sản phẩm.
