# 2138 - Các đỉnh có thể đến

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một đồ thị có hướng không chu trình gồm $n$ đỉnh và $m$ cạnh. Các đỉnh được đánh số $1,2,\dots,n$.

Với mỗi đỉnh, hãy tính số lượng đỉnh mà bạn có thể đến được từ đỉnh đó (bao gồm cả chính đỉnh đó).

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và cạnh.

Sau đó là $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên phân biệt $a$ và $b$: có một cạnh từ đỉnh $a$ đến đỉnh $b$.

# Kết quả

In ra $n$ số nguyên: với mỗi đỉnh, số lượng đỉnh có thể đến được.

# Giới hạn

* $1 \le n \le 5 \cdot 10^4$
* $1 \le m \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
1 2
1 3
1 4
2 3
3 5
4 5
```

Kết quả:

```cpp
5 3 2 2 1
```
