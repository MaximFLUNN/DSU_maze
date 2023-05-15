//#include <iostream>
//#include <vector>
//#include <random>
//
//class DSU {
//private:
//	int* m_data;
//	int* m_rank;
//	int m_size;
//public:
//	DSU(int size) {
//		m_data = new int[size];
//		m_rank = new int[size];
//		m_size = size;
//		for (; size > 0;  size--, make(size));
//	}
//
//	int get_data(int x) { return m_data[x]; }
//
//	void make(int x) {
//		m_data[x] = x;
//		m_rank[x] = 0;
//	}
//
//	int find(int x) { return x != m_data[x] ? find(m_data[x]) : x; }
//
//	void unite(int x, int y) {
//		int pX = find(x);
//		int pY = find(y);
//		if (m_rank[x] > m_rank[y]) {
//			m_data[pY] = pX;
//		}
//		else {
//			m_data[pX] = pY;
//			if (m_rank[x] == m_rank[y]) { m_rank[y]++; }
//		}
//	}
//
//	void print() {
//		for (int i = 0; i < m_size; std::cout << '(' << m_data[i] << ')', i++);
//	}
//
//	~DSU() {}
//
//};
//
//class Maze {
//private:
//	bool* m_right;
//	bool* m_bottom;
//public:
//	Maze(int size) {
//		m_right = new bool[size];
//		m_bottom = new bool[size];
//	}
//
//	bool get_right_wall(int x) { return m_right[x]; }
//	bool get_bottom_wall(int x) { return m_bottom[x]; }
//	void set_right_wall(int x, bool value) { m_right[x] = value; }
//	void set_bottom_wall(int x, bool value) { m_bottom[x] = value; }
//
//	~Maze() {}
//};
//
//int main() {
//	srand(time(NULL));
//
//	DSU dsu(7);
//
//	dsu.print();
//	std::cout << "Step: create" << std::endl;
//
//	dsu.unite(3, 6);
//
//	dsu.print();
//	std::cout << "Step: unite(3, 6)" << std::endl;
//
//	dsu.unite(5, 6);
//
//	dsu.print();
//	std::cout << "Step: unite(5, 6)" << std::endl;
//
//	dsu.unite(3, 4);
//
//	dsu.print();
//	std::cout << "Step: unite(3, 4)" << std::endl;
//
//	system("pause");
//
//	std::cout << "\nMaze\n";
//
//	int maze_size = 5;
//
//	DSU maze_dsu(maze_size * maze_size);
//	Maze maze(maze_size * maze_size);
//
//	std::vector<int> walls;
//
//	for (int i = 0; i <= maze_size * maze_size * 2 - 2; i++) {
//		if ((i % (2 * maze_size) == 0) || (i > maze_size * (maze_size - 1) * 2)) continue;
//		walls.push_back(i);
//	}
//
//	while (walls.size() > 0) {
//		int size = walls.size();
//
//		int j = rand() % size;
//
//		int x = (walls[j] - 1) / 2;
//		if (walls[j] % 2 == 0) {
//			if (maze_dsu.find(x) != maze_dsu.find(x + 1)) {
//				maze_dsu.unite(maze_dsu.find(x), maze_dsu.find(x + 1));
//				maze.set_right_wall(x, false);
//			}
//		}
//		else {
//			if (maze_dsu.find(x) != maze_dsu.find(x + maze_size)) {
//				maze_dsu.unite(maze_dsu.find(x), maze_dsu.find(x + maze_size));
//				maze.set_bottom_wall(x, false);
//			}
//		}
//
//		walls.erase(walls.begin() + j);
//	}
//
//	std::cout << "   ";
//	for (int i = 1; i < maze_size; i++) {
//		std::cout << "___";
//	}
//	std::cout << '\n';
//	for (int i = 0; i < maze_size; i++) {
//		std::cout << "|";
//		for (int j = maze_size * i; j < maze_size + maze_size * i; j++) {
//			if (j == maze_size * maze_size - 1) {
//				std::cout << "  |";
//			}
//			else if (maze.get_right_wall(j) && maze.get_bottom_wall(j)) {
//				std::cout << "__|";
//			}
//			else if (maze.get_right_wall(j)) {
//				std::cout << "  |";
//			}
//			else if (maze.get_bottom_wall(j)) {
//				std::cout << "__ ";
//			}
//			else {
//				std::cout << "   ";
//			}
//		}
//		std::cout << "\n";
//	}
//
// 	system("pause");
//	return 0;
//}
//////////////////// v2
//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//const int MAXN = 100;
//
//struct Edge {
//    int x, y;
//    char dir;
//    int w;
//};
//
//int n, m;
//vector<Edge> edges;
//int set[MAXN][MAXN];
//
//bool cmp(Edge a, Edge b) {
//    return a.w < b.w;
//}
//
//int find_set(int x, int y) {
//    if (set[x][y] == x*m + y) return x*m + y;
//    return set[x][y] = find_set(set[x][y] / m, set[x][y] % m);
//}
//
//void union_sets(int x1, int y1, int x2, int y2) {
//    int s1 = find_set(x1, y1);
//    int s2 = find_set(x2, y2);
//    if (s1 != s2) set[s1 / m][s1 % m] = s2;
//}
//
//void gen_maze() {
//    // initialize sets
//    for (int i = 0; i < n*m; i++) set[i / m][i % m] = i;
//
//    // generate edges
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            if (i < n-1) edges.push_back({i, j, 'd', rand()});
//            if (j < m-1) edges.push_back({i, j, 'r', rand()});
//        }
//    }
//
//    // sort edges by weight
//    sort(edges.begin(), edges.end(), cmp);
//
//    // generate maze
//    for (int i = 0; i < edges.size(); i++) {
//        int x1 = edges[i].x;
//        int y1 = edges[i].y;
//        int x2 = x1 + (edges[i].dir == 'd');
//        int y2 = y1 + (edges[i].dir == 'r');
//
//        if (i % n == 0)  cout << endl;
//        if (find_set(x1, y1) != find_set(x2, y2)) {
//            union_sets(x1, y1, x2, y2);
//            if (edges[i].dir == 'd') {
//                // remove bottom wall
//                cout << "__ ";
//            } else {
//                // remove right wall
//                cout << "  |";
//            }
//        } else {
//            if (edges[i].dir == 'd') {
//                // keep bottom wall
//                cout << "__|";
//            } else {
//                // keep right wall
//                cout << "  |";
//            }
//        }
//        //if (y1 == m-1) cout << endl;
//    }
//}
//
//int main() {
//    cin >> n >> m;
//    gen_maze();
//    return 0;
//} 
//////////////////// v3
//#include <iostream>
//#include <vector>
////#include <cstdlib>
//#include <ctime>
//
//using namespace std;
//
//const int WALL_BOTTOM = 1;
//const int WALL_RIGHT = 2;
//const int WALL_TOP = 3;
//const int WALL_LEFT = 4;
//
//struct Cell {
//    int set;
//    int walls;
//};
//
//int findSet(vector<int>& sets, int x) {
//    if (sets[x] != x) {
//        sets[x] = findSet(sets, sets[x]);
//    }
//    return sets[x];
//}
//
//void unionSets(vector<int>& sets, int x, int y) {
//    int px = findSet(sets, x);
//    int py = findSet(sets, y);
//    if (px != py) {
//        sets[py] = px;
//    }
//}
//
//int main() {
//    int rows = 10, cols = 10;
//    vector<vector<Cell> > grid(rows, vector<Cell>(cols));
//    vector<int> sets(rows * cols);
//    for (int i = 0; i < rows * cols; i++) {
//        sets[i] = i;
//    }
//    srand(time(NULL));
//    int numSets = rows * cols;
//    while (numSets != 2) {
//        // choose a random wall to remove
//        int i = rand() % (rows - 1);
//        int j = rand() % (cols - 1);
//        int dir = rand() % 2;
//        grid[i][j].walls = rand() % 2 ? WALL_BOTTOM : WALL_RIGHT;
//        if (dir == 0) {
//            // horizontal wall
//            if (findSet(sets, i * cols + j) != findSet(sets, (i + 1) * cols + j)) {
//                grid[i][j].walls &= ~WALL_BOTTOM;
//                grid[i + 1][j].walls &= ~WALL_TOP;
//                unionSets(sets, i * cols + j, (i + 1) * cols + j);
//                numSets--;
//            }
//        }
//        else {
//            // vertical wall
//            if (findSet(sets, i * cols + j) != findSet(sets, i * cols + j + 1)) {
//                grid[i][j].walls &= ~WALL_RIGHT;
//                grid[i][j + 1].walls &= ~WALL_LEFT;
//                unionSets(sets, i * cols + j, i * cols + j + 1);
//                numSets--;
//            }
//        }
//    }
//    // set entrance and exit
//    grid[0][0].walls &= ~WALL_LEFT;
//    grid[rows - 1][cols - 1].walls &= ~WALL_BOTTOM;
//    // print grid
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            cout << "+";
//            if (grid[i][j].walls & WALL_BOTTOM) {
//                cout << "---";
//            }
//            else {
//                cout << "   ";
//            }
//        }
//        cout << "+" << endl;
//        for (int j = 0; j < cols; j++) {
//            if (grid[i][j].walls & WALL_RIGHT) {
//                cout << "|";
//            }
//            else {
//                cout << " ";
//            }
//            cout << "   ";
//        }
//        cout << "|" << endl;
//    }
//    for (int j = 0; j < cols; j++) {
//        cout << "+---";
//    }
//    cout << "+" << endl;
//
//    return 0;
//}
///////////// v4
//#include <iostream>
//#include <vector>
////#include <cstdlib>
//#include <ctime>
//using namespace std;
//class Set {
//public:
//    int parent;
//    int rank;
//    Set(int parent) {
//        this->parent = parent;
//        rank = 0;
//    }
//};
//
//int findRoot(vector<Set>& sets, int v) {
//    if (v != sets[v].parent) {
//        sets[v].parent = findRoot(sets, sets[v].parent);
//    }
//    return sets[v].parent;
//} 
//
//void unionSets(vector<Set>& sets, int a, int b) {
//    int root1 = findRoot(sets, a);
//    int root2 = findRoot(sets, b);
//    if (root1 == root2) {
//        return;
//    }
//    if (sets[root1].rank > sets[root2].rank) {
//        sets[root2].parent = root1;
//    }
//    else {
//        sets[root1].parent = root2;
//        if (sets[root1].rank == sets[root2].rank) {
//            sets[root2].rank++;
//        }
//    }
//}
//
//class Maze {
//public:
//    int width;
//    int height;
//    vector<vector<bool>> verticalWalls;
//    vector<vector<bool>> horizontalWalls;
//    Maze(int width, int height) {
//        this->width = width;
//        this->height = height;
//        verticalWalls.resize(width - 1, vector<bool>(height, false));
//        horizontalWalls.resize(width, vector<bool>(height - 1, false));
//    }
//};
//
//void generateMazeEller(Maze& maze) {
//    vector<Set> sets(maze.width, Set(0));
//    for (int i = 0; i < maze.width; i++) {
//        sets[i] = Set(i);
//    }
//    for (int y = 0; y < maze.height; y++) {
//        // Создание вертикальных стен между множествами
//        if (y != 0) {
//            for (int x = 0; x < maze.width - 1; x++) {
//                if (findRoot(sets, x) == findRoot(sets, x + 1)) {
//                    continue;
//                }
//                if (rand() % 2 == 0 || findRoot(sets, x) != x) {
//                    maze.verticalWalls[x][y - 1] = true;
//                }
//                else {
//                    unionSets(sets, x, x + 1);
//                }
//            }
//        }
//        // Создание горизонтальных стен и объединение множеств
//        vector<int> setIds(maze.width, -1);
//        for (int x = 0; x < maze.width; x++) {
//            int setId = findRoot(sets, x);
//            setIds[x] = setId;
//            if (y == 0 || setId != setIds[x]) {//setIds[x - 1]) {
//                int count = 1;
//                int j = x + 1;
//                while (j < maze.width && findRoot(sets, j) == setId) {
//                    count++;
//                    j++;
//                }
//                if (count > 1 && (y == maze.height - 1 || rand() % 2 == 0)) {
//                    int hole = rand() % count;
//                    for (int k = 0; k < count; k++) {
//                        if (k != hole) {
//                            maze.horizontalWalls[x + k][y] = true;
//                            unionSets(sets, x + k, x + k + 1); // объединение множеств
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
//
//int main() {
//    int size = 15;
//    Maze maze(size, size);
//    generateMazeEller(maze);
//    for (int i = 0; i < size - 1; i++) {
//        //std::cout << "|";
//        for (int j = 0; j < size - 1; j++) {
//            if (maze.horizontalWalls[i][j] && maze.verticalWalls[i][j]) {
//                std::cout << "__|";
//            }
//            else if (maze.horizontalWalls[i][j]) {
//                std::cout << "__ ";
//            }
//            else if (maze.verticalWalls[i][j]) {
//                std::cout << "  |";
//            }
//            else {
//                std::cout << "   ";
//            }
//        }
//        std::cout << "\n";
//    }
//    return 0;
//}
//////////////// v5
#include <iostream>
#include <vector>
#include <string>

