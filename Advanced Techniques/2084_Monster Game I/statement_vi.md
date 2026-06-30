# 2084 - Monster Game I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn đang chơi một trò chơi gồm $n$ màn. Mỗi màn có một con quái vật. Ở các màn $1,2,\dots,n-1$, bạn có thể tiêu diệt hoặc bỏ qua con quái vật. Tuy nhiên, ở màn $n$ bạn phải tiêu diệt con quái vật cuối cùng để chiến thắng trò chơi.

Tiêu diệt một con quái vật tốn $sf$ thời gian, trong đó $s$ là sức mạnh của quái vật và $f$ là hệ số kỹ năng của bạn (hệ số kỹ năng càng thấp càng tốt). Sau khi tiêu diệt một con quái vật, bạn nhận được một hệ số kỹ năng mới. Tổng thời gian tối thiểu để bạn chiến thắng trò chơi là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $x$: số lượng màn và hệ số kỹ năng ban đầu của bạn.

Dòng thứ hai chứa $n$ số nguyên $s\_1,s\_2,\dots,s\_n$: sức mạnh của mỗi con quái vật.

Dòng thứ ba chứa $n$ số nguyên $f\_1,f\_2,\dots,f\_n$: hệ số kỹ năng mới của bạn sau khi tiêu diệt một con quái vật.

# Kết quả

In ra một số nguyên: tổng thời gian tối thiểu để chiến thắng trò chơi.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x \le 10^6$
* $1 \le s\_1 \le s\_2 \le \dots \le s\_n \le 10^6$
* $x \ge f\_1 \ge f\_2 \ge \dots \ge f\_n \ge 1$

# Ví dụ

Dữ liệu vào:

```cpp
5 100
20 30 30 50 90
90 60 20 20 10
```

Kết quả:

```cpp
4800
```

Giải thích: Cách chơi tối ưu là tiêu diệt quái vật thứ ba và thứ năm.
