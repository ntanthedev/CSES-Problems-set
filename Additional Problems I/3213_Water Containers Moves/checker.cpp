#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int pour_cost(int a, int b, int capA, int capB, char from, char to) {
    if (from == 'A' && to == 'B') return min(a, capB - b);
    return min(b, capA - a);
}

int apply_move(int& a, int& b, int capA, int capB, const string& move, int idx) {
    if (move == "FILL A") {
        int add = capA - a;
        if (add < 1)
            quitf(_wa, "Move %d: FILL A does not move any water", idx);
        a = capA;
        return add;
    }
    if (move == "FILL B") {
        int add = capB - b;
        if (add < 1)
            quitf(_wa, "Move %d: FILL B does not move any water", idx);
        b = capB;
        return add;
    }
    if (move == "EMPTY A") {
        if (a < 1)
            quitf(_wa, "Move %d: EMPTY A on an empty container", idx);
        int rem = a;
        a = 0;
        return rem;
    }
    if (move == "EMPTY B") {
        if (b < 1)
            quitf(_wa, "Move %d: EMPTY B on an empty container", idx);
        int rem = b;
        b = 0;
        return rem;
    }
    if (move == "MOVE A B") {
        int moved = pour_cost(a, b, capA, capB, 'A', 'B');
        if (moved < 1)
            quitf(_wa, "Move %d: MOVE A B does not move any water", idx);
        a -= moved;
        b += moved;
        return moved;
    }
    if (move == "MOVE B A") {
        int moved = pour_cost(a, b, capA, capB, 'B', 'A');
        if (moved < 1)
            quitf(_wa, "Move %d: MOVE B A does not move any water", idx);
        a += moved;
        b -= moved;
        return moved;
    }
    quitf(_wa, "Move %d: unknown command '%s'", idx, move.c_str());
    return 0;
}

void skip_moves(int n) {
    for (int i = 0; i < n; i++) {
        string tok = ans.readToken();
        if (tok == "MOVE") {
            ans.readToken();
            ans.readToken();
        } else {
            ans.readToken();
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int capA = inf.readInt();
    int capB = inf.readInt();
    int target = inf.readInt();

    string ref_first = ans.readToken();

    if (ref_first == "-1") {
        string out_first = ouf.readToken();
        if (out_first != "-1")
            quitf(_wa, "Measuring %d units is impossible", target);
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: impossible");
    }

    int ref_n = stoi(ref_first);
    int optimal_moved = ans.readInt();
    skip_moves(ref_n);

    string out_first = ouf.readToken();
    if (out_first == "-1")
        quitf(_wa, "Measuring %d units is possible but output is -1", target);

    int n = stoi(out_first);
    int claimed = ouf.readInt();
    int a = 0, b = 0, total = 0;
    for (int i = 0; i < n; i++) {
        string move = ouf.readToken();
        if (move == "MOVE") {
            string x = ouf.readToken();
            string y = ouf.readToken();
            move += " " + x + " " + y;
        } else {
            move += " " + ouf.readToken();
        }
        total += apply_move(a, b, capA, capB, move, i + 1);
    }

    if (a != target)
        quitf(_wa, "Container A has %d units, expected %d", a, target);

    if (total != claimed)
        quitf(_wa, "Reported moved water is %d, but moves sum to %d", claimed, total);

    if (total != optimal_moved)
        quitf(_wa, "Minimum moved water is %d, got %d", optimal_moved, total);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal solution with %d moves and %d moved water", n, total);
}
