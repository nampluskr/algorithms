#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

#define MAX_NODES 100

struct Edge { int to, cost; };
std::vector<Edge> adjList[MAX_NODES];
bool visited[MAX_NODES];
int parent[MAX_NODES];
std::vector<int> path;

void addEdge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
}

void createTree() {
    addEdge(0, 1, 16); addEdge(0, 2, 13);
    addEdge(1, 2, 10); addEdge(1, 3, 12);
    addEdge(2, 1, 4); addEdge(2, 4, 14);
    addEdge(3, 2, 9); addEdge(3, 5, 20);
    addEdge(4, 3, 7); addEdge(4, 5, 4);
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
        if (!visited[next.to]) {
            parent[next.to] = curr;
            dfs_preorder(next.to);
        }
}

// visited[start] = true; path.push_back(start);
void dfs_postorder(int curr) {
    for (auto& next: adjList[curr])
        if (!visited[next.to]) {
            // visit the next node (post order)
            visited[next.to] = true; path.push_back(next.to);

            parent[next.to] = curr;
            dfs_postorder(next.to);
        }
}

void bfs_preorder(int start) {
    std::queue<Edge> Q;
    Q.push({ start, 0 });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr.to]) continue;
        // visit the current node (preorder)
        visited[curr.to] = true; path.push_back(curr.to);

        for (auto& next: adjList[curr.to])
            if (!visited[next.to]) {
                parent[next.to] = curr.to;
                Q.push(next);
            }
    }
}

// visited[start] = true; path.push_back(start);
void bfs_postorder(int start) {
    std::queue<Edge> Q;
    Q.push({ start, 0 });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        for (auto& next: adjList[curr.to])
            if (!visited[next.to]) {
                // visit the next node (post order)
                visited[next.to] = true; path.push_back(next.to);

                parent[next.to] = curr.to;
                Q.push(next);
            }
    }
}

void stack_preorder(int start) {
    std::stack<Edge> S;
    S.push({ start, 0 });

    while (!S.empty()) {
        auto curr = S.top(); S.pop();

        if (visited[curr.to]) continue;
        // visit the current node (preorder)
        visited[curr.to] = true; path.push_back(curr.to);

        for (auto& next: adjList[curr.to])
            if (!visited[next.to]) {
                parent[next.to] = curr.to;
                S.push(next);
            }
    }
}

// visited[start] = true; path.push_back(start);
void stack_postorder(int start) {
    std::stack<Edge> S;
    S.push({ start, 0 });

    while (!S.empty()) {
        auto curr = S.top(); S.pop();

        for (auto& next: adjList[curr.to])
            if (!visited[next.to]) {
                // visit the next node (post order)
                visited[next.to] = true; path.push_back(next.to);

                parent[next.to] = curr.to;
                S.push(next);
            }
    }
}


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