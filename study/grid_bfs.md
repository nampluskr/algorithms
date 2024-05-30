### [특정 깊이까지만 탐색] target = depth from the initial point

```cpp
// target: depth from initial point
void bfs1(int row, int col, int target) {
	queue<Point> que;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = -1;

	visited[row][col] = 0;
	que.push({ row, col });

	while (!que.empty()) {
		Point cur = que.front(); que.pop();

		// 종료 조건
		if (visited[cur.row][cur.col] == target) return;

		for (int k = 0; k < 4; k++) {
			Point next = { cur.row + dr[k], cur.col + dc[k] };

			if (next.row < 0 || next.row >= N) continue;
			if (next.col < 0 || next.col >= M) continue;
			if (visited[next.row][next.col] != -1) continue;
			if (map[next.row][next.col] == 1) continue;

			visited[next.row][next.col] = visited[cur.row][cur.col] + 1;
			que.push({ next.row, next.col });
		}
	}
}
```

### [특정 개수까지만 탐색] target = number of points

```cpp
// target: number of points
void bfs2(int row, int col, int target) {
	priority_queue<Point> pq;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = 0;

	int cnt = 1;
	visited[row][col] = cnt++;
	pq.push({ row, col, 0 });

	while (!pq.empty()) {
		Point cur = pq.top(); pq.pop();

		for (int k = 0; k < 4; k++) {
			if (cnt > target) break;

			Point next = { cur.row + dr[k], cur.col + dc[k] };
			next.dist = abs(next.row - row) + abs(next.col - col);

			if (next.row < 0 || next.row >= N) continue;
			if (next.col < 0 || next.col >= M) continue;
			if (visited[next.row][next.col] != 0) continue;
			if (map[next.row][next.col] == 1) continue;

			visited[next.row][next.col] = cnt++;
			pq.push(next);
		}
		if (cnt > target) break;
	}
}
```

### [main.cpp] test code

```cpp
#include <queue>
using namespace std;

#define N	7
#define M	11

int map[N][M] = {
	{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
};
int visited[N][M];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

struct Point { 
	int row, col, dist;
	bool operator<(const Point& pt) const {
		if (dist != pt.dist) return dist > pt.dist;
		if (row != pt.row) return row > pt.row;
		return col > pt.col;
	}
};

void display(int map[N][M]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			printf("%2d ", map[i][j]);
		printf("\n");
	}
	printf("\n");
}

void init() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			map[i][j] = 0;
}


int main()
{
	display(map);

	//init();
	bfs1(0, 5, 5);
	display(visited);

	//init();
	bfs2(0, 5, 13);
	display(visited);

	return 0;
}
```
