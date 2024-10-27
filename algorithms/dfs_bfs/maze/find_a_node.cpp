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

struct Position { int row, col; };

bool dfs_preorder(const Position& curr, const Position& target) {
    if (visited[curr.row][curr.col]) return false;
    visited[curr.row][curr.col] = cnt++;
    if (curr.row == target.row && curr.col == target.col) return true;

    for (int k = 0; k < 4; k++) {
        Position next = { curr.row + dr[k], curr.col + dc[k] };
        if (next.row < 0 || next.row >= N) continue;
        if (next.col < 0 || next.col >= M) continue;
        if (!visited[next.row][next.col] && map[next.row][next.col] == 0)
            if (dfs_preorder(next, target)) return true;
    }
    return false;
}

// visited[start.row][start.col] = cnt++;
bool dfs_postorder(const Position& curr, const Position& target) {
    for (int k = 0; k < 4; k++) {
        Position next = { curr.row + dr[k], curr.col + dc[k] };
        if (next.row < 0 || next.row >= N) continue;
        if (next.col < 0 || next.col >= M) continue;
        if (!visited[next.row][next.col] && map[next.row][next.col] == 0) {
            visited[next.row][next.col] = cnt++;
            if (next.row == target.row && next.col == target.col) return true;
            if (dfs_postorder(next, target)) return true;
        }
    }
    return false;
}

bool bfs_preorder(const Position& start, const Position& target) {
    std::queue<Position> Q;
    Q.push({ start.row, start.col });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (visited[curr.row][curr.col]) continue;
            visited[curr.row][curr.col] = cnt++;

        if (curr.row == target.row && curr.col == target.col) return true;

        for (int k = 0; k < 4; k++) {
            Position next = { curr.row + dr[k], curr.col + dc[k] };
            if (next.row < 0 || next.row >= N) continue;
            if (next.col < 0 || next.col >= M) continue;
            if (!visited[next.row][next.col] && map[next.row][next.col] == 0)
                Q.push({ next.row, next.col });
        }
    }
    return false;
}

// visited[start.row][start.col] = cnt++;
bool bfs_postorder(const Position& start, const Position& target) {
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
                if (next.row == target.row && next.col == target.col) return true;
                Q.push({ next.row, next.col });
            }
        }
    }
    return false;
}

int main()
{
    Position start = { 0, 5 }, target = { 6, 6};
    printMap(map);

    if (1) {
        initMap();
        dfs_preorder(start, target);
        printMap(visited);
    }
    if (1) {
        initMap();
        visited[start.row][start.col] = cnt++;
        dfs_postorder(start, target);
        printMap(visited);
    }
    if (1) {
        initMap();
        bfs_preorder(start, target);
        printMap(visited);
    }
    if (1) {
        initMap();
        visited[start.row][start.col] = cnt++;
        bfs_postorder(start, target);
        printMap(visited);
    }

    return  0;
}