#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

#define MAX_NODES 100

std::vector<int> adjList[MAX_NODES];
bool visited[MAX_NODES];
int parent[MAX_NODES];
std::vector<int> path;

void addEdge(int from, int to) {
    adjList[from].push_back(to);
    adjList[to].push_back(from);
}

void createTree() {
    addEdge(0, 1); addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4); addEdge(2, 5); addEdge(2, 6);
    addEdge(3, 7); addEdge(3, 8);
    addEdge(6, 9);
}

void print(std::vector<int>& path) {
    printf(">> ");
    for (auto x: path) printf("[%d]->", x);
    printf("\n");
}

void initTree() {
    for (int i = 0; i < MAX_NODES; i++){
        visited[i] = false;
        parent[i] = -1;
    }
    path.clear();
}

void dfs_preorder(int curr) {
    if (visited[curr]) return;
    // visit the current node (preorder)
    visited[curr] = true; path.push_back(curr);

    for (auto& next: adjList[curr])
        if (!visited[next]) {
            parent[next] = curr;
            dfs_preorder(next);
        }
} // >> [0]->[1]->[3]->[7]->[8]->[2]->[4]->[5]->[6]->[9]->

// visited[start] = true; path.push_back(start);
void dfs_postorder(int curr) {
    for (auto& next: adjList[curr])
        if (!visited[next]) {
            // visit the next node (post order)
            visited[next] = true; path.push_back(next);

            parent[next] = curr;
            dfs_postorder(next);
        }
} // >> [0]->[1]->[3]->[7]->[8]->[2]->[4]->[5]->[6]->[9]->

void bfs_preorder(int start) {
    std::queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr]) continue;
        // visit the current node (preorder)
        visited[curr] = true; path.push_back(curr);

        for (auto& next: adjList[curr])
            if (!visited[next]) {
                parent[next] = curr;
                Q.push(next);
            }
    }
} // >> [0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->

// visited[start] = true; path.push_back(start);
void bfs_postorder(int start) {
    std::queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        for (auto& next: adjList[curr])
            if (!visited[next]) {
                // visit the next node (post order)
                visited[next] = true; path.push_back(next);

                parent[next] = curr;
                Q.push(next);
            }
    }
} // >> [0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->

void stack_preorder(int start) {
    std::stack<int> S;
    S.push(start);

    while (!S.empty()) {
        auto curr = S.top(); S.pop();

        if (visited[curr]) continue;
        // visit the current node (preorder)
        visited[curr] = true; path.push_back(curr);

        for (auto& next: adjList[curr])
            if (!visited[next]) {
                parent[next] = curr;
                S.push(next);
            }
    }
} // >> [0]->[2]->[6]->[9]->[5]->[4]->[1]->[3]->[8]->[7]->

// visited[start] = true; path.push_back(start);
void stack_postorder(int start) {
    std::stack<int> S;
    S.push(start);

    while (!S.empty()) {
        auto curr = S.top(); S.pop();

        for (auto& next: adjList[curr])
            if (!visited[next]) {
                // visit the next node (post order)
                visited[next] = true; path.push_back(next);

                parent[next] = curr;
                S.push(next);
            }
    }
} // >> [0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->


int main()
{
    int start = 0;
    createTree();

    if (1) {
        initTree();
        dfs_preorder(start);
        print(path);
    }
    if (1) {
        initTree();
        visited[start] = true; path.push_back(start);
        dfs_postorder(start);
        print(path);
    }
    if (1) {
        initTree();
        bfs_preorder(start);
        print(path);
    }
    if (1) {
        initTree();
        visited[start] = true; path.push_back(start);
        bfs_postorder(start);
        print(path);
    }
        if (1) {
        initTree();
        stack_preorder(start);
        print(path);
    }
    if (1) {
        initTree();
        visited[start] = true; path.push_back(start);
        stack_postorder(start);
        print(path);
    }

    return 0;
}