# 1684 - Chiếc bánh pizza không lồ

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Gia đình Uolevi sắp đặt một chiếc bánh pizza lớn và cùng nhau ăn nó. Tổng cộng có $n$ thành viên trong gia đình tham gia đặt hàng và có $m$ loại topping khả dụng. Bánh pizza có thể có bất kỳ số lượng topping nào.

Mỗi thành viên trong gia đình đưa ra hai nguyện vọng liên quan đến topping của bánh pizza. Các nguyện vọng có dạng "topping $x$ là tốt/xấu". Nhiệm vụ của bạn là chọn các topping sao cho ít nhất một nguyện vọng của mỗi người trở thành hiện thực (topping tốt được cho vào bánh pizza hoặc topping xấu không được cho vào).

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành viên trong gia đình và số loại topping. Các topping được đánh số $1,2,\dots,m$.

Sau đó, có $n$ dòng mô tả các nguyện vọng. Mỗi dòng chứa hai nguyện vọng có dạng "+ $x$" (topping $x$ là tốt) hoặc "- $x$" (topping $x$ là xấu).

# Kết quả

In ra một dòng với $m$ ký hiệu: cho mỗi topping "+" nếu nó được cho vào và "-" nếu nó không được cho vào. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

Nếu không có phương án hợp lệ, in ra "IMPOSSIBLE".

# Giới hạn

* $1 \le n,m \le 10^5$
* $1 \le x \le m$

# Ví dụ

Dữ liệu vào:

```cpp
3 5
+ 1 + 2
- 1 + 3
+ 4 - 2
```

Kết quả:

```cpp
- + + + -
```
