# 1630 - Công Việc và Hạn Chót

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn có $n$ công việc cần xử lý. Mỗi công việc có một thời lượng và một hạn chót, và bạn sẽ xử lý các công việc theo một thứ tự nào đó, lần lượt từng cái một. Phần thưởng cho một công việc là $d-f$ trong đó $d$ là hạn chót và $f$ là thời điểm bạn hoàn thành. (Thời điểm bắt đầu là $0$, và bạn phải xử lý tất cả các công việc ngay cả khi một công việc có thể mang lại phần thưởng âm.)

Hỏi phần thưởng tối đa bạn có thể đạt được nếu hành động tối ưu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng công việc.

Sau đó là $n$ dòng mô tả các công việc. Mỗi dòng chứa hai số nguyên $a$ và $d$: thời lượng và hạn chót của công việc.

# Kết quả

In ra một số nguyên: phần thưởng tối đa.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a,d \le 10^6$

# Ví dụ

Input:

```cpp
3
6 10
8 15
5 12
```

Output:

```cpp
2
```
