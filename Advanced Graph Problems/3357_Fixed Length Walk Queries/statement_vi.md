# 3357 - Truy Vấn Đường Đi Độ Dài Cố Định

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị vô hướng gồm $n$ đỉnh và $m$ cạnh. Đồ thị là đơn và liên thông.

Bạn bắt đầu tại một đỉnh cụ thể, và ở mỗi lượt bạn phải di chuyển qua một cạnh đến một đỉnh khác.

Nhiệm vụ của bạn là trả lời $q$ truy vấn dạng: "có thể bắt đầu từ đỉnh $a$ và kết thúc tại đỉnh $b$ sau đúng $x$ lượt hay không?"

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $q$:
số lượng đỉnh, cạnh và truy vấn. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh giữa hai đỉnh $a$ và $b$.

Cuối cùng, có $q$ dòng, mỗi dòng mô tả một truy vấn.
Mỗi dòng chứa ba số nguyên $a$, $b$ và $x$.

# Kết quả

Với mỗi truy vấn, in ra câu trả lời (`YES` hoặc `NO`) trên một dòng riêng biệt.

# Giới hạn

* $2 \le n \le 2500$
* $1 \le m \le 5000$
* $1 \le q \le 10^5$
* $0 \le x \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 5 6
1 2
2 3
1 3
2 4
3 4
1 2 2
1 4 1
1 4 5
2 2 1
2 2 2
3 4 8
```

Kết quả:

```cpp
YES
NO
YES
NO
YES
YES
```

*Giải thích*:

* Ở truy vấn 1, một đường đi khả thi là $1 \rightarrow 3 \rightarrow 2$.
* Ở truy vấn 3, một đường đi khả thi là $1 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 4$.
* Ở truy vấn 6, một đường đi khả thi là $3 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 4$.
