# 1751 - Chu trình Hành tinh

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn đang chơi một trò chơi gồm $n$ hành tinh. Mỗi hành tinh có một cổng dịch chuyển đến một hành tinh khác (hoặc chính nó).

Bạn bắt đầu ở một hành tinh và sau đó đi qua các cổng dịch chuyển cho đến khi bạn đến một hành tinh mà bạn đã ghé thăm trước đó.

Nhiệm vụ của bạn là tính cho mỗi hành tinh số lần dịch chuyển sẽ thực hiện nếu bạn bắt đầu ở hành tinh đó.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng hành tinh. Các hành tinh được đánh số $1,2,\dots,n$.

Dòng thứ hai chứa $n$ số nguyên $t\_1,t\_2,\dots,t\_n$: với mỗi hành tinh, đích đến của cổng dịch chuyển. Có thể $t\_i=i$.

# Kết quả

In ra $n$ số nguyên theo yêu cầu của đề bài.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le t\_i \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
2 4 3 1 4
```

Kết quả:

```cpp
3 3 1 3 4
```