int main() {
    const int ROWS = 10;
    const int COLS = 10;
    const int TOP_WALL = 1;
    const int RIGHT_WALL = 2;
    const int BOTTOM_WALL = 4;
    const int LEFT_WALL = 8;

    int maze[ROWS][COLS];

    // Инициализация клеток лабиринта
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze[i][j] = TOP_WALL | RIGHT_WALL | BOTTOM_WALL | LEFT_WALL;
        }
    }

    const int SETS = ROWS * COLS;

    int sets[SETS];
    for (int i = 0; i < SETS; i++) {
        sets[i] = i;
    }

    srand(time(nullptr));

    // Удаление стен между клетками в одном ряду
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 1; j++) {
            if (sets[i * COLS + j] != sets[i * COLS + j + 1]) {
                if (i == ROWS - 1) {
                    maze[i][j] &= ~RIGHT_WALL;
                }
                else if (rand() % 2 == 0) {
                    maze[i][j] &= ~RIGHT_WALL;
                    int old_set = sets[i * COLS + j + 1];
                    int new_set = sets[i * COLS + j];
                    for (int k = 0; k < SETS; k++) {
                        if (sets[k] == old_set) {
                            sets[k] = new_set;
                        }
                    }
                }
            }
        }
    }

    // Удаление стен между клетками в разных рядах
    for (int i = 0; i < ROWS - 1; i++) {
        int current_set = sets[i * COLS];
        int next_set = sets[(i + 1) * COLS];
        int set_count = 0;
        int set_positions[COLS];
        for (int j = 0; j < COLS; j++) {
            if (sets[i * COLS + j] == current_set) {
                set_positions[set_count++] = j;
            }
        }
        if (set_count > 1) {
            int random_index = rand() % set_count;
            int random_position = set_positions[random_index];
            maze[i][random_position] &= ~BOTTOM_WALL;
            int old_set = sets[(i + 1) * COLS + random_position];
            int new_set = sets[i * COLS + random_position];
            for (int k = 0; k < SETS; k++) {
                if (sets[k] == old_set) {
                    sets[k] = new_set;
                }
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        //std::cout << "|";
        for (int j = 0; j < 10; j++) {
            std::cout << '[' << maze[i][j] << ']';
            /*if (maze[i][j] && maze[i][j]) {
                std::cout << "__|";
            }
            else if (maze.horizontalWalls[i][j]) {
                std::cout << "__ ";
            }
            else if (maze.verticalWalls[i][j]) {
                std::cout << "  |";
            }
            else {
                std::cout << "   ";
            }*/
        }
        std::cout << "\n";
    }
    return 0;
}