# 3294 - Subarray Sum Constraints

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là xây dựng một mảng $x\_1,x\_2,\dots,x\_n$ gồm $n$ số nguyên.

Mảng phải thỏa mãn $m$ ràng buộc dạng $(l,r,s)$: tổng $x\_l + x\_{l+1} + \dots + x\_r$ phải bằng $s$.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: kích thước mảng và số lượng ràng buộc.

$m$ dòng tiếp theo, mỗi dòng chứa ba số nguyên $l$, $r$ và $s$: mô tả các ràng buộc.

# Kết quả

Nếu tồn tại nghiệm, in ra `YES` trên dòng đầu tiên.

Trên dòng thứ hai, in ra $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: nội dung của mảng. Tất cả các phần tử của mảng phải thỏa mãn $-10^{15} \le x\_i \le 10^{15}$ và mảng phải thỏa mãn tất cả các ràng buộc đã cho. Bạn có thể in ra bất kỳ nghiệm hợp lệ nào.

Nếu không tồn tại nghiệm, chỉ in ra `NO`.

# Giới hạn

* $1 \le n \le 5000$
* $0 \le m \le 2 \cdot 10^5$
* $1 \le l \le r \le n$
* $-10^9 \le s \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
1 3 3
3 5 3
4 4 -1
```

Kết quả:

```cpp
YES
0 2 1 -1 3
```
