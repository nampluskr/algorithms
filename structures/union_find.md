### Union Find Reference Code

```cpp
#define MAX_SIZE 20000

// Reference Code
struct UnionFind {
    int root[MAX_SIZE];
    int rank[MAX_SIZE];

    void clear() {
        for (int i = 0; i < MAX_SIZE; i++) {
            root[i] = i;
            rank[i] = 0;
        }
    }
    int find(int x) {
        if (root[x] == x) return x;
        else root[x] = find(root[x]);   // 경로 압축
    }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (rank[x] < rank[y]) {
            root[x] = y;
        }
        else {
            root[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
};
```
