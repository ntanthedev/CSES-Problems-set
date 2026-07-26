/*

* Problem:      2129 Task Assignment
* Input read:   n; n x n cost matrix
* Validity:     Output optimal total cost and n assignment pairs. Every employee and every
* ```
            task must appear exactly once, and the assignment cost must match the claim
* Optimality:   Claimed total cost must equal the minimum cost from ans
* Complexity:   O(n^2) time, O(n^2) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<vector<int>> cost(n + 1, vector<int>(n + 1));
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        cost[i][j] = inf.readInt();
    }
}

int optimal = ans.readInt();

int claimed = ouf.readInt(0, n * 1000, "minimum total cost");

if (claimed != optimal) {
    quitf(_wa, "contestant claimed total cost %d, but optimum is %d",
          claimed, optimal);
}

vector<char> usedEmployee(n + 1, 0);
vector<char> usedTask(n + 1, 0);

long long total = 0;

for (int i = 1; i <= n; i++) {
    int employee = ouf.readInt(1, n, format("assignment[%d].employee", i).c_str());
    int task = ouf.readInt(1, n, format("assignment[%d].task", i).c_str());

    if (usedEmployee[employee]) {
        quitf(_wa, "employee %d is assigned more than once", employee);
    }

    if (usedTask[task]) {
        quitf(_wa, "task %d is assigned more than once", task);
    }

    usedEmployee[employee] = 1;
    usedTask[task] = 1;
    total += cost[employee][task];
}

for (int i = 1; i <= n; i++) {
    if (!usedEmployee[i]) {
        quitf(_wa, "employee %d is not assigned any task", i);
    }

    if (!usedTask[i]) {
        quitf(_wa, "task %d is not assigned to any employee", i);
    }
}

if (total != claimed) {
    quitf(_wa, "claimed total cost is %d, but actual assignment cost is %lld",
          claimed, total);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid optimal assignment with total cost %lld", total);

}
