# 1130 - Tree Matching

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây gồm $n$ đỉnh.

Một *bộ ghép* (matching) là một tập hợp các cạnh sao cho mỗi đỉnh là đầu mút của nhiều nhất một cạnh. Hãy tìm số lượng cạnh lớn nhất trong một bộ ghép?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng đỉnh. Các đỉnh được đánh số $1,2,\ldots,n$.

Sau đó là $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối giữa đỉnh $a$ và $b$.

# Kết quả

In ra một số nguyên: số cặp lớn nhất.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 2
1 3
3 4
3 5
```

Kết quả:

```cpp
2
```

Giải thích: Một bộ ghép khả dụng là $(1,2)$ và $(3,4)$.
