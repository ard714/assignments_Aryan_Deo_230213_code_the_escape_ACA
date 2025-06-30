#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
int n, m;
char maze[MAXN][MAXN];
bool visited[MAXN][MAXN];
pair<int, int> parent[MAXN][MAXN];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
pair<int, int> start, end_pos;

// TODO 1: Check if (x, y) is a valid move
bool isValid(int x, int y) {
    // Check if coordinates are within bounds
    if (x < 0 || x >= n || y < 0 || y >= m) {
        return false;
    }
    // Check if cell is not a wall and not visited
    if (maze[x][y] == '0' || visited[x][y]) {
        return false;
    }
    return true;
}

// TODO 2: BFS Implementation
void bfs() {
    queue<pair<int, int>> q;
    
    // Initialize visited array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
            parent[i][j] = {-1, -1};
        }
    }
    
    visited[start.first][start.second] = true;
    q.push(start);

    while (!q.empty()) {
        pair<int, int> cur = q.front(); 
        q.pop();
        
        if (cur == end_pos) {
            cout << "Path found using BFS!" << endl;
            return;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                parent[nx][ny] = cur;
                q.push({nx, ny});
            }
        }
    }
    
    cout << "No path found using BFS!" << endl;
}

// TODO 3: DFS Implementation
bool dfs(int x, int y) {
    // Mark current cell as visited
    visited[x][y] = true;
    
    // If we reached the end, return true
    if (x == end_pos.first && y == end_pos.second) {
        return true;
    }
    
    // Explore all 4 directions
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (isValid(nx, ny)) {
            parent[nx][ny] = {x, y};
            if (dfs(nx, ny)) {
                return true;
            }
        }
    }
    
    return false;
}

// TODO 4: Reconstruct and print the path
void reconstructPath(pair<int, int> end_point) {
    vector<pair<int, int>> path;
    pair<int, int> current = end_point;
    
    // Follow parent links backward from end to start
    while (current.first != -1 && current.second != -1) {
        path.push_back(current);
        current = parent[current.first][current.second];
    }
    
    // Reverse the path to get start to end
    reverse(path.begin(), path.end());
    
    if (path.empty() || path[0] != start) {
        cout << "No valid path found!" << endl;
        return;
    }
    
    cout << "Path found! Length: " << path.size() << endl;
    cout << "Path coordinates: ";
    for (int i = 0; i < path.size(); i++) {
        cout << "(" << path[i].first << "," << path[i].second << ")";
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    // Mark path in maze with '*' (except start and end)
    for (int i = 1; i < path.size() - 1; i++) {
        int x = path[i].first;
        int y = path[i].second;
        if (maze[x][y] != 'S' && maze[x][y] != 'E') {
            maze[x][y] = '*';
        }
    }
}

void printMaze() {
    cout << "Maze with path marked:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << maze[i][j];
        }
        cout << '\n';
    }
}

int main() {
    cout << "Enter maze dimensions (n m): ";
    cin >> n >> m;
    
    cout << "Enter maze grid:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> maze[i][j];
            if (maze[i][j] == 'S') start = {i, j};
            if (maze[i][j] == 'E') end_pos = {i, j};
        }
    }
    
    cout << "\nOriginal maze:" << endl;
    printMaze();
    
    int choice;
    cout << "\nChoose algorithm:" << endl;
    cout << "1. BFS" << endl;
    cout << "2. DFS" << endl;
    cout << "Enter choice (1 or 2): ";
    cin >> choice;
    
    // Initialize visited array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
            parent[i][j] = {-1, -1};
        }
    }
    
    if (choice == 1) {
        cout << "\nRunning BFS..." << endl;
        bfs();
        reconstructPath(end_pos);
        printMaze();
    } else if (choice == 2) {
        cout << "\nRunning DFS..." << endl;
        if (dfs(start.first, start.second)) {
            cout << "Path found using DFS!" << endl;
            reconstructPath(end_pos);
            printMaze();
        } else {
            cout << "No path found using DFS!" << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}