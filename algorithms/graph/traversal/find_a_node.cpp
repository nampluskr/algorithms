// Find a node
#if 1
#include <cstdio>
#include <vector>
#include <queue>

#define MAX_NODES   100

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

void initGraph(bool visited[], std::vector<int>& path) {
    for (int i = 0; i < MAX_NODES; i++) visited[i] = false;
    path.clear();
}

bool dfs_preorder(int curr, int end, bool visited[], std::vector<int>& path) {
    if (visited[curr]) return false;
    // visit the node (preorder)
    visited[curr] = true;
    path.push_back(curr);

    // target condition
    if (curr == end) return true;

    for (auto& next : adjList[curr])
        if (dfs_preorder(next.to, end, visited, path))
            return true;

    return false;
}

// visit the start node at first
bool dfs_postorder(int curr, int end, bool visited[], std::vector<int>& path) {
    // target condition
    if (curr == end) return true;

    for (auto& next : adjList[curr])
        if (!visited[next.to]) {
            // visit the node (post order)
            visited[next.to] = true;
            path.push_back(next.to);
            // target condition
            // if (next.to == end) return true;

            if (dfs_postorder(next.to, end, visited, path))
                return true;
        }
    return false;
}

bool bfs_preorder(int start, int end, bool visited[], std::vector<int>& path) {
    std::queue<int> Q;
    Q.push(start);

    int flag = false;
    while(!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr]) continue;

        // visit the node (preorder)
        visited[curr] = true;
        path.push_back(curr);

        // target condition
        if (curr == end) { flag = true; break; }    // return true;

        for (auto& next: adjList[curr])
            Q.push(next.to);
    }
    return flag ? true : false;
}

// visit the start node at first
bool bfs_postorder(int start, int end, bool visited[], std::vector<int>& path) {
    std::queue<int> Q;
    Q.push(start);

    int flag = false;
    while(!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        // if (curr == end) { flag = true; break; } if Q.push({ next.to, curr.visited, curr.path });

        for (auto& next: adjList[curr])
            if (!visited[next.to]) {
                // visit the node (preorder)
                visited[next.to] = true;
                path.push_back(next.to);

                // target condition
                if (next.to == end) { flag = true; break; } // return false;
                Q.push(next.to);
            }
        if (flag) break;
    }
    return flag ? true : false;
}

int main()
{
    bool visited[MAX_NODES];
    int parent[MAX_NODES];
    std::vector<int> path;
    int start = 0, end = 5;

    createGraph();

    if (1) {
        printf("\n*** DFS [start -> end] ***\n");
        initGraph(visited, path);
        dfs_preorder(start, end, visited, path);
        print(path);

        printf("\n*** DFS [start -> end] ***\n");
        initGraph(visited, path);
        visited[start] = true;
        path.push_back(start);
        dfs_postorder(start, end, visited, path);
        print(path);
    }
    if (1) {
        printf("\n*** BFS [start -> end] ***\n");
        initGraph(visited, path);
        bfs_preorder(start, end, visited, path);
        print(path);

        printf("\n*** BFS [start -> end] ***\n");
        initGraph(visited, path);
        visited[start] = true;
        path.push_back(start);
        bfs_postorder(start, end, visited, path);
        print(path);
    }

    return 0;
}
#endif