### Find all nodes

```cpp
// [Tree] Find all nodes
#if 0
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

#define MAX_NODES   100

struct Edge { int to, cost; };
std::vector<Edge> adjList[MAX_NODES];
int parent[MAX_NODES];
bool visited[MAX_NODES];
std::vector<int> path;

void addEdge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
    adjList[to].push_back({ from, cost });
}

void createGraph() {
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

void initGraph() {
    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    path.clear();
}

void visitNode(int nodeIdx) {
    visited[nodeIdx] = true;
    path.push_back(nodeIdx);
}

void dfs_preorder(int curr) {
    if (visited[curr]) return;
    visitNode(curr);    // preorder

    for (auto& next : adjList[curr]) {
        if (!visited[next.to]) {
            parent[next.to] = curr;
            dfs_preorder(next.to);
        }
    }
}

void dfs_postorder(int curr) {

    for (auto& next : adjList[curr]) {
        if (!visited[next.to]) {
            visitNode(next.to); // post order

            parent[next.to] = curr;
            dfs_postorder(next.to);
        }
    }
}

void bfs_preorder(int start) {
    std::queue<Edge> Q;
    Q.push({ start, 0 });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr.to]) continue;
        visitNode(curr.to);    // preorder

        for (auto& next : adjList[curr.to])
            if (!visited[next.to]) {
                parent[next.to] = curr.to;
                Q.push(next);
            }
    }
}

void bfs_postorder(int start) {
    std::queue<Edge> Q;
    Q.push({ start, 0 });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        for (auto& next : adjList[curr.to])
            if (!visited[next.to]) {
                visitNode(next.to);    // postorder
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
        visitNode(curr.to);    // preorder

        for (auto& next : adjList[curr.to])
            if (!visited[next.to]) {
                parent[next.to] = curr.to;
                S.push(next);
            }
    }
}

void stack_postorder(int start) {
    std::stack<Edge> S;
    S.push({ start, 0 });

    while (!S.empty()) {
        auto curr = S.top(); S.pop();

        for (auto& next : adjList[curr.to])
            if (!visited[next.to]) {
                visitNode(next.to);    // postorder
                parent[next.to] = curr.to;
                S.push(next);
            }
    }
}

int main()
{
    createGraph();
    int start = 0;

    if (1) {
        printf("\n*** DFS-preorder [find all nodes] ***\n");
        initGraph();
        dfs_preorder(start);
        print(path);
    }
    if (1) {
        printf("\n*** DFS-post order [find all nodes] ***\n");
        initGraph();
        visitNode(start);
        dfs_postorder(start);
        print(path);
    }
    if (1) {
        printf("\n*** BFS-predorder [find all nodes] ***\n");
        initGraph();
        bfs_preorder(start);
        print(path);
    }
    if (1) {
        printf("\n*** BFS-post order [find all nodes] ***\n");
        initGraph();
        visitNode(start);
        bfs_postorder(start);
        print(path);
    }
    if (1) {
        printf("\n*** Stack-predorder [find all nodes] ***\n");
        initGraph();
        stack_preorder(start);
        print(path);
    }
    if (1) {
        printf("\n*** Stack-post order [find all nodes] ***\n");
        initGraph();
        visitNode(start);
        stack_postorder(start);
        print(path);
    }


    return 0;
}
#endif
```

### Find a node

