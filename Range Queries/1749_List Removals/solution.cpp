#include <iostream>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

// Changes the value in the position i to x.
void change(int i, int x) {
    i += TREE_SIZE;
    tree[i] = x;
    while (i > 1) {
        i /= 2;
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
}

// Returns the index of the kth 'active' position.
int query(int k) {
    int s = 1;
    while (s < TREE_SIZE) {
        // The index of the left child is s * 2.
        // The index of the right child is s * 2 + 1.
        if (tree[s * 2] >= k) {
            s = s * 2;
        } else {
            k -= tree[s * 2];
            s = s * 2 + 1;
        }
    }
    return s - TREE_SIZE;
}

const int N = 200001;
int x[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        change(i, 1);
    }

    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        int pos = query(p);
        cout << x[pos] << ' ';
        change(pos, 0);
    }
    cout << '\n';
}
