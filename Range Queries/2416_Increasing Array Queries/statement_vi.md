# 2416 - Truy vấn mảng tăng dần

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một mảng gồm $n$ số nguyên. Các phần tử của mảng được đánh chỉ số $1,2,\dots,n$.

Bạn có thể sửa đổi mảng bằng thao tác sau: chọn một phần tử của mảng và tăng giá trị của nó lên một.

Nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: khi xét một đoạn con từ vị trí $a$ đến vị trí $b$, số thao tác tối thiểu cần thực hiện để đoạn con đó trở thành mảng tăng dần là bao nhiêu?

Một mảng được gọi là tăng dần nếu mỗi phần tử lớn hơn hoặc bằng phần tử đứng trước nó.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: kích thước của mảng và số lượng truy vấn.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$: vị trí bắt đầu và kết thúc của một đoạn con.

# Kết quả

Với mỗi truy vấn, in ra số thao tác tối thiểu.

# Giới hạn

* $1 \le n,q \le 2\cdot10^5$
* $1 \le x\_i \le 10^9$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
2 10 4 2 5
3 5
2 2
1 4
```

Kết quả:

```cpp
2
0
14
```
