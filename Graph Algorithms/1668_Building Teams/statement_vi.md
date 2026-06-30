# 1668 - Building Teams

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ học sinh trong lớp của Uolevi và $m$ mối quan hệ bạn bè giữa chúng. Nhiệm vụ của bạn là chia các học sinh thành hai đội sao cho không có hai học sinh nào trong cùng một đội là bạn bè. Bạn có thể tự do chọn kích thước của các đội.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng học sinh và mối quan hệ bạn bè. Các học sinh được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các mối quan hệ bạn bè. Mỗi dòng chứa hai số nguyên $a$ và $b$: học sinh $a$ và $b$ là bạn bè.

Mỗi mối quan hệ bạn bè là giữa hai học sinh khác nhau. Bạn có thể giả sử có nhiều nhất một mối quan hệ bạn bè giữa hai học sinh bất kỳ.

# Kết quả

In ra một ví dụ về cách xây dựng các đội. Với mỗi học sinh, in "1" hoặc "2" tùy thuộc vào đội mà học sinh đó được gán. Bạn có thể in bất kỳ phương án hợp lệ nào.

Nếu không có lời giải, in "IMPOSSIBLE".

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Input:

```cpp
5 3
1 2
1 3
4 5
```

Output:

```cpp
1 2 2 1 2
```
