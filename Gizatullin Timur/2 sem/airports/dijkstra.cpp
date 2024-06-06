#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <queue>
#include <functional>

using namespace std;

constexpr int OFFSET = 30000;
constexpr int INF = numeric_limits<int>::max();

class Vertex {
public:
    int previous_vertex = 0;
    int distance_from_start = INF;
};

class Neighbor {
public:
    int vertex;
    int distance;
};

class CompareDistance {
public:
    bool operator()(const Neighbor& n1, const Neighbor& n2) const {
        return n1.distance > n2.distance;
    }
};

void dijkstra(int start, int end, const vector<vector<int>>& adjacency_matrix) {
    int matrix_size = adjacency_matrix.size();
    vector<Vertex> vertices(matrix_size);
    priority_queue<Neighbor, vector<Neighbor>, CompareDistance> min_queue;

    vertices[start].distance_from_start = 0;
    min_queue.push({start, 0});

    while (!min_queue.empty())
    {
        Neighbor top = min_queue.top();
        int current_vertex = top.vertex;
        int current_distance = top.distance;

        min_queue.pop();

        if (current_distance > vertices[current_vertex].distance_from_start) {
            continue;
        }

        for (int neighbor = 0; neighbor < matrix_size; ++neighbor)
        {
            int edge_distance = adjacency_matrix[current_vertex][neighbor];
            if (edge_distance != INF) {
                int new_distance = current_distance + edge_distance;
                if (new_distance < vertices[neighbor].distance_from_start)
                {
                    vertices[neighbor].distance_from_start = new_distance;
                    vertices[neighbor].previous_vertex = current_vertex;
                    min_queue.push({neighbor, new_distance});
                }
            }
        }
    }

    if (vertices[end].distance_from_start == INF) {
        cout << "No path found" << endl;
    } 
    else
    {
        cout << "Shortest path: ";
        for (int v = end; v != -1; v = vertices[v].previous_vertex) {
            cout << v + OFFSET << " <- ";
        }
        cout << "\nTime: " << vertices[end].distance_from_start << endl;
    }
}

void fill_adjacency_matrix(vector<vector<int>>& adjacency_matrix, const string& filename) {
    ifstream datafile(filename);

    if (!datafile.is_open())
    {
        cerr << "Error: Couldn't open parsed file" << endl;
        return;
    }

    string line;
    while (getline(datafile, line))
    {
        stringstream inputStream(line);
        int source, destination, time;
        char comma;

        if (inputStream >> source >> comma >> destination >> comma >> time)
        {
            source -= OFFSET;
            destination -= OFFSET;
            if (source >= 0 && source < adjacency_matrix.size() && destination >= 0 && destination < adjacency_matrix.size()) {
                adjacency_matrix[source][destination] = min(adjacency_matrix[source][destination], time);
            }
        }
    }
}

void run() {
    const int matrix_size = 10000;
    vector<vector<int>> adjacency_matrix(matrix_size, vector<int>(matrix_size, INF));

    fill_adjacency_matrix(adjacency_matrix, "parsed.csv");

    while (true) {
        int start_id, end_id;
        cout << "start:";
        cin >> start_id;
        cout << "end:";
        cin >> end_id;

        start_id -= OFFSET;
        end_id -= OFFSET;

        if (start_id >= 0 && start_id < matrix_size && end_id >= 0 && end_id < matrix_size) {
            dijkstra(start_id, end_id, adjacency_matrix);} 
        else{
            cout << "Invalid vertices" << endl;}
    }
}

int main() {
    run();
    return 0;
}
