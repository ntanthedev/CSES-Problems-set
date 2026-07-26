#include <bits/stdc++.h>
using namespace std;

struct plan {
    int rep_right;
    int rep_down;
    char kind; // 0: 2x3, 1: 3x2, 2: 9x5, 3: 5x9
    char full_bottom = 0;
};

const char d95[9][5] = {
    {0, 0, 3, 3, 2}, {0, 4, 3, 2, 2}, {1, 4, 4, 0, 0}, {1, 1, 3, 3, 0},
    {2, 2, 3, 1, 1}, {0, 2, 4, 4, 1}, {0, 0, 4, 2, 2}, {3, 3, 2, 1, 2},
    {3, 2, 2, 1, 1},
};

struct fill_tr {
    vector<string> res;
    int rows, cols;
    plan* has_95 = nullptr;
    vector<plan> trom, right;

    explicit fill_tr(int n, int m) : rows(n), cols(m) {}

    int check2x3(int r, int c, vector<plan>& t) {
        if (!(r & 1) && !(c % 3)) {
            t.push_back({c / 3, r >> 1, 0});
            return 1;
        }
        if (!(c & 1) && !(r % 3)) {
            t.push_back({c >> 1, r / 3, 1});
            return 1;
        }
        if (!(r % 6) && !((c - 2) % 3)) {
            t.push_back({1, r / 3, 0});
            t.push_back({(c - 2) / 3, r >> 1, 1});
            return 1;
        }
        if (!(c % 6) && !((r - 2) % 3)) {
            t.push_back({c / 3, 1, 0});
            t.push_back({c >> 1, (r - 2) / 3, 1});
            return 1;
        }
        if (!(c % 6) && r > 3 && !((r - 3) & 1)) {
            t.push_back({c >> 1, 1, 1});
            t.push_back({c / 3, (r - 3) >> 1, 0});
            return 1;
        }
        if (!(r % 6) && c > 3 && !((c - 3) & 1)) {
            t.push_back({1, r >> 1, 0});
            t.push_back({(c - 3) >> 1, r / 3, 1});
            return 1;
        }
        return 0;
    }

    int possible() {
        long long square = 1LL * rows * cols;
        if (square % 3) return 0;
        if (check2x3(rows, cols, trom)) return 1;
        if (square < 45) return 0;
        if (rows >= 9 && !(rows % 9) && cols >= 5 && !(cols % 5)) {
            trom.push_back({cols / 5, rows / 9, 2});
            return 1;
        }
        if (rows >= 5 && !(rows % 5) && cols >= 9 && !(cols % 9)) {
            trom.push_back({cols / 9, rows / 5, 3});
            return 1;
        }

        auto try95 = [&](int r, int c) {
            vector<plan> tb, tr;
            if (rows >= 9 && cols >= 5) {
                r = rows - 9;
                c = cols - 5;
                if (!r && check2x3(rows, c, tr)) {
                    has_95 = new plan{1, 1, 2};
                    right = move(tr);
                    return true;
                }
                if (!c && check2x3(r, cols, tb)) {
                    has_95 = new plan{1, 1, 2, 1};
                    trom = move(tb);
                    return true;
                }
                tb.clear();
                tr.clear();
                if (check2x3(r, cols, tb) && check2x3(9, c, tr)) {
                    has_95 = new plan{1, 1, 2, 1};
                    trom = move(tb);
                    right = move(tr);
                    return true;
                }
                tb.clear();
                tr.clear();
                if (check2x3(rows, c, tb) && check2x3(r, 5, tr)) {
                    has_95 = new plan{1, 1, 2, 0};
                    trom = move(tb);
                    right = move(tr);
                    return true;
                }
            }
            tb.clear();
            tr.clear();
            if (rows >= 5 && cols >= 9) {
                r = rows - 5;
                c = cols - 9;
                if (!r && check2x3(rows, c, tr)) {
                    has_95 = new plan{1, 1, 3};
                    right = move(tr);
                    return true;
                }
                if (!c && check2x3(r, cols, tb)) {
                    has_95 = new plan{1, 1, 3, 1};
                    trom = move(tb);
                    return true;
                }
                if (check2x3(r, cols, tb) && check2x3(5, c, tr)) {
                    has_95 = new plan{1, 1, 3, 1};
                    trom = move(tb);
                    right = move(tr);
                    return true;
                }
                tb.clear();
                tr.clear();
                if (check2x3(rows, c, tb) && check2x3(r, 9, tr)) {
                    has_95 = new plan{1, 1, 3, 0};
                    trom = move(tb);
                    right = move(tr);
                    return true;
                }
            }
            return false;
        };

        return try95(0, 0) ? 1 : 0;
    }

