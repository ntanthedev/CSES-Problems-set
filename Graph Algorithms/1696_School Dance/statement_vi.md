# 1696 - Khiêu vũ Trường học

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một trường học có $n$ nam sinh và $m$ nữ sinh. Tuần sau trường sẽ tổ chức một buổi khiêu vũ. Một cặp khiêu vũ gồm một nam và một nữ, và có $k$ cặp tiềm năng.

Nhiệm vụ của bạn là tìm ra số lượng cặp khiêu vũ tối đa và chỉ ra cách đạt được con số này.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $k$: số lượng nam sinh, nữ sinh và các cặp tiềm năng. Các nam sinh được đánh số $1,2,\dots,n$, và các nữ sinh được đánh số $1,2,\dots,m$.

Sau đó, có $k$ dòng mô tả các cặp tiềm năng. Mỗi dòng chứa hai số nguyên $a$ và $b$: nam $a$ và nữ $b$ sẵn sàng khiêu vũ cùng nhau.

# Kết quả

Đầu tiên in ra một số nguyên $r$: số lượng cặp khiêu vũ tối đa. Sau đó, in ra $r$ dòng mô tả các cặp. Bạn có thể in ra bất kỳ nghiệm đúng nào.

# Giới hạn

* $1 \le n,m \le 500$
* $1 \le k \le 1000$
* $1 \le a \le n$
* $1 \le b \le m$

# Ví dụ

Dữ liệu vào:

```cpp
3 2 4
1 1
1 2
2 1
3 1
```

Kết quả:

```cpp
2
1 2
3 1
```
