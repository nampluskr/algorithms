#include <cstdio>
#include <vector>
#include <queue>

#define MAX_NODES 20

struct Edge { int to, cost; };
std::vector<Edge> adjList[MAX_NODES];

void addEdge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
    //adjList[to].push_back({ from, cost });
}

void print(const std::vector<int>& path) {
    printf(">> ");
    for (int node : path) printf("[%d]->", node);
    printf("\n");
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

void init(bool visited[], std::vector<int>& path) {
    for (int i = 0; i < MAX_NODES; i++) visited[i] = false;
    path.clear();
    printf("==========================================\n");
}

void dfs_preorder(int curr, int end, bool visited[], std::vector<int>& path) {
    if (visited[curr]) return;

    // visit the node
    visited[curr] = true;
    path.push_back(curr);

    // 종료 조건
    if (curr == end) { print(path); return; }

    for (auto& next : adjList[curr]) {
        //if (!visited[next.to]) {  // pruning
            dfs_preorder(next.to, end, visited, path);
            // Bracktrack
            path.pop_back();
            visited[next.to] = false;
        //}
    }
}

void dfs_postorder(int curr, int end, bool visited[], std::vector<int>& path) {
    // 종료 조건
    if (curr == end) { print(path); return; }

    for (auto& next : adjList[curr])
        if (!visited[next.to]) {
            // visit the node
            visited[next.to] = true;
            path.push_back(next.to);

            dfs_postorder(next.to, end, visited, path);

            // Backtrack
            path.pop_back();
            visited[next.to] = false;
        }
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

void bfs_preorder(int start, int end, bool visited[], std::vector<int>& path) {
    std::queue<qEdge> Q; 
    Q.push({ start, visited, path });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.visited[curr.to]) continue;
        // visit the node
        curr.visited[curr.to] = true;
        curr.path.push_back(curr.to);

        // 종료 조건
        if (curr.to == end) { print(curr.path); continue; }

        for (auto next : adjList[curr.to]) {
            //if (!curr.visited[next.to]) { // pruning
                Q.push({ next.to, curr.visited, curr.path });
                // Backtrack
                //curr.path.pop_back();
                //curr.visited[next.to] = false;
            //}
        }
    }
}

void bfs_postorder(int start, int end, bool visited[], std::vector<int>& path) {
    std::queue<qEdge> Q;
    visited[start] = true;
    path.push_back(start);
    Q.push({ start, visited, path }); 

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        // 종료 조건
        if (curr.to == end) { print(curr.path); continue; }

        for (auto next : adjList[curr.to])
            if (!curr.visited[next.to]) {
                // visit the node
                curr.visited[next.to] = true;
                curr.path.push_back(next.to);

                Q.push({ next.to, curr.visited, curr.path });

                // Backtrack
                curr.path.pop_back();
                curr.visited[next.to] = false;
            }
    }
}


int main()
{
    bool visited[MAX_NODES];
    std::vector<int> path;
    int start = 0, end = 5;

    createGraph();

    init(visited, path);
    dfs_preorder(start, end, visited, path);

    init(visited, path);
    visited[start] = true;
    path.push_back(start);
    dfs_postorder(start, end, visited, path);

    init(visited, path);
    bfs_preorder(start, end, visited, path);

    init(visited, path);
    bfs_postorder(start, end, visited, path);

    return 0;
}
