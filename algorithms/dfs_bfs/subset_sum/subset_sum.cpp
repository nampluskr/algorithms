#include <cstdio>
#include <vector>
#include <queue>

int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
std::vector<int> sol;
int target = 12;
int arrSize = 10;

struct State {
    int k, sum;
    std::vector<int> sol;

    State(int k, int sum, const std::vector<int>& sol) {
        this->k = k;
        this->sum = sum;
        for (auto x: sol) this->sol.push_back(x);
    }
};

void print(std::vector<int>& sol) {
    printf("[ ");
    for (int x: sol) printf("%d, ", x);
    printf("]\n");
}

void dfs1(int k, int sum) {
    if (sum == target) { print(sol); return; }
    if (k == arrSize) return;

    sol.push_back(arr[k]);
    dfs1(k + 1, sum + arr[k]);
    sol.pop_back();

    dfs1(k + 1, sum);
}

void dfs2(int k, int sum) {
    if (sum == target) { print(sol); return; }
    if (k == arrSize) return;

    for (int i = k; i < arrSize; i++) {
        sol.push_back(arr[i]);
        dfs2(i + 1, sum + arr[i]);
        sol.pop_back();
    }
}

void bfs1(int k, int sum) {
    std::queue<State> Q;
    Q.push({ k, sum, sol });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.sum == target) { print(curr.sol); continue; }
        if (curr.k == arrSize) continue;

        curr.sol.push_back(arr[curr.k]);
        Q.push({ curr.k + 1, curr.sum + arr[curr.k], curr.sol });
        curr.sol.pop_back();

        Q.push({ curr.k + 1, curr.sum, curr.sol });
    }
}

void bfs2(int k, int sum) {
    std::queue<State> Q;
    Q.push({ k, sum, sol });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.sum == target) { print(curr.sol); continue; }
        if (curr.k == arrSize) continue;

        for (int i = curr.k; i < arrSize; i++) {
            curr.sol.push_back(arr[i]);
            Q.push({ i + 1, curr.sum + arr[i], curr.sol });
            curr.sol.pop_back();
        }
    }
}

*** DFS1 ***
[ 1, 2, 3, 6, ]
[ 1, 2, 4, 5, ]
[ 1, 2, 9, ]
[ 1, 3, 8, ]
[ 1, 4, 7, ]
[ 1, 5, 6, ]
[ 2, 3, 7, ]
[ 2, 4, 6, ]
[ 2, 10, ]
[ 3, 4, 5, ]
[ 3, 9, ]
[ 4, 8, ]
[ 5, 7, ]


int main()
{
    if (1) {
        printf("\n*** DFS1 ***\n");
        sol.clear();
        dfs1(0, 0);
    }
    if (1) {
        printf("\n*** DFS2 ***\n");
        sol.clear();
        dfs2(0, 0);
    }
    if (1) {
        printf("\n*** BFS1 ***\n");
        sol.clear();
        bfs1(0, 0);
    }
    if (1) {
        printf("\n*** BFS2 ***\n");
        sol.clear();
        bfs2(0, 0);
    }

    return 0;
}