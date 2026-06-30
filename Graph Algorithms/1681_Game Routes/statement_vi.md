# 1681 - Đường đi trong trò chơi

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một trò chơi có $n$ màn chơi, được kết nối bởi $m$ đường dịch chuyển, và nhiệm vụ của bạn là đi từ màn $1$ đến màn $n$. Trò chơi được thiết kế sao cho không có chu trình có hướng nào trong đồ thị cơ bản. Hỏi có bao nhiêu cách để hoàn thành trò chơi?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng màn chơi và số lượng đường dịch chuyển. Các màn chơi được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các đường dịch chuyển. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một đường dịch chuyển từ màn $a$ đến màn $b$.

# Kết quả

In ra một số nguyên: số cách bạn có thể hoàn thành trò chơi. Vì kết quả có thể rất lớn, hãy in ra kết quả theo modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 2
2 4
1 3
3 4
1 4
```

Kết quả:

```cpp
3
```
