# 1679 - Lịch học

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn cần hoàn thành $n$ khóa học. Có $m$ yêu cầu dạng "khóa học $a$ phải được hoàn thành trước khóa học $b$". Nhiệm vụ của bạn là tìm một thứ tự để bạn có thể hoàn thành các khóa học.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng khóa học và số lượng yêu cầu. Các khóa học được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các yêu cầu. Mỗi dòng chứa hai số nguyên $a$ và $b$: khóa học $a$ phải được hoàn thành trước khóa học $b$.

# Kết quả

In ra một thứ tự mà bạn có thể hoàn thành các khóa học. Bạn có thể in ra bất kỳ thứ tự hợp lệ nào bao gồm tất cả các khóa học.

Nếu không có lời giải, in ra "IMPOSSIBLE".

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
1 2
3 1
4 5
```

Kết quả:

```cpp
3 4 1 5 2
```
