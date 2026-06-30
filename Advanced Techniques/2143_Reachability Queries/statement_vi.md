# 2143 - Truy vấn khả năng đến

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một đồ thị có hướng gồm $n$ đỉnh và $m$ cạnh. Các cạnh được đánh số $1,2,\dots,n$.

Nhiệm vụ của bạn là trả lời $q$ truy vấn dạng "có thể đến đỉnh $b$ từ đỉnh $a$ không?"

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $q$: số lượng đỉnh, cạnh và truy vấn.

Sau đó là $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên phân biệt $a$ và $b$: có một cạnh từ đỉnh $a$ đến đỉnh $b$.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng gồm hai số nguyên $a$ và $b$: "có thể đến đỉnh $b$ từ đỉnh $a$ không?"

# Kết quả

In ra câu trả lời cho mỗi truy vấn: "YES" hoặc "NO".

# Giới hạn

* $1 \le n \le 5 \cdot 10^4$
* $1 \le m,q \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
4 4 3
1 2
2 3
3 1
4 3
1 3
1 4
4 1
```

Kết quả:

```cpp
YES
NO
YES
```
