#include <iostream>
#include <vector>
#include <random>

class DSU {
private:
	int* m_data;
	int* m_rank;
	int m_size;
public:
	DSU(int size) {
		m_data = new int[size];
		m_rank = new int[size];
		m_size = size;
		for (; size > 0;  size--, make(size));
	}

	int get_data(int x) { return m_data[x]; }

	void make(int x) {
		m_data[x] = x;
		m_rank[x] = 0;
	}

	int find(int x) { return x != m_data[x] ? find(m_data[x]) : x; }

	void unite(int x, int y) {
		int pX = find(x);
		int pY = find(y);
		if (m_rank[x] > m_rank[y]) {
			m_data[pY] = pX;
		}
		else {
			m_data[pX] = pY;
			if (m_rank[x] == m_rank[y]) { m_rank[y]++; }
		}
	}

	void print() {
		for (int i = 0; i < m_size; std::cout << '(' << m_data[i] << ')', i++);
	}

	~DSU() {
		delete[] m_data;
		delete[] m_rank;
	}

};

class Maze {
private:
	DSU m_dsu;
	bool* m_right;
	bool* m_bottom;
public:
	Maze(int size) : m_dsu(size) {
		m_right = new bool[size];
		m_bottom = new bool[size];
	}

	void create() {
		
	}

	bool is_not_in_one_path(int x_wall, int y_wall) { return m_dsu.find(x_wall) != m_dsu.find(y_wall); }
	void continue_path(int x, int y) { m_dsu.unite(x, y); }
	int get_start_position(int x) { return m_dsu.find(x); }

	bool is_right_wall(int x) { return m_right[x]; }
	bool is_bottom_wall(int x) { return m_bottom[x]; }
	void destroy_right_wall(int x) { m_right[x] = false; }
	void destroy_bottom_wall(int x) { m_bottom[x] = false; }

	void print() {

	}

	~Maze() {
		delete[] m_right;
		delete[] m_bottom;
	}
};

int main() {
	srand(time(NULL));

	DSU dsu(7);

	dsu.print();
	std::cout << "Step: create" << std::endl;

	dsu.unite(3, 6);

	dsu.print();
	std::cout << "Step: unite(3, 6)" << std::endl;

	dsu.unite(5, 6);

	dsu.print();
	std::cout << "Step: unite(5, 6)" << std::endl;

	dsu.unite(3, 4);

	dsu.print();
	std::cout << "Step: unite(3, 4)" << std::endl;

	system("pause");

	std::cout << "\nMaze\n";

	int maze_size = 10;

	DSU maze_dsu(maze_size * maze_size);
	Maze maze(maze_size * maze_size);

	std::vector<int> walls;

	for (int i = 0; i <= maze_size * maze_size * 2 - 2; i++) {
		if ((i % (2 * maze_size) == 0) || (i > maze_size * (maze_size - 1) * 2)) continue;
		walls.push_back(i);
	}

	while (walls.size() > 0) {
		int size = walls.size();

		int j = rand() % size;

		int x = (walls[j] - 1) / 2;

		if (walls[j] % 2 == 0) {
			if (maze.is_not_in_one_path(x, x + 1)) {
				maze.continue_path(maze.get_start_position(x), maze.get_start_position(x + 1));
				maze.destroy_right_wall(x);
			}
		}
		else {
			if (maze.is_not_in_one_path(x, x + maze_size)) {
				maze.continue_path(maze.get_start_position(x), maze.get_start_position(x + maze_size));
				maze.destroy_bottom_wall(x);
			}
		}

		walls.erase(walls.begin() + j);
	}

	std::cout << "   ";
	for (int i = 1; i < maze_size; i++) {
		std::cout << "___";
	}
	std::cout << '\n';
	for (int i = 0; i < maze_size; i++) {
		std::cout << "|";
		for (int j = maze_size * i; j < maze_size + maze_size * i; j++) {
			if (j == maze_size * maze_size - 1) {
				std::cout << "  |";
			}
			else if (maze.is_right_wall(j) && maze.is_bottom_wall(j)) {
				std::cout << "__|";
			}
			else if (maze.is_right_wall(j)) {
				std::cout << "  |";
			}
			else if (maze.is_bottom_wall(j)) {
				std::cout << "__ ";
			}
			else {
				std::cout << "   ";
			}
		}
		std::cout << "\n";
	}

 	system("pause");
	return 0;
}