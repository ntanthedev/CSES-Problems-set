# 2079 - Tìm tâm

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây gồm $n$ đỉnh, nhiệm vụ của bạn là tìm một *tâm*, tức là một đỉnh sao cho khi nó được chọn làm gốc của cây, mỗi cây con có tối đa $\lfloor n/2 \rfloor$ đỉnh.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng đỉnh. Các đỉnh được đánh số $1,2,\ldots,n$.

Sau đó là $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối giữa đỉnh $a$ và đỉnh $b$.

# Kết quả

In ra một số nguyên: một đỉnh là tâm. Nếu có nhiều khả năng, bạn có thể chọn bất kỳ đỉnh nào trong số đó.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 2
2 3
3 4
3 5
```

Kết quả:

```cpp
3
```
