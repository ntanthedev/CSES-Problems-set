# 1665 - Coding Company

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Công ty của bạn có $n$ lập trình viên, và mỗi người có trình độ kỹ năng từ $0$ đến $100$. Nhiệm vụ của bạn là chia các lập trình viên thành các đội làm việc cùng nhau.

Dựa trên kinh nghiệm của bạn, bạn biết rằng các đội làm việc hiệu quả khi trình độ kỹ năng của các lập trình viên xấp xỉ nhau. Vì lý do này, chi phí phạt khi tạo một đội là chênh lệch trình độ giữa lập trình viên giỏi nhất và lập trình viên kém nhất.

Có bao nhiêu cách chia các lập trình viên thành các đội sao cho tổng chi phí phạt không vượt quá $x$?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $x$: số lượng lập trình viên và tổng chi phí phạt tối đa cho phép.

Dòng tiếp theo chứa $n$ số nguyên $t\_1,t\_2,\dots,t\_n$: trình độ kỹ năng của mỗi lập trình viên.

# Kết quả

In ra một số nguyên: số cách chia hợp lệ modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 100$
* $0 \le x \le 5000$
* $0 \le t\_i \le 100$

# Ví dụ

Dữ liệu vào:

```cpp
3 2
2 5 3
```

Kết quả:

```cpp
3
```
