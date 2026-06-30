# 3398 - Vòng Hoán Vị

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng đã được sắp xếp $[1,2,\dots,n]$ và một hoán vị $p\_1,p\_2,\dots,p\_n$. Ở mỗi vòng, tất cả phần tử di chuyển theo hoán vị: phần tử ở vị trí $i$ di chuyển đến vị trí $p\_i$.

Sau bao nhiêu vòng thì mảng được sắp xếp trở lại lần đầu tiên?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$.

Dòng tiếp theo chứa $n$ số nguyên $p\_1,p\_2,\dots,p\_n$.

# Kết quả

In ra số vòng cần tìm modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
8
5 3 2 6 4 1 8 7
```

Kết quả:

```cpp
4
```

*Giải thích*: Mảng thay đổi qua các vòng như sau:

* Vòng 1: $[6,3,2,5,1,4,8,7]$
* Vòng 2: $[4,2,3,1,6,5,7,8]$
* Vòng 3: $[5,3,2,6,4,1,8,7]$
* Vòng 4: $[1,2,3,4,5,6,7,8]$