```cpp
// [Tree] Find a node
#if 1
#include <cstdio>
#include <vector>
#include <queue>

#define MAX_NODES   100

struct Edge { int to, cost; };
std::vector<Edge> adjList[MAX_NODES];
int parent[MAX_NODES];
bool visited[MAX_NODES];
std::vector<int> path;

void addEdge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
    adjList[to].push_back({ from, cost });
}

void createGraph() {
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

void initGraph() {
    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    path.clear();
}

void visitNode(int nodeIdx) {
    visited[nodeIdx] = true;
    path.push_back(nodeIdx);
}

bool dfs_preorder(int curr, int end) {
    if (visited[curr]) return false;
    visitNode(curr);                // preorder

    if (curr == end) return true;   // target condition

    for (auto& next : adjList[curr]) {
        if (!visited[next.to]) {
            parent[next.to] = curr;
            if (dfs_preorder(next.to, end)) return true;
        }
    }
    return false;
}

// visit initial node
bool dfs_postorder(int curr, int end) {
    //if (curr == end) return true;   // target condition

    for (auto& next : adjList[curr]) {
        if (!visited[next.to]) {
            visitNode(next.to);     // post order
            if (next.to == end) return true;   // target condition

            parent[next.to] = curr;
            if (dfs_postorder(next.to, end)) return true;
        }
    }
    return false;
}

bool bfs_preorder(int start, int end) {
    std::queue<Edge> Q;
    Q.push({ start, 0 });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr.to]) continue;
        visitNode(curr.to);                 // preorder

        if (curr.to == end) return true;    // target condition

        for (auto& next : adjList[curr.to])
            if (!visited[next.to]) {
                parent[next.to] = curr.to;
                Q.push(next);
            }
    }
    return false;
}

bool bfs_postorder(int start, int end) {
    std::queue<Edge> Q;
    Q.push({ start, 0 });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        //if (curr.to == end) return true;    // target condition

        for (auto& next : adjList[curr.to])
            if (!visited[next.to]) {
                visitNode(next.to);                 // postorder
                if (next.to == end) return true;    // target condition

                parent[next.to] = curr.to;
                Q.push(next);
            }
    }
    return false;
}

int main()
{
    createGraph();
    int start = 0, end = 7;

    if (1) {
        printf("\n*** DFS [find all nodes] ***\n");
        initGraph();
        dfs_preorder(start, end);
        print(path);
    }
    if (1) {
        printf("\n*** DFS [find all nodes] ***\n");
        initGraph();
        visitNode(start);
        dfs_postorder(start, end);
        print(path);
    }
    if (1) {
        printf("\n*** BFS [find all nodes] ***\n");
        initGraph();
        bfs_preorder(start, end);
        print(path);
    }
    if (1) {
        printf("\n*** BFS [find all nodes] ***\n");
        initGraph();
        visitNode(start);
        bfs_postorder(start, end);
        print(path);
    }



    return 0;
}
#endif
```

### Find all paths (Backtracking)

```cpp
// Find all paths
#if 1
#include <cstdio>
#include <vector>
#include <queue>

#define MAX_NODES   100

struct Edge {
    int to, cost;
    std::vector<int> path;

    Edge(int to, int cost) {
        this->to = to;
        this->cost = cost;
        this->path.clear();
    }
    Edge(int to, int cost, std::vector<int>& path) {
        this->to = to;
        this->cost = cost;
        for (int x : path) this->path.push_back(x);
    }
};
std::vector<Edge> adjList[MAX_NODES];
bool visited[MAX_NODES];
std::vector<int> path;

void addEdge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
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

void initGraph() {
    for (int i = 0; i < MAX_NODES; i++) visited[i] = false;
    path.clear();
}

void dfs_preorder(int curr, int end) {
    if (!visited[curr]) {
        // visit node (preorder)
        visited[curr] = true;
        path.push_back(curr);

        // target condition
        if (curr == end) { print(path); return; }

        for (auto& next : adjList[curr]) {
            if (!visited[next.to]) {
                dfs_preorder(next.to, end);

                // Bactrack
                visited[next.to] = false;
                path.pop_back();
            }
        }
    }
}


void dfs_postorder(int curr, int end) {
    // target condition
    if (curr == end) { print(path); return; } 

    for (auto& next : adjList[curr]) {
        if (!visited[next.to]) {
            // visit node (post order)
            visited[next.to] = true; 
            path.push_back(next.to);

            dfs_postorder(next.to, end);

            // Bactrack
            visited[next.to] = false;
            path.pop_back();
        }
    }
}

void bfs_postorder(int start, int end) {
    std::queue<Edge> Q;
    Q.push({ start, 0, path });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        // target condition
        if (curr.to == end) { print(curr.path); continue; }

        for (auto& next : adjList[curr.to])
            if (!visited[next.to]) {
                // visit node (post order)
                visited[next.to] = true;
                curr.path.push_back(next.to);

                Q.push({ next.to, next.cost, curr.path });
                // Backtrack
                visited[next.to] = false;
                curr.path.pop_back();
            }
    }
}


int main()
{
    int start = 0, end = 7;

    createGraph();

    if (1) {
        printf("\n*** DFS [Preorder] ***\n");
        initGraph();
        dfs_preorder(start, end);
    }
    if (1) {
        printf("\n*** DFS [Post Order] ***\n");
        initGraph();
        visited[start] = true;
        path.push_back(start);
        dfs_postorder(start, end);
    }
    if (1) {
        printf("\n*** BFS [Post Order] ***\n");
        initGraph();
        visited[start] = true;
        path.push_back(start);
        bfs_postorder(start, end);
    }


    return 0;
}
#endif
```

