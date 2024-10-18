#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

#define MAX_NODES 100

vector<int> adjList[MAX_NODES];

bool visited[MAX_NODES];
int parent[MAX_NODES];
vector<int> path;

void addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void dfs_preorder(int curr) {
    if (visited[curr]) return;  // base condition

    // 노드 방문 (현재 노드 처리)
    visited[curr] = true;
    path.push_back(curr);

    for (int next : adjList[curr])
        if (!visited[next]) {
            parent[next] = curr;
            dfs_preorder(next);
        }
}

void dfs_postorder(int curr) {
    for (auto& next : adjList[curr])
        if (!visited[next]) {
            visited[next] = true;
            path.push_back(next);

            parent[next] = curr;
            dfs_postorder(next);
        }
}

void dfs_stack1(int start) {
    stack<int> S;
    S.push(start);

    while (!S.empty()) {
        int curr = S.top(); S.pop();

        if (visited[curr]) continue;
        visited[curr] = true;
        path.push_back(curr);

        for (int next: adjList[curr])
            if (!visited[next]) {
                parent[next] = curr;
                S.push(next);
            }
    }
}


void dfs_stack2(int start) {
    stack<int> S;
    S.push(start);

    visited[start] = true;
    path.push_back(start);

    while (!S.empty()) {
        int curr = S.top(); S.pop();

        for (int next : adjList[curr])
            if (!visited[next]) {
                visited[next] = true;
                path.push_back(next);

                parent[next] = curr;
                S.push(next);
            }
    }
}

void bfs_preorder(int start) {
    queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();

        if (visited[curr]) continue;
        visited[curr] = true;
        path.push_back(curr);

        for (int next : adjList[curr])
            if (!visited[next]) {
                parent[next] = curr;
                Q.push(next);
            }
    }
}


void bfs_postorder(int start) {
    queue<int> Q;
    Q.push(start);

    visited[start] = true;
    path.push_back(start);

    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();

        for (int next : adjList[curr])
            if (!visited[next]) {
                visited[next] = true;
                path.push_back(next);

                parent[next] = curr;
                Q.push(next);
            }
    }
}

void clear() {
    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    path.clear();
}

void printArray(const vector<int>& path) {
    printf(">> ");
    for (int u : path)
        printf("[%d]-", u);
    printf("\n");
}

int main()
{
    addEdge(0, 1); addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4); addEdge(2, 5); addEdge(2, 6);
    addEdge(3, 7); addEdge(3, 8);
    addEdge(6, 9);

    if (0) {
        clear();
        dfs_preorder(0);

        printArray(path);
    }

    if (0) {
        clear();
        visited[0] = true;
        path.push_back(0);
        dfs_postorder(0);

        printArray(path);
    }

    if (0) {
        clear();
        dfs_stack1(0);
        printArray(path);
    }

    if (0) {
        clear();
        dfs_stack2(0);
        printArray(path);
    }

    if (1) {
        clear();
        bfs_preorder(0);
        printArray(path);
    }

    if (1) {
        clear();
        bfs_postorder(0);
        printArray(path);
    }

    return 0;
}
