#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;

constexpr int OFFSET = 30000;
constexpr int INF = numeric_limits<int>::max();

class Vertex {
public:
    int previous_vertex = 0;
    int distance_from_start = INF;
};

class Edge {
public:
    int destination;
    int weight;
};

void dijkstra(int start, int end, const vector<vector<Edge>>& graph)
{
    int num_vertices = graph.size();
    vector<Vertex> vertices(num_vertices);
    vertices[start].distance_from_start = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        if (current_distance > vertices[current_vertex].distance_from_start)
            continue;

        for (const Edge& edge : graph[current_vertex]) {
            int new_distance = current_distance + edge.weight;
            if (new_distance < vertices[edge.destination].distance_from_start) {
                vertices[edge.destination].distance_from_start = new_distance;
                vertices[edge.destination].previous_vertex = current_vertex;
                pq.push({new_distance, edge.destination});
            }
        }
    }

    if (vertices[end].distance_from_start == INF) {
        cout << "No path found" << endl;
    } else {
        cout << "Shortest path: ";
        vector<int> path;
        for (int idx_vertex = end; idx_vertex != start; idx_vertex = vertices[idx_vertex].previous_vertex) {
            path.push_back(idx_vertex + OFFSET);
        }
        path.push_back(start + OFFSET);
        reverse(path.begin(), path.end());
        for (int vertex : path) {
            cout << vertex << " <- ";
        }
        cout << endl;
        cout << "Time: " << vertices[end].distance_from_start << endl;
    }
}

vector<vector<Edge>> parse_graph(const string& filename, int matrix_size)
{
    vector<vector<Edge>> graph(matrix_size);

    ifstream datafile(filename);
    if (!datafile.is_open()) {
        cerr << "Error: Couldn't open parsed file" << endl;
        return graph;
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
            graph[source].push_back({destination, time});
        }
    }

    return graph;
}

int main()
{
    const string filename = "parsed.csv";
    const int matrix_size = 10000;
    vector<vector<Edge>> graph = parse_graph(filename, matrix_size);

    int start, end;
    char state;
    do {
        cout << "Press 'c' to continue, 'q' to exit: ";
        cin >> state;
        switch (state) {
            case 'c':
                cout << "start: ";   cin >> start;
                cout << "end: ";     cin >> end;
                start -= OFFSET;
                end -= OFFSET;
                dijkstra(start, end, graph);
                break;
            case 'q':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option" << endl;
        }
    } while (state != 'q');

    return 0;
}
