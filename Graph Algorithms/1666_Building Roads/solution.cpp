#include <iostream>
#include <vector>
using namespace std;

const int N = 100001;
vector<int> graph[N];
int component[N];

void mark_component(int x, int id) {
    if (component[x]) return;
    component[x] = id;
    for (int y : graph[x]) {
        mark_component(y, id);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int count = 0;
    vector<int> roots;
    for (int i = 1; i <= n; ++i) {
        if (component[i] == 0) {
            mark_component(i, ++count);
            roots.push_back(i);
        }
    }

    cout << count - 1 << '\n';
    for (int i = 0; i + 1 < roots.size(); ++i) {
        cout << roots[i] << ' ' << roots[i + 1] << '\n';
    }
}
