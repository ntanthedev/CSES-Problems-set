# 2426 - Programmers and Artists

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một công ty muốn tuyển $a$ lập trình viên và $b$ nghệ sĩ.

Có tổng cộng $n$ ứng viên, và mỗi ứng viên có thể trở thành lập trình viên hoặc nghệ sĩ. Bạn biết kỹ năng lập trình và kỹ năng nghệ thuật của từng ứng viên.

Nhiệm vụ của bạn là chọn những nhân viên mới sao cho tổng kỹ năng của họ là lớn nhất.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $a$, $b$ và $n$: số lượng lập trình viên và nghệ sĩ cần tuyển, và tổng số ứng viên.

Sau đó là $n$ dòng mô tả các ứng viên. Mỗi dòng chứa hai số nguyên $x$ và $y$: kỹ năng lập trình và kỹ năng nghệ thuật của ứng viên.

# Kết quả

In ra một số nguyên: tổng kỹ năng lớn nhất.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $0 \le a,b \le n$
* $a+b \le n$
* $1 \le x,y \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
2 1 4
3 7
9 8
1 5
4 2
```

Kết quả:

```cpp
20
```

**Giải thích:** Một phương án tối ưu là tuyển hai lập trình viên với kỹ năng $9$ và $4$ cùng một nghệ sĩ với kỹ năng $7$. Tổng kỹ năng là $9+4+7=20$.
