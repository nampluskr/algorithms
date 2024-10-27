#include <cstdio>
#include <queue>

#define N   7
#define M   11

int map[N][M] = {
    { -1, -1, -1, -1, -1,  0, -1, -1, -1, -1, -1, },
    { -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, },
    { -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, },
    { -1,  0,  0,  0, -1,  0, -1,  0, -1,  0, -1, },
    { -1,  0, -1,  0, -1,  0, -1, -1, -1,  0, -1, },
    { -1,  0, -1,  0,  0,  0,  0,  0,  0,  0, -1, },
    { -1, -1, -1, -1, -1, -1,  0, -1, -1, -1, -1, },
};
int visited[N][M];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int cnt;
struct Position { int row, col; };

void printMap(int map[N][M]) {
    printf("\n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++)
            printf("%2d ", map[i][j]);
        printf("\n");
    }
}

void initMap() {
    cnt = 1;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++)
            visited[i][j] = 0;
    }
}

void dfs_preorder(const Position& curr) {
    if (visited[curr.row][curr.col]) return;
    visited[curr.row][curr.col] = cnt++;

    for (int k = 0; k < 4; k++) {
        Position next = { curr.row + dr[k], curr.col + dc[k] };
        if (next.row < 0 || next.row >= N) continue;
        if (next.col < 0 || next.col >= M) continue;
        if (!visited[next.row][next.col] && map[next.row][next.col] == 0)
            dfs_preorder(next);
    }
}

// visited[start.row][start.col] = cnt++; the start node at first
void dfs_postorder(const Position& curr) {
    for (int k = 0; k < 4; k++) {
        Position next = { curr.row + dr[k], curr.col + dc[k] };
        if (next.row < 0 || next.row >= N) continue;
        if (next.col < 0 || next.col >= M) continue;
        if (!visited[next.row][next.col] && map[next.row][next.col] == 0) {
            visited[next.row][next.col] = cnt++;
            dfs_postorder(next);
        }
    }
}

void bfs_preorder(const Position& start) {
    std::queue<Position> Q;
    Q.push({ start.row, start.col });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr.row][curr.col]) continue;
            visited[curr.row][curr.col] = cnt++;

        for (int k = 0; k < 4; k++) {
            Position next = { curr.row + dr[k], curr.col + dc[k] };
            if (next.row < 0 || next.row >= N) continue;
            if (next.col < 0 || next.col >= M) continue;
            if (!visited[next.row][next.col] && map[next.row][next.col] == 0)
                Q.push({ next.row, next.col });
        }
    }
}

// visited[start.row][start.col] = cnt++;
void bfs_postorder(const Position& start) {
    std::queue<Position> Q;
    Q.push({ start.row, start.col });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        for (int k = 0; k < 4; k++) {
            Position next = { curr.row + dr[k], curr.col + dc[k] };
            if (next.row < 0 || next.row >= N) continue;
            if (next.col < 0 || next.col >= M) continue;
            if (!visited[next.row][next.col] && map[next.row][next.col] == 0) {
                visited[next.row][next.col] = cnt++;
                Q.push({ next.row, next.col });
            }
        }
    }
}

int main()
{
    Position start = { 0, 5 };
    printMap(map);

    if (1) {
        initMap();
        dfs_preorder(start);
        printMap(visited);
    }
    if (1) {
        initMap();
        visited[start.row][start.col] = cnt++;
        dfs_postorder(start);
        printMap(visited);
    }
    if (1) {
        initMap();
        bfs_preorder(start);
        printMap(visited);
    }
    if (1) {
        initMap();
        visited[start.row][start.col] = cnt++;
        bfs_postorder(start);
        printMap(visited);
    }

    return  0;
}