    void draw9x5(int y, int x) {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 5; j++)
                res[y + i][x + j] = 'A' + d95[i][j];
    }

    void draw5x9(int y, int x) {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 9; j++)
                res[y + i][x + j] = 'A' + d95[j][i];
    }

    void draw2x3(int y, int x, int color) {
        char A = 'A' + 2 * color;
        char B = A + 1;
        res[y][x] = A;
        res[y][x + 1] = A;
        res[y + 1][x] = A;
        res[y][x + 2] = B;
        res[y + 1][x + 1] = B;
        res[y + 1][x + 2] = B;
    }

    void draw3x2(int y, int x, int color) {
        char A = 'A' + 2 * color;
        char B = A + 1;
        res[y][x] = A;
        res[y + 1][x] = A;
        res[y][x + 1] = A;
        res[y + 1][x + 1] = B;
        res[y + 2][x] = B;
        res[y + 2][x + 1] = B;
    }

    void draw_single(int& y, int& x, int& color, plan& p) {
        int old_x = x;
        if (p.kind == 2 || p.kind == 3) {
            for (int i = 0; i < p.rep_down; i++) {
                x = old_x;
                for (int j = 0; j < p.rep_right; ++j, x += (p.kind == 2) ? 5 : 9)
                    if (p.kind == 2) draw9x5(y, x);
                    else draw5x9(y, x);
                y += (p.kind == 2) ? 9 : 5;
            }
        } else {
            while (y < rows) {
                for (x = old_x; x < cols; x += p.kind ? 2 : 3) {
                    if (p.kind) draw3x2(y, x, color);
                    else draw2x3(y, x, color);
                    color ^= 1;
                }
                y += p.kind ? 3 : 2;
                color ^= 2;
            }
        }
    }

    void draw_list(int& y, int& x, int& color, vector<plan>& t) {
        if (t.size() == 1) {
            draw_single(y, x, color, t[0]);
            return;
        }
        int cdiff = 0, old_color = color;
        int old_y = y, old_x = x;
        plan p = t[0];
        auto draw_cell = [&](int yy, int xx) {
            if (p.kind) draw3x2(yy, xx, color);
            else draw2x3(yy, xx, color);
            cdiff ^= 1;
            color = old_color + cdiff;
        };
        if (p.rep_right == 1) {
            for (y = old_y; y < rows; y += p.kind ? 3 : 2) draw_cell(y, x);
            x += p.kind ? 2 : 3;
            cdiff ^= 2;
            old_color += 2;
            color = old_color + cdiff;
            p = t[1];
            for (y = old_y; y < rows; y += p.kind ? 3 : 2) {
                for (int i = x; i < cols; i += p.kind ? 2 : 3) draw_cell(y, i);
                cdiff ^= 2;
                color = old_color + cdiff;
            }
        } else {
            for (x = old_x; x < cols; x += p.kind ? 2 : 3) draw_cell(y, x);
            y += p.kind ? 3 : 2;
            cdiff ^= 2;
            old_color += 2;
            color = old_color + cdiff;
            p = t[1];
            for (; y < rows; y += p.kind ? 3 : 2) {
                for (x = old_x; x < cols; x += p.kind ? 2 : 3) draw_cell(y, x);
                cdiff ^= 2;
                color = old_color + cdiff;
            }
        }
    }

    void draw() {
        res.assign(rows, string(cols, ' '));
        int y = 0, x = 0, color = 0;
        if (!has_95) {
            draw_list(y, x, color, trom);
        } else {
            draw_single(y, x, color, *has_95);
            color = 2;
            if (!trom.empty() && !right.empty()) {
                int old_x = x, old_y = y, old_r = rows, old_c = cols;
                x = 0;
                if (!has_95->full_bottom) cols = old_x;
                draw_list(y, x, color, trom);
                cols = old_c;
                color = 6;
                y = 0;
                if (has_95->full_bottom) rows = old_y;
                draw_list(y, old_x, color, right);
                rows = old_r;
            } else if (!trom.empty()) {
                color = 4;
                if (has_95->full_bottom) x = 0;
                draw_list(y, x, color, trom);
            } else if (!right.empty()) {
                color = 4;
                y = 0;
                draw_list(y, x, color, right);
            }
        }
        for (const string& row : res) cout << row << '\n';
    }

    ~fill_tr() { delete has_95; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        fill_tr f(n, m);
        if (f.possible()) {
            cout << "YES\n";
            f.draw();
        } else {
            cout << "NO\n";
        }
    }
}
