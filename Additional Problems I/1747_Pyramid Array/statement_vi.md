# 1747 - Mảng Hình Chóp

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một mảng gồm $n$ số nguyên phân biệt. Ở mỗi bước, bạn có thể hoán đổi hai giá trị liền kề bất kỳ.

Bạn muốn biến đổi mảng thành một *mảng hình chóp*. Điều này có nghĩa là mảng cuối cùng phải tăng dần rồi giảm dần. Mảng cuối cùng cũng có thể chỉ tăng dần hoặc chỉ giảm dần.

Số bước di chuyển ít nhất cần thực hiện là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Dòng tiếp theo chứa $n$ số nguyên phân biệt $x\_1, x\_2, \dots, x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: số bước di chuyển ít nhất.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
2 1 5 3
```

Kết quả:

```cpp
1
```

Giải thích: Bạn có thể hoán đổi hai giá trị đầu tiên để tạo thành mảng hình chóp $[1,2,5,3]$.
