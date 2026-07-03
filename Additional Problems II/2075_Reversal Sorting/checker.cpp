/*

* Problem:      2075 Reversal Sorting
* Input read:   n; permutation p[1..n]
* Validity:     Output k in [0,n], then k reversal ranges [l,r]; after applying them,
* ```
            the permutation must become 1,2,...,n
* Optimality:   Bound only: at most n reversals
* Complexity:   O((n+k) log n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

struct Node {
int val;
uint32_t pri;
int sz;
bool rev;
Node* left;
Node* right;
};

static int size_of(Node* t) {
return t ? t->sz : 0;
}

static void pull(Node* t) {
if (t) {
t->sz = 1 + size_of(t->left) + size_of(t->right);
}
}

static void push(Node* t) {
if (!t || !t->rev) return;

t->rev = false;
swap(t->left, t->right);

if (t->left) t->left->rev = !t->left->rev;
if (t->right) t->right->rev = !t->right->rev;

}

static uint32_t splitmix32(uint32_t x) {
uint64_t z = x + 0x9e3779b97f4a7c15ULL;
z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
z = z ^ (z >> 31);
return (uint32_t)z;
}

static Node* merge_treap(Node* a, Node* b) {
if (!a) return b;
if (!b) return a;

if (a->pri > b->pri) {
    push(a);
    a->right = merge_treap(a->right, b);
    pull(a);
    return a;
} else {
    push(b);
    b->left = merge_treap(a, b->left);
    pull(b);
    return b;
}

}

static void split_treap(Node* t, int leftCount, Node*& a, Node*& b) {
if (!t) {
a = b = nullptr;
return;
}

push(t);

if (size_of(t->left) >= leftCount) {
    split_treap(t->left, leftCount, a, t->left);
    b = t;
    pull(b);
} else {
    split_treap(t->right, leftCount - size_of(t->left) - 1, t->right, b);
    a = t;
    pull(a);
}

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<Node> nodes(n + 1);
Node* root = nullptr;

for (int i = 1; i <= n; i++) {
    int value = inf.readInt();

    nodes[i].val = value;
    nodes[i].pri = splitmix32((uint32_t)i);
    nodes[i].sz = 1;
    nodes[i].rev = false;
    nodes[i].left = nullptr;
    nodes[i].right = nullptr;

    root = merge_treap(root, &nodes[i]);
}

int k = ouf.readInt(0, n, "number of reversals");

for (int op = 1; op <= k; op++) {
    int l = ouf.readInt(1, n, format("reversal[%d].left", op).c_str());
    int r = ouf.readInt(l, n, format("reversal[%d].right", op).c_str());

    Node* a = nullptr;
    Node* b = nullptr;
    Node* c = nullptr;

    split_treap(root, l - 1, a, b);
    split_treap(b, r - l + 1, b, c);

    if (b) b->rev = !b->rev;

    root = merge_treap(merge_treap(a, b), c);
}

vector<Node*> st;
Node* cur = root;
int expected = 1;

while (cur || !st.empty()) {
    while (cur) {
        push(cur);
        st.push_back(cur);
        cur = cur->left;
    }

    cur = st.back();
    st.pop_back();

    if (cur->val != expected) {
        quitf(_wa, "after all reversals, position %d has value %d, expected %d",
              expected, cur->val, expected);
    }

    expected++;
    cur = cur->right;
}

if (expected != n + 1) {
    quitf(_wa, "internal checker error while traversing the final permutation");
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid sorting with %d reversals", k);

}
