#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<utility>
#include<iomanip>
#include<algorithm>

using namespace std;
void printMaze(const vector<vector<char>> &maze) {
for (const auto &row : maze) {
for (const auto &cell : row) {
cout << cell << ' ';
}
cout << '\n';
}
cout << '\n';
}

void printPathCoordinates(const vector<pair<int, int>> &path) {
cout << "Path coordinates:\n";
for (const auto &[x, y] : path) {
cout << "(" << x << ", " << y << ") ";
}
cout << '\n';
}

bool solveMazeBFS(vector<vector<char>> &maze, pair<int, int> start, pair<int, int> end) {
int rows = maze.size(), cols = maze[0].size();
vector<vector<bool>> visited(rows, vector<bool>(cols, false));
queue<pair<int, int>> q;
vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
q.push(start);
visited[start.first][start.second] = true;

while (!q.empty()) {
auto [x, y] = q.front();
q.pop();

if (make_pair(x, y) == end) {
vector<pair<int, int>> path;
pair<int, int> current = end;

while (current != start) {
path.push_back(current);
maze[current.first][current.second] = '*';
current = parent[current.first][current.second];
}

path.push_back(start);
maze[start.first][start.second] = '*';
reverse(path.begin(), path.end());
printPathCoordinates(path);
return true;
}

for (auto [dx, dy] : directions) {
int nx = x + dx, ny = y + dy;

if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
maze[nx][ny] == '.' && !visited[nx][ny]) {
visited[nx][ny] = true;
parent[nx][ny] = {x, y};
q.push({nx, ny});
}
}
}
return false;
}

bool solveMazeDFS(vector<vector<char>> &maze, pair<int, int> start, pair<int, int> end) {
int rows = maze.size(), cols = maze[0].size();
vector<vector<bool>> visited(rows, vector<bool>(cols, false));
stack<pair<int, int>> st;
vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
st.push(start);
visited[start.first][start.second] = true;
while (!st.empty()) {
auto [x, y] = st.top();
st.pop();
if (make_pair(x, y) == end) {
vector<pair<int, int>> path;
pair<int, int> current = end;
while (current != start) {
path.push_back(current);
maze[current.first][current.second] = '*';
current = parent[current.first][current.second];
}
path.push_back(start);
maze[start.first][start.second] = '*';
reverse(path.begin(), path.end());
printPathCoordinates(path);
return true;
}
for (auto [dx, dy] : directions) {
int nx = x + dx, ny = y + dy;
if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
maze[nx][ny] == '.' && !visited[nx][ny]) {
visited[nx][ny] = true;
parent[nx][ny] = {x, y};
st.push({nx, ny});
}
}
}
return false;
}
int main() {
int rows, cols;
cout << "Enter the number of rows and columns for the maze: ";
cin >> rows >> cols;
vector<vector<char>> maze(rows, vector<char>(cols));
cout << "Enter the maze layout (use '.' for paths, '#' for walls):\n";
for (int i = 0; i < rows; ++i) {
for (int j = 0; j < cols; ++j) {
cin >> maze[i][j];
}
}
int sx, sy, ex, ey;
cout << "Enter the start coordinates (row and column): ";
cin >> sx >> sy;
cout << "Enter the end coordinates (row and column): ";
cin >> ex >> ey;
cout << "\nOriginal Maze:\n";
printMaze(maze);
cout << "\nSolving using BFS...\n";
vector<vector<char>> bfsMaze = maze;
if (solveMazeBFS(bfsMaze, {sx, sy}, {ex, ey})) {
cout << "Path found using BFS:\n";
printMaze(bfsMaze);
} else {
cout << "No path found using BFS.\n";
}
cout << "\nSolving using DFS...\n";
vector<vector<char>> dfsMaze = maze;
if (solveMazeDFS(dfsMaze, {sx, sy}, {ex, ey})) {
cout << "Path found using DFS:\n";
printMaze(dfsMaze);
} else {
cout << "No path found using DFS.\n";
}
return 0;
}