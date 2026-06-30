# 2164 - Truy vấn Josephus

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một trò chơi có $n$ đứa trẻ (đánh số $1,2,\dots,n$) đứng thành vòng tròn.
Trong trò chơi, cứ mỗi đứa trẻ thứ hai sẽ bị loại khỏi vòng tròn, cho đến khi
không còn đứa trẻ nào.

Nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: "khi có $n$ đứa trẻ, đứa thứ $k$ bị
loại là ai?"

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $q$: số lượng truy vấn.

Sau đó là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $n$ và $k$:
số lượng đứa trẻ và vị trí của đứa trẻ cần tìm.

# Kết quả

In ra $q$ số nguyên: đáp án cho mỗi truy vấn.

# Giới hạn

* $1 \le q \le 10^5$
* $1 \le k \le n \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
7 1
7 3
2 2
1337 1313
```

Kết quả:

```cpp
2
6
1
1107
```
