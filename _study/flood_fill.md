### [flood_fill.cpp] dfs (recursive / iterative), bfs (iterative)

```cpp
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define MAX_NODES   11

// 필수
struct Edge { int x, cost; };
vector<Edge> adjList[MAX_NODES];
int visited[MAX_NODES];

// 보조
int parent[MAX_NODES];
vector<int> path;
vector<int> hist;

void add_edge(int s, int e, int cost = 0) {
    adjList[s].push_back({ e, cost });
    adjList[e].push_back({ s, cost });
}

void create_graph() {
    add_edge(0, 1); add_edge(0, 2);
    add_edge(1, 3); add_edge(1, 4);
    add_edge(2, 5); add_edge(2, 6);
    add_edge(3, 7);
    add_edge(4, 8);
    add_edge(5, 9);
    add_edge(6, 10);
}

void init_visited() {
    path.clear();
    hist.clear();
    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
}

void show(vector<int> vec) {
    printf(">> "); 
    for (int i = 0; i < vec.size() - 1; i++)
        printf("%d->", vec[i]);
    printf("%d\n", vec.back());
}

void trace(int start, int end) {
    if (parent[end] == -1) return;
    if (end == start) path.push_back(end);
    trace(start, parent[end]);
    path.push_back(end);
}

void show_path(int start, int end) {
    path.clear();
    path.push_back(start);
    trace(start, end);
    show(path);
}

void dfs_recur1(int cur) {
    if (!visited[cur]) {
        // 노드 방문 처리 (cur)
        visited[cur] = 1; hist.push_back(cur);

        // 종료 조건 확인 (cur)

        for (const auto& next : adjList[cur]) {
            if (visited[next.x]) continue;
            dfs_recur1(next.x); parent[next.x] = cur;
        }
    }
}

void dfs_recur2(int cur) {
    // 종료 조건 확인 (cur)

    for (const auto& next : adjList[cur]) {
        if (visited[next.x]) continue;
        // 노드 방문 처리 (next)
        visited[next.x] = 1; hist.push_back(next.x);
        dfs_recur2(next.x); parent[next.x] = cur;
    }
}

void dfs_iter1(int start) {
    stack<Edge> stk;
    init_visited();

    stk.push({ start }); parent[start] = -1;

    while (!stk.empty()) {
        auto cur = stk.top(); stk.pop();

        if (!visited[cur.x]) {
            // 노드 방문 처리 (cur)
            visited[cur.x] = 1; hist.push_back(cur.x);

            // 종료 조건 확인 (cur)

            for (const auto& next : adjList[cur.x]) {
                if (visited[next.x]) continue;
                stk.push({ next.x }); parent[next.x] = cur.x;
            }
        }
    }
}

void dfs_iter2(int start) {
    stack<Edge> stk;
    init_visited();

    visited[start] = 1; hist.push_back(start);
    stk.push({ start }); parent[start] = -1;

    while (!stk.empty()) {
        auto cur = stk.top(); stk.pop();

        // 종료 조건 확인 (cur)

        for (const auto& next : adjList[cur.x]) {
            if (visited[next.x]) continue;
            // 노드 방문 처리 (next)
            visited[next.x] = 1; hist.push_back(next.x);
            stk.push({ next.x }); parent[next.x] = cur.x;
        }
    }
}

void bfs1(int start) {
    queue<Edge> que;
    init_visited();

    que.push({ start }); parent[start] = -1;

    while (!que.empty()) {
        auto cur = que.front(); que.pop();

        if (!visited[cur.x]) {
            // 노드 방문 처리 (cur)
            visited[cur.x] = 1; hist.push_back(cur.x);

            // 종료 조건 확인 (cur)

            for (const auto& next : adjList[cur.x]) {
                if (visited[next.x]) continue;
                que.push({ next.x }); parent[next.x] = cur.x;
            }
        }
    }
}

void bfs2(int start) {
    queue<Edge> que;
    init_visited();

    visited[start] = 1; hist.push_back(start);
    que.push({ start }); parent[start] = -1;

    while (!que.empty()) {
        auto cur = que.front(); que.pop();

        // 종료 조건 확인 (cur)

        for (const auto& next : adjList[cur.x]) {
            if (visited[next.x]) continue;
            // 노드 방문 처리 (next)
            visited[next.x] = 1; hist.push_back(next.x);
            que.push({ next.x }); parent[next.x] = cur.x;
        }
    }
}

int main()
{
    create_graph();

    printf("\n[DFS - Recursive-1]\n");
    init_visited();
    dfs_recur1(0);
    show(hist); show_path(0, 9);
    
    printf("\n[DFS - Recursive-2]\n");
    init_visited();
    visited[0] = 1; hist.push_back(0);
    dfs_recur2(0);
    show(hist); show_path(0, 9);

    printf("\n[DFS - Iterative-1]\n");
    init_visited();
    dfs_iter1(0);
    show(hist); show_path(0, 9);

    printf("\n[DFS - Iterative-2]\n");
    init_visited();
    dfs_iter2(0);
    show(hist); show_path(0, 9);

    printf("\n[BFS - Iterative-1]\n");
    bfs1(0);
    show(hist); show_path(0, 9);

    printf("\n[BFS - Iterative-2]\n");
    bfs2(0);
    show(hist); show_path(0, 9);


    return 0;
}
```
