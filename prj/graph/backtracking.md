### BFS

```cpp
void find_all_paths(const vector<vector<int>>& graph, int startNode, int endNode) {
    vector<bool> visited(graph.size(), false); 
    vector<int> path; // Current path being explored

    queue<pair<vector<int>, int>> q; 
    q.push({path, startNode}); 
    visited[startNode] = true;

    while (!q.empty()) {
        vector<int> currentPath = q.front().first; // Path so far
        int currentNode = q.front().second;  // Current node
        q.pop();

        if (currentNode == endNode) { 
            cout << "Path found: ";
            for (int node : currentPath) {
                cout << node << " ";
            }
            cout << endl;
        } else {
            for (int neighbor : graph[currentNode]) {
                if (!visited[neighbor]) {
                    path.push_back(neighbor); // Add neighbor to path 
                    visited[neighbor] = true;    
                    q.push({currentPath, neighbor});  // Explore neighbor
                    visited[neighbor] = true;   
                }
            }
        }
    }
}

### DFS

```cpp
void find_all_paths(const vector<vector<int>>& graph, int startNode, int endNode) {
    vector<bool> visited(graph.size(), false); 
    vector<int> path; // Current path being explored

    dfs(graph, startNode, endNode, visited, path);
}

void dfs(const vector<vector<int>>& graph, int currentNode, int endNode, vector<bool>& visited, vector<int>& currentPath) {
    visited[currentNode] = true;
    currentPath.push_back(currentNode); 

    if (currentNode == endNode) { // Found a path to the end node
        cout << "Path found: ";
        for (int node : currentPath) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        for (int neighbor : graph[currentNode]) {
            if (!visited[neighbor]) { // Explore unvisited neighbors
                dfs(graph, neighbor, endNode, visited, currentPath); 
            }
        }
    }

    // Backtrack: Remove the current node from the path after exploring its neighbors.
    currentPath.pop_back();
    visited[currentNode] = false;  
}
```
