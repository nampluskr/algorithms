# if 1
// 연결된 모든 노드 탐색 (traversal, flood fill)

#include <cstdio>
#include <vector>
#include <stack>
#include <queue>

#define MAX_NODES 20

struct Edge { int to, cost; };
std::vector<Edge> adjList[MAX_NODES];
int nodeCnt;

void addEdge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
    adjList[to].push_back({ from, cost });
    nodeCnt++;
}

void createGraph() {
    nodeCnt = 0;
    addEdge(0, 1); addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4); addEdge(2, 5); addEdge(2, 6);
    addEdge(3, 7); addEdge(3, 8);
    addEdge(6, 9);
}

void print(const std::vector<int>& path) {
    printf(">> ");
    for (int node : path) printf("[%d]->", node);
    printf("\n");
}

void dfs_preorder(int curr, bool visited[], std::vector<int>& path) {
    if (visited[curr]) return;
    // visit the node (preorder)
    visited[curr] = true;
    path.push_back(curr);

    for (auto& next : adjList[curr])
        if (!visited[next.to])
            dfs_preorder(next.to, visited, path);
}

// set initial condition
// visited[curr] = true;
// path.clear();
void dfs_postorder(int curr, bool visited[], std::vector<int>& path) {

    for (auto& next : adjList[curr])
        if (!visited[next.to]) {
            // visit (post order)
            visited[next.to] = true;
            path.push_back(next.to);

            dfs_postorder(next.to, visited, path);
        }
}

void bfs_preorder(int start, bool visited[], std::vector<int>& path) {
    std::queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr]) continue;
        // visit the node (preorder)
        visited[curr] = true;
        path.push_back(curr);

        for (auto next : adjList[curr])
            if (!visited[next.to])
                Q.push(next.to);
    }
}

void bfs_postorder(int start, bool visited[], std::vector<int>& path) {
    std::queue<int> Q;
    Q.push(start);

    // set initial condition
    visited[start] = true;
    path.push_back(start);

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        for (auto next: adjList[curr]) 
            if (!visited[next.to]) {
                // visit the node (post order)
                visited[next.to] = true;
                path.push_back(next.to);
                Q.push(next.to);
            }
    }
}

void initGraph(bool visited[], std::vector<int>& path) {
    for (int i = 0; i < MAX_NODES; i++) visited[i] = false;
    path.clear();
}

int main()
{
    createGraph();

    bool visited[MAX_NODES];
    std::vector<int> path;
    int start = 0, end = 4;

    initGraph(visited, path);
    dfs_preorder(start, visited, path);
    print(path);

    initGraph(visited, path);
    visited[start] = true;
    path.push_back(start);
    dfs_postorder(start, visited, path);
    print(path);

    initGraph(visited, path);
    bfs_preorder(start, visited, path);
    print(path);

    initGraph(visited, path);
    bfs_postorder(start, visited, path);
    print(path);

    return 0;
}
#endif
