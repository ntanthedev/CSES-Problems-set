#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

const int N = 3;
using grid = array<char, N * N>;
const grid GOAL = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

const int SWAP[][2] = {{0, 1}, {0, 3}, {1, 2}, {1, 4}, {2, 5}, {3, 4},
                       {3, 6}, {4, 5}, {4, 7}, {5, 8}, {6, 7}, {7, 8}};

int grid_hash(grid &g) {
    int h = 0;
    for (int i = 0; i < N * N; ++i) {
        h = h * 9 + (g[i] - '1');
    }
    return h;
}

int main() {
    grid s;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> s[i * N + j];
        }
    }

    vector<grid> q{s};
    unordered_map<int, int> dist;
    dist[grid_hash(s)] = 0;

    for (int qi = 0; qi < q.size(); ++qi) {
        auto cur = q[qi];
        if (cur == GOAL) {
            cout << dist[grid_hash(cur)] << '\n';
            return 0;
        }
        for (auto [i, j] : SWAP) {
            auto nxt = cur;
            swap(nxt[i], nxt[j]);
            if (!dist.count(grid_hash(nxt))) {
                dist[grid_hash(nxt)] = dist[grid_hash(cur)] + 1;
                q.push_back(nxt);
            }
        }
    }
}
