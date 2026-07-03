#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int test = 0; test < t; test++) {
        int n = inf.readInt();
        int m = inf.readInt();
        int y1 = inf.readInt();
        int x1 = inf.readInt();
        int y2 = inf.readInt();
        int x2 = inf.readInt();
        string ans_flag = ans.readToken();
        if (ans_flag != "YES" && ans_flag != "NO")
            quitf(_fail, "Invalid judge answer token '%s'", ans_flag.c_str());

        string out_flag = ouf.readToken();
        if (out_flag != "YES" && out_flag != "NO")
            quitf(_wa, "Expected YES or NO, got '%s'", out_flag.c_str());

        if (out_flag == "NO") {
            if (ans_flag != "NO")
                quitf(_wa, "Hamiltonian path exists but contestant printed NO");
            continue;
        }

        if (ans_flag == "NO")
            quitf(_wa, "No Hamiltonian path exists but contestant printed YES");

        string ans_path = ans.readToken();
        string path = ouf.readToken();

        int expected_len = n * m - 1;
        if ((int)path.size() != expected_len)
            quitf(_wa, "Path length must be %d, got %d", expected_len, (int)path.size());

        int cy = y1, cx = x1;
        vector<vector<bool>> visited(n + 1, vector<bool>(m + 1, false));
        visited[cy][cx] = true;
        int visited_count = 1;

        for (char ch : path) {
            if (ch != 'U' && ch != 'D' && ch != 'L' && ch != 'R')
                quitf(_wa, "Invalid direction '%c'", ch);
            int ny = cy, nx = cx;
            if (ch == 'U') ny--;
            else if (ch == 'D') ny++;
            else if (ch == 'L') nx--;
            else nx++;

            if (ny < 1 || ny > n || nx < 1 || nx > m)
                quitf(_wa, "Move '%c' from (%d,%d) goes out of bounds", ch, cy, cx);
            if (visited[ny][nx])
                quitf(_wa, "Cell (%d,%d) visited more than once", ny, nx);

            visited[ny][nx] = true;
            visited_count++;
            cy = ny;
            cx = nx;
        }

        if (cy != y2 || cx != x2)
            quitf(_wa, "Path ends at (%d,%d), expected (%d,%d)", cy, cx, y2, x2);
        if (visited_count != n * m)
            quitf(_wa, "Only %d cells visited, expected %d", visited_count, n * m);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "All %d tests passed", t);
}
