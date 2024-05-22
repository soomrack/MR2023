#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

constexpr int OFFSET = 30000;
constexpr int INF = INT_MAX;

class Vertex {
public:
    int previous_vertex = -1;
    int distance_from_start = INF;
};

class Neighbor {
public:
    int vertex;
    int distance;
};

class CompareDistance {
public:
    bool operator()(const Neighbor& n1, const Neighbor& n2) {
        return n1.distance > n2.distance;
    }
};

void dijkstra(int start, int end, const vector<vector<Neighbor>>& adjacency_list) {
    int n = adjacency_list.size();
    vector<Vertex> vertices(n);
    vector<Neighbor> heap;
    heap.push_back({start, 0});
    vertices[start].distance_from_start = 0;
    push_heap(heap.begin(), heap.end(), CompareDistance());

    while (!heap.empty()) {
        int current_vertex = heap.front().vertex;
        int current_distance = heap.front().distance;
        pop_heap(heap.begin(), heap.end(), CompareDistance());
        heap.pop_back();

        if (current_distance > vertices[current_vertex].distance_from_start) {
            continue;
        }

        for (const Neighbor& neighbor : adjacency_list[current_vertex]) {
            int new_distance = current_distance + neighbor.distance;
            if (new_distance < vertices[neighbor.vertex].distance_from_start) {
                vertices[neighbor.vertex].distance_from_start = new_distance;
                vertices[neighbor.vertex].previous_vertex = current_vertex;
                heap.push_back({neighbor.vertex, new_distance});
                push_heap(heap.begin(), heap.end(), CompareDistance());
            }
        }
    }

    if (vertices[end].distance_from_start == INF) {
        cout << "No path found" << endl;
    } else {
        cout << "Shortest path: ";
        vector<int> path;
        for (int idx_vertex = end; idx_vertex != start; idx_vertex = vertices[idx_vertex].previous_vertex) {
            path.push_back(OFFSET + idx_vertex);
        }
        path.push_back(OFFSET + start);
        reverse(path.begin(), path.end());
        for (int vertex : path) {
            cout << vertex << " ";
        }
        cout << endl;
        cout << "Time: " << vertices[end].distance_from_start << endl;
    }
}

void fill_adjacency_list(vector<vector<Neighbor>>& adjacency_list, int matrix_size) {
    ifstream datafile("parsed.csv");

    if (!datafile.is_open()) {
        cout << "Error: Couldn't open parsed file" << endl;
        return;
    }

    string line;
    while (getline(datafile, line)) {
        stringstream inputStream(line);
        int source, destination, time;
        char comma;

        inputStream >> source >> comma >> destination >> comma >> time;

        source -= OFFSET;
        destination -= OFFSET;

        if (source < matrix_size && destination < matrix_size) {
            adjacency_list[source].push_back({destination, time});
        }
    }
}

void start() {
    int matrix_size = 10000;
    int start = 0, end = 0;
    unsigned int state, run = 1;

    vector<vector<Neighbor>> adjacency_list(matrix_size);

    fill_adjacency_list(adjacency_list, matrix_size);

    while (run) {
        cout << "Press 1 to continue, 0 to exit: ";
        cin >> state;

        switch (state) {
        case 0:
            run = 0;
            break;
        case 1:
            cout << "start: ";   cin >> start;
            cout << "end: ";     cin >> end;
            start -= OFFSET;
            end -= OFFSET;
            dijkstra(start, end, adjacency_list);
            break;
        }
    }
}

int main() {
    start();
    return 0;
}
