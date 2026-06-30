# 1688 - Truy vấn công ty II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một công ty có $n$ nhân viên, tạo thành một hệ thống phân cấp dạng cây, trong đó mỗi nhân viên có một sếp, ngoại trừ tổng giám đốc.

Nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: ai là sếp chung thấp nhất của nhân viên $a$ và $b$ trong hệ thống phân cấp?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng nhân viên và số truy vấn. Các nhân viên được đánh số $1,2,\dots,n$, và nhân viên $1$ là tổng giám đốc.

Dòng tiếp theo chứa $n-1$ số nguyên $e\_2,e\_3,\dots,e\_n$: với mỗi nhân viên $2,3,\dots,n$, sếp của họ.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$: ai là sếp chung thấp nhất của nhân viên $a$ và $b$?

# Kết quả

In ra câu trả lời cho mỗi truy vấn.

# Giới hạn

* $1 \le n,q \le 2 \cdot 10^5$
* $1 \le e\_i \le i-1$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
1 1 3 3
4 5
2 5
1 4
```

Kết quả:

```cpp
3
1
1
```
