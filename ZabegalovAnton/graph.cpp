#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;


class Vertex {
public:
    int prev_vert = 0;
    int dist_from_start = INT_MAX;
};


class Neighbor {
public:
    int vertex;
    int dist;
    bool operator<(const Neighbor& other) const {
        return dist > other.dist;
    }
};


void deikstra(int start, int end, const vector<vector<int>>& fl_table)
{
    int table_size = fl_table.size();
    vector<Vertex> Verts(table_size);
    vector<int> stack_to_go;
    priority_queue<Neighbor> queue;

    queue.push({ start, 0 });
    Verts[start].dist_from_start = 0;

    while (!queue.empty()) {
        int current_vertex = queue.top().vertex;
        int current_dist = queue.top().dist;
        queue.pop();

        for (int neighbor = 0; neighbor < table_size; ++neighbor) {
            if (fl_table[current_vertex][neighbor] != INT_MAX) { 
                stack_to_go.push_back(neighbor); 
            }
        }

        for (int neighbor : stack_to_go) {
            int new_dist = current_dist + fl_table[current_vertex][neighbor];
            if (new_dist < Verts[neighbor].dist_from_start) {
                Verts[neighbor].dist_from_start = new_dist;
                Verts[neighbor].prev_vert = current_vertex;
                queue.push({ neighbor, new_dist });
            }
        }
        stack_to_go.clear();
    }


    if (Verts[end].dist_from_start == INT_MAX) { cout << "No path found" << endl; }
    else {
        cout << "Shortest path: ";
        vector<int> path;

        for (int idx_vert = end; idx_vert != start; idx_vert = Verts[idx_vert].prev_vert)
            cout << idx_vert << " " << "<-" << " ";
        cout << start << endl;
        cout << "Time: " << Verts[end].dist_from_start << endl;
    }
}


void print_flight_table(const vector<vector<int>>& flight_table)
{
    int table_size = flight_table.size();

    for (int i = 0; i < table_size; ++i) {
        cout << i << "  ";
        for (int j = 0; j < table_size; ++j) {
            if (flight_table[i][j] == INT_MAX) { cout << "INF "; }
            else { cout << flight_table[i][j] << "   "; }
        }
    }
}


void filling_table(vector<vector<int>>& flight_table)
{
    ifstream datafile;
    datafile.open("data_after_parse.txt");

    if (not datafile.is_open()) {
        cout << "Couldn't open datafile\table_size";
        return;
    }

    string txtline;
    while (not datafile.eof()) {
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

        if (flight_table[str][col] > time) { flight_table[str][col] = time; }
    }
}


void init() {
    int table_size = 40 * 1000;
    int start = 33105, end = 30693;
    unsigned int state, run = 1;

    vector<vector<int>> flight_table(table_size, vector<int>(table_size, INT_MAX));

    filling_table(flight_table);

    // while (run) {
    //     cout << "to start press 1: ";
    //     cin >> state;

    //     switch (state) {
    //     case 0:
    //         run = 0;
    //         break;
    //     case 1:
    //         cout << "start: ";   cin >> start;
    //         cout << "end: ";     cin >> end;
    //         deikstra(start, end, flight_table);
    //         break;
    //     }
    // }
     deikstra(start, end, flight_table);
}


int main()
{
    init();
}
