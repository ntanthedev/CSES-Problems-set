# 1194 - Quái Vật

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn và một số con quái vật đang ở trong một mê cung. Khi bạn bước một bước theo một hướng nào đó trong mê cung, mỗi con quái vật cũng có thể đồng thời bước một bước. Mục tiêu của bạn là đến được một trong các ô biên mà không bao giờ ở chung ô với quái vật.

Nhiệm vụ của bạn là tìm hiểu xem mục tiêu có khả thi hay không, và nếu có, hãy in ra một đường đi mà bạn có thể đi theo. Kế hoạch của bạn phải hoạt động trong mọi tình huống; ngay cả khi lũ quái vật biết trước đường đi của bạn.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: chiều cao và chiều rộng của bản đồ.

Sau đó là $n$ dòng, mỗi dòng gồm $m$ ký tự mô tả bản đồ. Mỗi ký tự là `.` (sàn), `#` (tường), `A` (điểm xuất phát) hoặc `M` (quái vật). Có đúng một ký tự `A` trong dữ liệu vào.

# Kết quả

Đầu tiên in ra "YES" nếu mục tiêu khả thi, và "NO" nếu không.

Nếu mục tiêu khả thi, cũng in ra một ví dụ về đường đi hợp lệ (độ dài đường đi và mô tả của nó bằng các ký tự `D`, `U`, `L` và `R`). Bạn có thể in ra bất kỳ đường đi nào, miễn là độ dài của nó không vượt quá $n \cdot m$ bước.

# Giới hạn

* $1 \le n,m \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
5 8
########
#M..A..#
#.#.M#.#
#M#..#..
#.######
```

Kết quả:

```cpp
YES
5
RRDDR
```
