# 1749 - Xóa phần tử khỏi danh sách

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một danh sách gồm $n$ số nguyên. Nhiệm vụ của bạn là xóa các phần tử khỏi danh sách tại các vị trí cho trước và báo cáo các phần tử đã bị xóa.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước ban đầu của danh sách. Trong quá trình xử lý, các phần tử được đánh số $1,2,\dots,k$ với $k$ là kích thước hiện tại của danh sách.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của danh sách.

Dòng cuối cùng chứa $n$ số nguyên $p\_1,p\_2,\dots,p\_n$: các vị trí của các phần tử cần xóa.

# Kết quả

In ra các phần tử theo thứ tự chúng bị xóa.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$
* $1 \le p\_i \le n-i+1$

# Ví dụ

Dữ liệu vào:

```cpp
5
2 6 1 4 2
3 1 3 1 1
```

Kết quả:

```cpp
1 2 2 6 4
```

Giải thích: Nội dung của danh sách lần lượt là $[2,6,1,4,2]$, $[2,6,4,2]$, $[6,4,2]$, $[6,4]$, $[4]$ và $[]$.
