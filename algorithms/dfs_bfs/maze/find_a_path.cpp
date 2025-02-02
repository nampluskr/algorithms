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

struct Position {
    int row, col;
    int visited[N][M];

    Position(int row, int col) { this->row = row, this->col = col; }
    Position(int row, int col, int visited[N][M]) {
        this->row = row, this->col = col;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                this->visited[i][j] = visited[i][j];
    }
};

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

bool dfs_preorder(const Position& curr, const Position& target) {
    if (visited[curr.row][curr.col]) return false;
    visited[curr.row][curr.col] = cnt++;

    if (curr.row == target.row && curr.col == target.col) { printMap(visited); return true; }

    for (int k = 0; k < 4; k++) {
        Position next = { curr.row + dr[k], curr.col + dc[k] };
        if (next.row < 0 || next.row >= N) continue;
        if (next.col < 0 || next.col >= M) continue;
        if (!visited[next.row][next.col] && map[next.row][next.col] == 0) {
            if (dfs_preorder(next, target)) return true;
            visited[next.row][next.col] = 0;    // backtrack
        }
    }
    return false;
}

// visited[start.row][start.col] = cnt++;
bool dfs_postorder(const Position& curr, const Position& target) {
    if (curr.row == target.row && curr.col == target.col) { printMap(visited); return true; }

    for (int k = 0; k < 4; k++) {
        Position next = { curr.row + dr[k], curr.col + dc[k] };
        if (next.row < 0 || next.row >= N) continue;
        if (next.col < 0 || next.col >= M) continue;
        if (!visited[next.row][next.col] && map[next.row][next.col] == 0) {
            visited[next.row][next.col] = visited[curr.row][curr.col] + 1;
            // visited[next.row][next.col] = cnt++;
            if (dfs_postorder(next, target)) return true;
            visited[next.row][next.col] = 0;    // backtrack
        }
    }
    return false;
}

bool bfs_preorder(const Position& start, const Position& target) {
    std::queue<Position> Q;
    Q.push({ start.row, start.col, visited });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.visited[curr.row][curr.col]) continue;
            curr.visited[curr.row][curr.col] = cnt++;

        if (curr.row == target.row && curr.col == target.col) { printMap(curr.visited); return true; }

        for (int k = 0; k < 4; k++) {
            Position next = { curr.row + dr[k], curr.col + dc[k] };
            if (next.row < 0 || next.row >= N) continue;
            if (next.col < 0 || next.col >= M) continue;
            if (!curr.visited[next.row][next.col] && map[next.row][next.col] == 0)
                Q.push({ next.row, next.col, curr.visited });
                // curr.visited[next.row][next.col] = 0;
        }
    }
    return false;
}

// visited[start.row][start.col] = cnt++;
bool bfs_postorder(const Position& start, const Position& target) {
    std::queue<Position> Q;
    Q.push({ start.row, start.col, visited });

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        if (curr.row == target.row && curr.col == target.col) { printMap(curr.visited); return false; }

        for (int k = 0; k < 4; k++) {
            Position next = { curr.row + dr[k], curr.col + dc[k] };
            if (next.row < 0 || next.row >= N) continue;
            if (next.col < 0 || next.col >= M) continue;
            if (!curr.visited[next.row][next.col] && map[next.row][next.col] == 0) {
                // curr.visited[next.row][next.col] = curr.visited[curr.row][curr.col] + 1;
                curr.visited[next.row][next.col] = cnt++;
                Q.push({ next.row, next.col, curr.visited });
                curr.visited[next.row][next.col] = 0;
            }
        }
    }
    return false;
}

int main()
{
    Position start = { 0, 5 }, target = { 6, 6 };
    // printMap(map);

    if (1) {
        initMap();
        dfs_preorder(start, target);
    }
    if (1) {
        initMap();
        visited[start.row][start.col] = cnt++;
        dfs_postorder(start, target);
    }
    if (1) {
        initMap();
        bfs_preorder(start, target);
    }
    if (1) {
        initMap();
        visited[start.row][start.col] = cnt++;
        bfs_postorder(start, target);
    }

    return  0;
}