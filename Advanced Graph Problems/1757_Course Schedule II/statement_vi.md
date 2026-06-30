# 1757 - Lịch Học II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn cần hoàn thành $n$ khóa học với các yêu cầu có dạng "khóa học $a$ phải được hoàn thành trước khóa học $b$".

Bạn muốn hoàn thành khóa học $1$ càng sớm càng tốt. Nếu có nhiều cách, bạn muốn hoàn thành khóa học $2$ càng sớm càng tốt, và cứ tiếp tục như vậy.

Nhiệm vụ của bạn là xác định thứ tự hoàn thành các khóa học.

## Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng khóa học và yêu cầu. Các khóa học được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các yêu cầu. Mỗi dòng chứa hai số nguyên $a$ và $b$: khóa học $a$ phải được hoàn thành trước khóa học $b$.

Bạn có thể giả sử có ít nhất một lịch hợp lệ.

## Kết quả

In ra một dòng chứa $n$ số nguyên: thứ tự hoàn thành các khóa học.

## Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

## Ví dụ

Dữ liệu vào:

```cpp
4 2
2 1
2 3
```

Kết quả:

```cpp
2 1 3 4
```
