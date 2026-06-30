# 2427 - Trò chơi Di chuyển Cặp Chữ cái

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $2n$ hộp xếp thành một dòng. Hai hộp liền kề nhau là trống, và tất cả các hộp khác đều chứa một chữ cái "A" hoặc "B". Cả hai chữ cái đều xuất hiện trong đúng $n-1$ hộp.

Nhiệm vụ của bạn là di chuyển các chữ cái sao cho tất cả chữ cái "A" đều đứng trước bất kỳ chữ cái "B" nào. Ở mỗi lượt, bạn có thể chọn hai hộp liền kề bất kỳ có chứa chữ cái và di chuyển các chữ cái đó đến hai hộp trống liền kề, giữ nguyên thứ tự của chúng.

Có thể chứng minh rằng hoặc tồn tại một lời giải gồm tối đa $10n$ lượt, hoặc không có lời giải.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: có $2n$ hộp.

Dòng thứ hai chứa một xâu gồm $2n$ ký tự mô tả vị trí ban đầu. Mỗi ký tự là "A", "B" hoặc "." (hộp trống).

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượt di chuyển. Sau đó, in ra $k$ dòng mô tả các bước di chuyển. Bạn có thể in ra bất kỳ lời giải nào, miễn là $k \le 1000$.

Nếu không có lời giải, chỉ in ra "-1".

# Giới hạn

* $1 \le n \le 100$

# Ví dụ 1

Dữ liệu vào:

```cpp
3
AB..BA
```

Kết quả:

```cpp
2
ABBA..
A..ABB
```

# Ví dụ 2

Dữ liệu vào:

```cpp
3
ABAB..
```

Kết quả:

```cpp
-1
```
