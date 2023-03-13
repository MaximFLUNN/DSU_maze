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

	~DSU() {}

};

class Maze {
private:
	bool* m_right;
	bool* m_bottom;
public:
	Maze(int size) {
		m_right = new bool[size];
		m_bottom = new bool[size];
	}

	bool get_right_wall(int x) { return m_right[x]; }
	bool get_bottom_wall(int x) { return m_bottom[x]; }
	void set_right_wall(int x, bool value) { m_right[x] = value; }
	void set_bottom_wall(int x, bool value) { m_bottom[x] = value; }

	~Maze() {}
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

	int maze_size = 5;

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
			if (maze_dsu.find(x) != maze_dsu.find(x + 1)) {
				maze_dsu.unite(maze_dsu.find(x), maze_dsu.find(x + 1));
				maze.set_right_wall(x, false);
			}
		}
		else {
			if (maze_dsu.find(x) != maze_dsu.find(x + maze_size)) {
				maze_dsu.unite(maze_dsu.find(x), maze_dsu.find(x + maze_size));
				maze.set_bottom_wall(x, false);
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
			else if (maze.get_right_wall(j) && maze.get_bottom_wall(j)) {
				std::cout << "__|";
			}
			else if (maze.get_right_wall(j)) {
				std::cout << "  |";
			}
			else if (maze.get_bottom_wall(j)) {
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