#include <iostream>
using namespace std;

const int N = 100001;
int preorder[N], inorder[N];
int inorder_pos[N];

// [l_p, r_p] is the range of the current subtree in the `preorder` array.
// [l_i, r_i] is the range of the current subtree in the `inorder` array.
void postorder(int l_p, int r_p, int l_i, int r_i) {
    if (r_p < l_p) return;
    int root = preorder[l_p];
    int root_pos = inorder_pos[root];
    int left_sz = root_pos - l_i;
    postorder(l_p + 1, l_p + left_sz, l_i, root_pos - 1);
    postorder(l_p + left_sz + 1, r_p, root_pos + 1, r_i);
    cout << root << ' ';
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> preorder[i];
    }

    for (int i = 1; i <= n; ++i) {
        cin >> inorder[i];
        inorder_pos[inorder[i]] = i;
    }

    postorder(1, n, 1, n);
    cout << '\n';
}
