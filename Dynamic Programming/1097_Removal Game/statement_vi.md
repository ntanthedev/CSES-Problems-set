# 1097 - Removal Game

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một danh sách gồm $n$ số và hai người chơi thay phiên nhau di chuyển. Ở mỗi lượt, một người chơi bỏ đi số đầu tiên hoặc số cuối cùng khỏi danh sách, và số điểm của họ tăng lên bằng số đó. Cả hai người chơi đều cố gắng tối đa hóa điểm số của mình.

Hỏi người chơi đầu tiên có thể đạt được điểm số tối đa là bao nhiêu khi cả hai đều chơi tối ưu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của danh sách.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của danh sách.

# Kết quả

In ra điểm số tối đa của người chơi đầu tiên.

# Giới hạn

* $1 \le n \le 5000$
* $-10^9 \le x\_i \le 10^9$

# Ví dụ

Input:

```cpp
4
4 5 1 3
```

Output:

```cpp
8
```
