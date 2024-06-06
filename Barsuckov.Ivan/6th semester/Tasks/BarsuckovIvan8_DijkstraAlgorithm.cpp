#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

constexpr int OFFSET = 30000;  // uses to offset vertex indexes
constexpr int INF = INT_MAX;  // infinite distance

class Vertex {
public:
    int previous_vertex = 0;  // the previous vertex in the shortest path
    int distance_from_start = INF;  // the distance from the starting vertex to the current vertex
};

class Neighbour {
public:
    int vertex;
    int distance;
};

class CompareDistance {
public:
    bool operator()(const Neighbour& n1, const Neighbour& n2) {
        return n1.distance > n2.distance;
    }
};

void dijkstra(int start, int end, int** adjacency_matrix, int matrix_size)
{
    vector<Vertex> vertices(matrix_size);
    /* This is to implement a priority queue that stores pairs 
       (vertex, distance from the starting vertex) */
    vector<Neighbour> heap;
    heap.push_back({start, 0});  
    vertices[start].distance_from_start = 0;
    
    push_heap(heap.begin(), heap.end(), CompareDistance());  // ordering the heap

    
    while (!heap.empty()) {
        // The vertex with the smallest distance is extracted from the heap
        int current_vertex = heap.front().vertex;
        int current_distance = heap.front().distance;
        pop_heap(heap.begin(), heap.end(), CompareDistance());
        heap.pop_back();

        /* For each neighbor of the current vertex, it is checked whether 
           there is a smaller path through the current vertex */ 
        for (int Neighbour = 0; Neighbour < matrix_size; ++Neighbour) {
            if (adjacency_matrix[current_vertex][Neighbour] != INF) {
                int new_distance = current_distance + adjacency_matrix[current_vertex][Neighbour];
                if (new_distance < vertices[Neighbour].distance_from_start) {
                    vertices[Neighbour].distance_from_start = new_distance;
                    vertices[Neighbour].previous_vertex = current_vertex;
                    heap.push_back({Neighbour, new_distance});
                    push_heap(heap.begin(), heap.end(), CompareDistance());
                }
            }
        }
    }

    /* If the path is found, it outputs the shortest path and the total time.
       If the path is not found, it outputs "No path found" */
    if (vertices[end].distance_from_start == INF) {
        cout << "No path found" << endl;
    } else {
        cout << "Shortest path: ";
        vector<int> path;
        for (int idx_vertex = end; idx_vertex != start; idx_vertex = vertices[idx_vertex].previous_vertex) {
            cout << OFFSET + idx_vertex << " <- ";
        }
        cout << OFFSET + start << endl;
        cout << "Time: " << vertices[end].distance_from_start << endl;
    }
}

// Reads the "parsed.csv" file and fills the adjacency matrix with edge weights
void fill_adjacency_matrix(int** adjacency_matrix, int matrix_size)
{
    ifstream datafile;
    datafile.open("parsed.csv");

    if (!datafile.is_open()) {
        cout << "Error: Couldn't open parsed file";
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
            adjacency_matrix[source][destination] = min(adjacency_matrix[source][destination], time);
        }
    }
}

// Running Dijkstra's algorithm using the adjacency matrix
void start() {
    int matrix_size = 10000;
    int start = 0, end = 0;
    unsigned int state, run = 1;

    int** adjacency_matrix = new int*[matrix_size];
    for (int i = 0; i < matrix_size; ++i) {
        adjacency_matrix[i] = new int[matrix_size];
        for (int j = 0; j < matrix_size; ++j) {
            adjacency_matrix[i][j] = INF;
        }
    }

    fill_adjacency_matrix(adjacency_matrix, matrix_size);

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
            dijkstra(start, end, adjacency_matrix, matrix_size);
            break;
        }
    }

    for (int i = 0; i < matrix_size; ++i) {
        delete[] adjacency_matrix[i];
    }
    delete[] adjacency_matrix;
}

int main()
{
    start();
    return 0;
}