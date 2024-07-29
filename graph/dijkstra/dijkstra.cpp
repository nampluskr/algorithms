#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define MAX_NODES   10
#define INF         1e6

struct Edge {
    int to, cost;
    bool operator<(const Edge& edge) const { return cost > edge.cost; }
};
vector<Edge> adjList[MAX_NODES];
int visited[MAX_NODES];     // for BFS
int dist[MAX_NODES];        // for Dijkstra
int parent[MAX_NODES];

void add_edge(int from, int to, int cost = 0) {
    adjList[from].push_back({ to, cost });
}

void create_graph() {
    add_edge(0, 1, 16);  add_edge(0, 2, 13);
    add_edge(1, 2, 10);  add_edge(1, 3, 12);
    add_edge(2, 1, 4);   add_edge(2, 4, 14);
    add_edge(3, 2, 9);   add_edge(3, 5, 20);
    add_edge(4, 3, 7);   add_edge(4, 5, 4);
}

// shorted path (unweighted edge)
void bfs(int start, int end) {
    queue<Edge> que;
    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    visited[start] = 1;
    que.push({ start });
    while (!que.empty()) {
        auto cur = que.front(); que.pop();

        for (const auto& next: adjList[cur.to]) {
            if (visited[next.to]) continue;
            visited[next.to] = 1;
            que.push({ next.to });
        }
    }
}


// Min cost path (weighted edge)
void dijkstra(int start, int end) {
    // init
    priority_queue<Edge> pq;
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[start] = 0;
    pq.push({ start, dist[start] });    parent[start] = -1;
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();

        if (cur.to == end) break;

        if (dist[cur.to] < cur.cost) continue;
        for (const auto& next: adjList[cur.to])
            if (dist[next.to] > cur.cost + next.cost) {
                dist[next.to] = cur.cost + next.cost;
                pq.push({ next.to, dist[next.to] }); parent[next.to] = cur.to;
            }
    }
}

int main()
{
    create_graph();
    dijkstra(0, 5);
    printf("%d\n", dist[5]);

    bfs(0, 5);


    return 0;
}