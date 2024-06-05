#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

class Vertex {
public:
	int prev_vertex = -1;
	int dist_from_start = INT_MAX;
};

class Neighbor {
public:
	int vertex_index;
	int distance;
	bool operator < (const Neighbor& other) const {
		return distance > other.distance;
	}

	Neighbor(int v, int d) : vertex_index(v), distance(d) {}
};

void dijkstra(int start, int end, const vector<vector<int>>& fl_table) {
	int table_size = fl_table.size();
	vector<Vertex> vertices(table_size);
	vector<int> stack_to_go;
	vector<bool> in_queue(table_size, false);
	priority_queue<Neighbor> queue;

	queue.push({ start, 0 });
	vertices[start].dist_from_start = 0;

	while (!queue.empty()) {
		int current_vertex = queue.top().vertex_index;
		int current_distance = queue.top().distance;
		queue.pop();

		for (int neighbor = 0; neighbor < table_size; ++neighbor) {
			if (fl_table[current_vertex][neighbor] != INT_MAX) {
				stack_to_go.push_back(neighbor);
			}
		}

		for (int neighbor : stack_to_go) {
			int new_dist = current_distance + fl_table[current_vertex][neighbor];
			if (new_dist < vertices[neighbor].dist_from_start) {
				vertices[neighbor].dist_from_start = new_dist;
				vertices[neighbor].prev_vertex = current_vertex;
				queue.push({ neighbor, new_dist });
			}
		}

		stack_to_go.clear();
	}

	if (vertices[end].dist_from_start == INT_MAX) {
		cout << "No path found" << endl;
	}
	else {
		cout << "Shortest path: ";
		vector<int> path;

		for (int idx_vertices = end; idx_vertices != start; idx_vertices = vertices[idx_vertices].prev_vertex)
			cout << idx_vertices << " " << "<-" << " ";
		cout << start << endl;
		cout << "Time: " << vertices[end].dist_from_start << endl;
	}
}

void print_fl_table(const vector<vector<int>>& flight_table) {
	int table_size = flight_table.size();

	for (int i = 0; i < table_size; ++i) {
		cout << i << " ";
		for (int j = 0; j < table_size; ++j) {
			if (flight_table[i][j] == INT_MAX) {
				cout << "INF ";
			}
			else {
				cout << flight_table[i][j] << "   ";
			}
		}
	}
}

void filling_table(vector<vector<int>>& flight_table) {
	ifstream DATAFILE;
	DATAFILE.open("new_data.txt");

	if (not DATAFILE.is_open()) {
		cout << "Couldn't open datafile\n";
		return;
	}

	string txtline;
	while (not DATAFILE.eof()) {
		getline(DATAFILE, txtline);
		stringstream inputString(txtline);

		int str, col, time;
		string tempString;

		getline(inputString, tempString, '\t');
		str = stoi(tempString);

		getline(inputString, tempString, '\t');
		col = stoi(tempString);

		getline(inputString, tempString, '\t');
		time = stoi(tempString);

		if (flight_table[str][col] > time) {
			flight_table[str][col] = time;
		}
	}
}

void init() {
	int table_size = 40 * 1000;
	int start, end;
	unsigned int state, run = 1;

	vector<vector<int>> flight_table(table_size, vector<int>(table_size, INT_MAX));

	filling_table(flight_table);

	while (run) {
		cout << "To start press 1: ";
		cin >> state;

		switch (state) {
		case 0:
			run = 0;
			break;
		case 1:
			cout << "Start: ";
			cin >> start;
			cout << "End: ";
			cin >> end;
			dijkstra(start, end, flight_table);
			break;
		}
	}
}

int main() {
	init();
	return 0;
}
