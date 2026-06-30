# 3361 - Two Array Average

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho hai mảng, mỗi mảng gồm $n$ số nguyên.

Nhiệm vụ của bạn là chọn một tiền tố khác rỗng từ cả hai mảng sao cho giá trị trung bình của tất cả các số đã chọn là lớn nhất có thể.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$.

Dòng thứ hai chứa $n$ số nguyên $a\_1,a\_2,\dots,a\_n$: các số trong mảng thứ nhất.

Dòng thứ ba chứa $n$ số nguyên $b\_1,b\_2,\dots,b\_n$: các số trong mảng thứ hai.

# Kết quả

In ra hai số: kích thước của các tiền tố.

Câu trả lời của bạn được coi là đúng nếu sai số tuyệt đối hoặc tương đối so với giá trị trung bình lớn nhất không vượt quá $10^{-6}$.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le a\_i, b\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
1 5 5 2
3 1 3 1
```

Kết quả:

```cpp
3 1
```

*Giải thích*: nếu bạn chọn các tiền tố $[1,5,5]$ và $[3]$, giá trị trung bình là $(1+5+5+3)/4=3.5$, đây là giá trị trung bình lớn nhất có thể.
