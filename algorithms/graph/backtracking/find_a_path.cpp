// Find a path
#if 0
#include <cstdio>
#include <vector>
#include <queue>

#define MAX_NODES   100

struct Edge { int to, cost; };
std::vector<Edge> adjList[MAX_NODES];
int nodeCnt;

void addEdge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
    // adjList[to].push_back({ from, cost });
    nodeCnt++;
}

void createGraph() {
    addEdge(0, 1, 8); addEdge(0, 2, 7); addEdge(0, 3, 4);
    addEdge(1, 2, 2); addEdge(1, 4, 3); addEdge(1, 5, 9);
    addEdge(2, 3, 5); addEdge(2, 5, 6);
    addEdge(3, 5, 7); addEdge(3, 6, 2);
    addEdge(4, 7, 9);
    addEdge(5, 4, 3); addEdge(5, 6, 4); addEdge(5, 7, 5);
    addEdge(6, 7, 8);
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
    if (curr == end) { print(path); return true; }

    for (auto& next : adjList[curr]) {
        if (dfs_preorder(next.to, end, visited, path))
            return true;
        // Bactrack
        visited[next.to] = false;
        path.pop_back();
    }
    return false;
}

// visit the start node at first
bool dfs_postorder(int curr, int end, bool visited[], std::vector<int>& path) {
    // target condition
    if (curr == end) { print(path); return true; }

    for (auto& next : adjList[curr])
        if (!visited[next.to]) {
            // visit the node (post order)
            visited[next.to] = true;
            path.push_back(next.to);

            if (dfs_postorder(next.to, end, visited, path))
                return true;

            // Bactrack
            visited[next.to] = false;
            path.pop_back();
        }
    return false;
}

struct qEdge {
    int to;
    bool visited[MAX_NODES];
    std::vector<int> path;

    qEdge(int to, bool visited[], std::vector<int>& path) {
        this->to = to;
        for (int i = 0; i < MAX_NODES; i++) this->visited[i] = visited[i];
        for (int x : path) this->path.push_back(x);
    }
};

bool bfs_preorder(int start, int end, bool visited[], std::vector<int>& path) {
    std::queue<qEdge> Q;
    Q.push({ start, visited, path });

    int flag = false;
    while(!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.visited[curr.to]) continue;
        // visit the node (preorder)
        curr.visited[curr.to] = true;
        curr.path.push_back(curr.to);

        // target condition
        if (curr.to == end) { print(curr.path); flag = false; break; }  // return true;

        for (auto& next: adjList[curr.to]) {
            Q.push({ next.to, curr.visited, curr.path });
            // Backtrack
            // curr.visited[next.to] = true;
            // curr.path.pop_back();
        }
    }
    return flag ? true : false;
}

// visit the start node at first
bool bfs_postorder(int start, int end, bool visited[], std::vector<int>& path) {
    std::queue<qEdge> Q;
    Q.push({ start, visited, path });

    bool flag = false;
    while(!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.to == end) { print(curr.path); flag = true; break; } // return true;

        for (auto& next: adjList[curr.to])
            if (!visited[next.to]) {
                // visit the node (preorder)
                curr.visited[next.to] = true;
                curr.path.push_back(next.to);

                Q.push({ next.to, curr.visited, curr.path });

                // Backtrack
                curr.visited[next.to] = true;
                curr.path.pop_back();
            }
    }
    return flag ? true : false;
}

int main()
{
    bool visited[MAX_NODES];
    std::vector<int> path;
    int start = 0, end = 7;

    createGraph();

    if (1) {
        printf("\n*** DFS [Preorder] ***\n");
        initGraph(visited, path);
        dfs_preorder(start, end, visited, path);

        printf("\n*** DFS [Post Order] ***\n");
        initGraph(visited, path);
        visited[start] = true;
        path.push_back(start);
        dfs_postorder(start, end, visited, path);
    }
    if (1) {
        printf("\n*** BFS [Preorder] ***\n");
        initGraph(visited, path);
        bfs_preorder(start, end, visited, path);

        printf("\n*** BFS [Post Order] ***\n");
        initGraph(visited, path);
        visited[start] = true;
        path.push_back(start);
        bfs_postorder(start, end, visited, path);
    }


    return 0;
}
#endif