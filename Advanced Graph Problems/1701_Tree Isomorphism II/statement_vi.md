# 1701 - Đẳng Cấu Cây II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho hai cây (không có gốc), nhiệm vụ của bạn là xác định xem chúng có *đẳng cấu* hay không, tức là có thể vẽ chúng sao cho trông giống hệt nhau.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test. Sau đó, có $t$ bộ test được mô tả như sau:

Dòng đầu tiên chứa một số nguyên $n$: số lượng đỉnh trong cả hai cây. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó, có $n-1$ dòng mô tả các cạnh của cây thứ nhất, và cuối cùng là $n-1$ dòng mô tả các cạnh của cây thứ hai.

# Kết quả

Với mỗi bộ test, in ra "YES" nếu hai cây đẳng cấu, ngược lại in "NO".

# Giới hạn

* $1 \le t \le 1000$
* $2 \le n \le 10^5$
* tổng tất cả các giá trị $n$ không vượt quá $10^5$

# Ví dụ

Dữ liệu vào:

```cpp
2
3
1 2
2 3
1 2
1 3
3
1 2
2 3
1 3
3 2
```

Kết quả:

```cpp
YES
YES
```
