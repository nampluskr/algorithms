#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

#define MAX_NODES 100

struct Edge {
    int to, cost;
    bool visited[MAX_NODES];
    std::vector<int> path;

    Edge(int to, int cost) { this->to = to; this->cost = cost; }
    Edge(int to, int cost, bool visited[], std::vector<int>& path) {
        this->to = to; this->cost = cost;
        for (int i = 0; i < MAX_NODES; i++) this->visited[i] = visited[i];
        for (int x: path) this->path.push_back(x);
    }
};
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

bool dfs_preorder(int curr, int target) {
    if (visited[curr]) return false;
    // visit the current node (preorder)
    visited[curr] = true; path.push_back(curr);
    if (curr == target) { print(path); return true; }

    for (auto& next: adjList[curr])
        if (!visited[next.to]) {
            parent[next.to] = curr;
            if (dfs_preorder(next.to, target)) return true;
            // backtrack
            visited[next.to] = false; path.pop_back();
        }
    return false;
}

// visited[start] = true; path.push_back(start);
bool dfs_postorder(int curr, int target) {
    if (curr == target) { print(path); return true; }

    for (auto& next: adjList[curr])
        if (!visited[next.to]) {
            // visit the next node (post order)
            visited[next.to] = true; path.push_back(next.to);
            // if (next.to == target) { print(path); return; }

            parent[next.to] = curr;
            if (dfs_postorder(next.to, target)) return true;
            // backtrack
            visited[next.to] = false; path.pop_back();
        }
    return false;
}

bool bfs_preorder(int start, int target) {
    std::queue<Edge> Q;
    Q.push({ start, 0, visited, path });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.visited[curr.to]) continue;
        // visit the current node (preorder)
        curr.visited[curr.to] = true; curr.path.push_back(curr.to);
        if (curr.to == target) { print(curr.path); return true; }

        for (auto& next: adjList[curr.to])
            if (!curr.visited[next.to]) {
                parent[next.to] = curr.to;
                Q.push({ next.to, next.cost, curr.visited, curr.path });
                // bactrack
                // curr.visited[next.to] = false; curr.path.pop_back();
            }
    }
    return false;
}

// visited[start] = true; path.push_back(start);
bool bfs_postorder(int start, int target) {
    std::queue<Edge> Q;
    Q.push({ start, 0, visited, path });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.to == target) { print(curr.path); return true; }

        for (auto& next: adjList[curr.to])
            if (!curr.visited[next.to]) {
                // visit the next node (post order)
                curr.visited[next.to] = true; curr.path.push_back(next.to);
                // if (next.to == target) { print(curr.path); return; }

                parent[next.to] = curr.to;
                Q.push({ next.to, next.cost, curr.visited, curr.path });
                // backtrack
                curr.visited[next.to] = false; curr.path.pop_back();
            }
    }
    return false;
}

int main()
{
    int start = 0, target = 5;
    createTree();

    if (1) {
        printf("\n*** DFS - preorder\n");
        initTree();
        dfs_preorder(start, target);
    }
    if (1) {
        printf("\n*** DFS - post order\n");
        initTree();
        visited[start] = true; path.push_back(start);
        dfs_postorder(start, target);
    }
    if (1) {
        printf("\n*** BFS - preorder\n");
        initTree();
        bfs_preorder(start, target);
    }
    if (1) {
        printf("\n*** BFS - post order\n");
        initTree();
        visited[start] = true; path.push_back(start);
        bfs_postorder(start, target);
    }

    return 0;
}