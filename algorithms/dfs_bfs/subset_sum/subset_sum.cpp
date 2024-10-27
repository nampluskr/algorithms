#include <cstdio>
#include <vector>
#include <queue>

int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
std::vector<int> sol;
int target = 12;
int arrSize = 10;

void print(std::vector<int>& sol) {
    printf("[ ");
    for (int x: sol) printf("%d, ", x);
    printf("]\n");
}

void dfs1(int k, int sum) {
    if (sum == target) { print(sol); return; }
    if (k == arrSize) return;

    if (sum + arr[k] <= target) {   // pruning
        sol.push_back(arr[k]);
        dfs1(k + 1, sum + arr[k]);
        sol.pop_back();
    }
    if (sum <= target)      // pruning
        dfs1(k + 1, sum);
}

void dfs2(int k, int sum) {
    if (sum == target) { print(sol); return; }
    if (k == arrSize) return;

    for (int i = k; i < arrSize; i++) {
        if (sum + arr[i] <= target) {   // pruning
            sol.push_back(arr[i]);
            dfs2(i + 1, sum + arr[i]);
            sol.pop_back();
        }
    }
}

struct State {
    int k, sum;
    std::vector<int> sol;

    State(int k, int sum, const std::vector<int>& sol) {
        this->k = k;
        this->sum = sum;
        for (auto x: sol) this->sol.push_back(x);
    }
};

void bfs1(int k, int sum) {
    std::queue<State> Q;
    Q.push({ k, sum, sol });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.sum == target) { print(curr.sol); continue; }
        if (curr.k == arrSize) continue;

        if (curr.sum + arr[curr.k <= target]) { // pruning
            curr.sol.push_back(arr[curr.k]);
            Q.push({ curr.k + 1, curr.sum + arr[curr.k], curr.sol });
            curr.sol.pop_back();
        }
        if (curr.sum <= target)     // pruning
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
            if (curr.sum + arr[i] <= target) {  // pruning
                curr.sol.push_back(arr[i]);
                Q.push({ i + 1, curr.sum + arr[i], curr.sol });
                curr.sol.pop_back();
            }
        }
    }

}


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