# 1702 - Duyệt Cây

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có ba cách phổ biến để duyệt các đỉnh của một cây nhị phân:

* *Tiền thứ tự (Preorder)*: Duyệt gốc trước, sau đó duyệt cây con bên trái, và cuối cùng duyệt cây con bên phải.
* *Trung thứ tự (Inorder)*: Duyệt cây con bên trái trước, sau đó duyệt gốc, và cuối cùng duyệt cây con bên phải.
* *Hậu thứ tự (Postorder)*: Duyệt cây con bên trái trước, sau đó duyệt cây con bên phải, và cuối cùng duyệt gốc.

Cho một cây nhị phân gồm $n$ đỉnh với các nhãn phân biệt. Bạn được cho thứ tự duyệt tiền thứ tự và trung thứ tự của cây, nhiệm vụ của bạn là xác định thứ tự duyệt hậu thứ tự của cây.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng đỉnh. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó là hai dòng mô tả thứ tự duyệt tiền thứ tự và trung thứ tự của cây. Cả hai dòng đều gồm $n$ số nguyên.

Bạn có thể giả định rằng dữ liệu vào tương ứng với một cây nhị phân.

# Kết quả

In ra thứ tự duyệt hậu thứ tự của cây.

# Giới hạn

* $1 \le n \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
5
5 3 2 1 4
3 5 1 2 4
```

Kết quả:

```cpp
3 1 4 2 5
```
