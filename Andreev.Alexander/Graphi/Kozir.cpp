#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

class Vertex {
public:
    int prev_vert = 0;
    int dist_from_start = numeric_limits<int>::max();
};

class Neighbor {
public:
    int vertex;
    int dist;
};

class MinHeap {
private:
    vector<Neighbor> heap;

    void heapify_up(int idx) {
        int parent = (idx - 1) / 2;
        while (idx > 0 && heap[idx].dist < heap[parent].dist) {
            swap(heap[idx], heap[parent]);
            idx = parent;
            parent = (idx - 1) / 2;
        }
    }

    void heapify_down(int idx) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < heap.size() && heap[left].dist < heap[smallest].dist) {
            smallest = left;
        }
        if (right < heap.size() && heap[right].dist < heap[smallest].dist) {
            smallest = right;
        }

        if (smallest != idx) {
            swap(heap[idx], heap[smallest]);
            heapify_down(smallest);
        }
    }

public:
    bool empty() const {
        return heap.empty();
    }

    void push(const Neighbor& neighbor) {
        heap.push_back(neighbor);
        heapify_up(heap.size() - 1);
    }

    Neighbor pop() {
        if (heap.empty()) {
            throw out_of_range("Heap is empty");
        }

        Neighbor min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);

        return min;
    }
};

void dijkstra(int start, int end, const vector<vector<int>>& fl_table) {
    int table_size = fl_table.size();
    vector<Vertex> Verts(table_size);
    vector<int> stack_to_go;
    MinHeap heap;

    heap.push({ start, 0 });
    Verts[start].dist_from_start = 0;

    while (!heap.empty()) {
        int current_vertex = heap.pop().vertex;

        for (int neighbor = 0; neighbor < table_size; ++neighbor) {
            if (fl_table[current_vertex][neighbor] != numeric_limits<int>::max()) {
                stack_to_go.push_back(neighbor);
            }
        }

        for (int neighbor : stack_to_go) {
            int new_dist = Verts[current_vertex].dist_from_start + fl_table[current_vertex][neighbor];
            if (new_dist < Verts[neighbor].dist_from_start) {
                Verts[neighbor].dist_from_start = new_dist;
                Verts[neighbor].prev_vert = current_vertex;
                heap.push({ neighbor, new_dist });
            }
        }
        stack_to_go.clear();
    }

    if (Verts[end].dist_from_start == numeric_limits<int>::max()) {
        cout << "No path found" << endl;
    }
    else {
        cout << "Shortest path: ";
        vector<int> path;

        for (int idx_vert = end; idx_vert != start; idx_vert = Verts[idx_vert].prev_vert)
            cout << idx_vert << " <- ";
        cout << start << endl;
        cout << "Time: " << Verts[end].dist_from_start << endl;
    }
}

void print_flight_table(const vector<vector<int>>& flight_table) {
    int table_size = flight_table.size();

    for (int i = 0; i < table_size; ++i) {
        cout << i << "  ";
        for (int j = 0; j < table_size; ++j) {
            if (flight_table[i][j] == numeric_limits<int>::max()) {
                cout << "INF ";
            }
            else {
                cout << flight_table[i][j] << "   ";
            }
        }
        cout << endl;
    }
}

void filling_table(vector<vector<int>>& flight_table) {
    ifstream datafile;
    datafile.open("data_after_parse.txt");

    if (!datafile.is_open()) {
        cout << "Couldn't open datafile" << endl;
        return;
    }

    string txtline;
    while (!datafile.eof()) {
        getline(datafile, txtline);
        stringstream inputString(txtline);

        int str, col, time;
        string tempString;

        getline(inputString, tempString, '\t');
        str = atoi(tempString.c_str());

        getline(inputString, tempString, '\t');
        col = atoi(tempString.c_str());

        getline(inputString, tempString, '\t');
        time = atoi(tempString.c_str());

        if (flight_table[str][col] > time) {
            flight_table[str][col] = time;
        }
    }
}

void init() {
    int table_size = 40 * 1000;
    int start, end;
    unsigned int state, run = 1;

    vector<vector<int>> flight_table(table_size, vector<int>(table_size, numeric_limits<int>::max()));

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
