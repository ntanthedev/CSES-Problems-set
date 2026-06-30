# 2423 - Lấp đầy bảng bằng tromino

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là lấp đầy một lưới $n \times m$ bằng các L-tromino (ba ô vuông tạo thành hình chữ L). Ví dụ, đây là một cách lấp đầy lưới $4 \times 6$:
![](da3ce928fcf66fd793d582a1a5ad7f7f9cc37e68aa2aadacee90f99bc4271692)

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng mô tả các bộ test. Mỗi dòng chứa hai số nguyên $n$ và $m$.

# Kết quả

Với mỗi bộ test, in ra YES nếu có lời giải, và NO nếu không.

Nếu có lời giải, cũng in ra $n$ dòng, mỗi dòng chứa $m$ chữ cái từ A–Z. Các ô vuông cạnh nhau phải có cùng chữ cái khi và chỉ khi chúng thuộc cùng một tromino. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le t \le 100$
* $1 \le n,m \le 100$

# Ví dụ

Dữ liệu vào:

```cpp
2
4 6
4 7
```

Kết quả:

```cpp
YES
AADDBB
ACCDEB
BCAEEC
BBAACC
NO
```
