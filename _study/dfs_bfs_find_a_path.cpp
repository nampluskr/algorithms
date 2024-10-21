# if 0
// start - end 까지 경로가 존재 여부 확인

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

bool dfs_preorder(int curr, int end, bool visited[], std::vector<int>& path) {
    if (visited[curr]) return false;
    // visit the node (preorder)
    visited[curr] = true;
    path.push_back(curr);
    if (curr == end) { return true; }

    for (auto& next : adjList[curr])
        if (!visited[next.to])
            if (dfs_preorder(next.to, end, visited, path)) return true;
    return false;
}

// set initial condition
// visited[curr] = true;
// path.clear();
bool dfs_postorder(int curr, int end, bool visited[], std::vector<int>& path) {

    if (curr == end) { return true; }

    for (auto& next : adjList[curr])
        if (!visited[next.to]) {
            // visit (post order)
            visited[next.to] = true;
            path.push_back(next.to);

            if (dfs_postorder(next.to, end, visited, path)) return true;
        }
    return false;
}

void bfs_preorder(int start, int end, bool visited[], std::vector<int>& path) {
    std::queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr]) continue;
        // visit the node (preorder)
        visited[curr] = true;
        path.push_back(curr);
        if (curr == end) break;

        for (auto next : adjList[curr])
            if (!visited[next.to])
                Q.push(next.to);
    }
}

void bfs_postorder(int start, int end, bool visited[], std::vector<int>& path) {
    std::queue<int> Q;
    Q.push(start);

    // set initial condition
    visited[start] = true;
    path.push_back(start);

    bool flag = false;
    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        for (auto next : adjList[curr])
            if (!visited[next.to]) {
                // visit the node (post order)
                visited[next.to] = true;
                path.push_back(next.to);
                if (next.to == end) { flag = true; break; }
                Q.push(next.to);
            }
        if (flag) break;
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
    int start = 0, end = 3;

    initGraph(visited, path);
    dfs_preorder(start, end, visited, path);
    print(path);

    initGraph(visited, path);
    visited[start] = true;
    path.push_back(start);
    dfs_postorder(start, end, visited, path);
    print(path);

    initGraph(visited, path);
    bfs_preorder(start, end, visited, path);
    print(path);

    initGraph(visited, path);
    bfs_postorder(start, end, visited, path);
    print(path);

    return 0;
}
#endif