### Find a path (Backtracking)

```cpp
// Find a path
#if 0
#include <cstdio>
#include <vector>
#include <queue>

#define MAX_NODES   100

struct Edge {
    int to, cost;
    std::vector<int> path;

    Edge(int to, int cost) {
        this->to = to;
        this->cost = cost;
        this->path.clear();
    }
    Edge(int to, int cost, std::vector<int>& path) {
        this->to = to;
        this->cost = cost;
        this->path.clear();
        for (int x : path) this->path.push_back(x);
    }
};
std::vector<Edge> adjList[MAX_NODES];
bool visited[MAX_NODES];
std::vector<int> path;

void addEdge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
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

void initGraph() {
    for (int i = 0; i < MAX_NODES; i++) visited[i] = false;
    path.clear();
}

bool dfs_preorder(int curr, int end) {
    if (!visited[curr]) {
        // visit node (preorder)
        visited[curr] = true;
        path.push_back(curr);

        // target condition
        if (curr == end) { print(path); return true; }

        for (auto& next : adjList[curr]) {
            if (!visited[next.to]) {
                if (dfs_preorder(next.to, end)) return true;

                // Bactrack
                visited[next.to] = false;
                path.pop_back();
            }
        }
    }
    return false;
}


bool dfs_postorder(int curr, int end) {
    // target condition
    if (curr == end) { print(path); return true; }

    for (auto& next : adjList[curr]) {
        if (!visited[next.to]) {
            // visit node (post order)
            visited[next.to] = true;
            path.push_back(next.to);

            if (dfs_postorder(next.to, end)) return true;

            // Bactrack
            visited[next.to] = false;
            path.pop_back();
        }
    }
    return false;
}

// void bfs_preorder(int start, int end) {
//     std::queue<Edge> Q;
//     Q.push({ start, 0, path });

//     while (!Q.empty()) {
//         auto curr = Q.front(); Q.pop();

//         if (!visited[curr.to]) {
//             // visite node (preorder)
//             visited[curr.to] = true;
//             curr.path.push_back(curr.to);

//             // target condition
//             if (curr.to == end) { print(curr.path); continue; }

//             for (auto& next: adjList[curr.to])
//                 if (!visited[next.to]) {
//                     Q.push({ next.to, next.cost, curr.path });
//                     // Backtrack
//                     visited[next.to] = false;
//                     // curr.path.pop_back();
//                 }
//         }
//     }
// }

bool bfs_postorder(int start, int end) {
    std::queue<Edge> Q;
    Q.push({ start, 0, path });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        // target condition
        if (curr.to == end) { print(curr.path); return true; }

        for (auto& next : adjList[curr.to])
            if (!visited[next.to]) {
                // visit node (post order)
                visited[next.to] = true;
                curr.path.push_back(next.to);

                Q.push({ next.to, next.cost, curr.path });
                // Backtrack
                visited[next.to] = false;
                curr.path.pop_back();
            }
    }
    return false;
}


int main()
{
    int start = 0, end = 5;

    createGraph();

    if (1) {
        printf("\n*** DFS [Preorder] ***\n");
        initGraph();
        dfs_preorder(start, end);
    }
    if (1) {
        printf("\n*** DFS [Post Order] ***\n");
        initGraph();
        visited[start] = true;
        path.push_back(start);
        dfs_postorder(start, end);
    }
    // if (1) {
    //     printf("\n*** BFS [Pre Order] ***\n");
    //     initGraph();
    //     bfs_preorder(start, end);
    // }
    if (1) {
        printf("\n*** BFS [Post Order] ***\n");
        initGraph();
        visited[start] = true;
        path.push_back(start);
        bfs_postorder(start, end);
    }

    return 0;
}
#endif
```
