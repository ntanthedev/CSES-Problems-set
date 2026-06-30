# 1134 - Mã Prüfer

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một *mã Prüfer* của một cây gồm $n$ đỉnh là một dãy gồm $n-2$ số nguyên xác định duy nhất cấu trúc của cây.

Mã được xây dựng như sau: Khi còn ít nhất ba đỉnh, tìm một lá có nhãn nhỏ nhất, thêm nhãn của đỉnh kề duy nhất của nó vào mã, và xóa lá đó khỏi cây.

Cho một mã Prüfer của một cây, nhiệm vụ của bạn là dựng lại cây ban đầu.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng đỉnh. Các đỉnh được đánh số $1,2,\ldots,n$.

Dòng thứ hai chứa $n-2$ số nguyên: mã Prüfer.

# Kết quả

In ra $n-1$ dòng mô tả các cạnh của cây. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh giữa đỉnh $a$ và đỉnh $b$. Bạn có thể in các cạnh theo thứ tự bất kỳ.

# Giới hạn

* $3 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
2 2 4
```

Kết quả:

```cpp
1 2
2 3
2 4
4 5
```
