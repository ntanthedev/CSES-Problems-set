# 1197 - Tìm Chu Trình

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một đồ thị có hướng, nhiệm vụ của bạn là tìm hiểu xem nó có chứa chu trình âm hay không, và cũng đưa ra một ví dụ về chu trình đó.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và cạnh. Các đỉnh được đánh số $1,2,\ldots,n$.

Sau đó, dữ liệu vào có $m$ dòng mô tả các cạnh. Mỗi dòng chứa ba số nguyên $a$, $b$, và $c$: có một cạnh từ đỉnh $a$ đến đỉnh $b$ với độ dài $c$.

# Kết quả

Nếu đồ thị chứa một chu trình âm, đầu tiên in ra "YES", sau đó là các đỉnh trong chu trình theo đúng thứ tự của chúng. Nếu có nhiều chu trình âm, bạn có thể in ra bất kỳ chu trình nào. Nếu không có chu trình âm, in ra "NO".

# Giới hạn

* $1 \le n \le 2500$
* $1 \le m \le 5000$
* $1 \le a,b \le n$
* $-10^9 \le c \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 2 1
2 4 1
3 1 1
4 1 -3
4 3 -2
```

Kết quả:

```cpp
YES
1 2 4 1
```
