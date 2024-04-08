#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

struct Vertex {
    int prev_vert = 0;
    int dist_from_start = INT_MAX;
};

struct Neighbor {
    int vertex;
    int dist;
    bool operator<(const Neighbor& other) const {
        return dist > other.dist; // меняем приоритет кучи
    }
};

void Dijkstra(int start, int end, const vector<vector<int>>& fl_table) 
{
    int table_size = fl_table.size(); // таблица смежности
    vector<Vertex> Verts(table_size); // глобальный контроллер дистанции
    vector<int> stack_to_go; // стек рассматриваемых соседей
    priority_queue<Neighbor> queue; // куча с обратным приоритетом

    queue.push({ start, 0 }); 
    Verts[start].dist_from_start = 0;

    while (!queue.empty()) {
        int current_vertex = queue.top().vertex;
        int current_dist = queue.top().dist;
        queue.pop();

        for (int neighbor = 0; neighbor < table_size; ++neighbor) 
            if (fl_table[current_vertex][neighbor] != INT_MAX) 
                stack_to_go.push_back(neighbor);

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


    if (Verts[end].dist_from_start == INT_MAX)
        cout << "No path found" << endl;
    else {
        cout << "Shortest path: ";
        vector<int> path;
        for (int idx_vert = end; idx_vert != start; idx_vert = Verts[idx_vert].prev_vert)
            cout << idx_vert << " " << "<-" << " ";
        cout << start << endl;
        cout << "Time: " << Verts[end].dist_from_start << endl;
    }
}


void print_flight_table(const std::vector<std::vector<int>>& flight_table) 
{
    int table_size = flight_table.size();
    for (int i = 0; i < table_size; ++i) {
        std::cout << i << "  ";
        for (int j = 0; j < table_size; ++j) {
            if (flight_table[i][j] == INT_MAX) std::cout << "INF ";
            else std::cout << flight_table[i][j] << "   ";
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

    std::string txtline;
    while (not datafile.eof()) {
        std::getline(datafile, txtline);
        stringstream inputString(txtline);

        int str, col, time;
        string tempString;

        getline(inputString, tempString, '\t');
        str = atoi(tempString.c_str());
        
        getline(inputString, tempString, '\t');
        col = atoi(tempString.c_str());

        getline(inputString, tempString, '\t');
        time = atoi(tempString.c_str());

        //cout << str << "\t" << col << "\t" << time << endl;

        if (flight_table[str][col] > time)
            flight_table[str][col] = time;
    }
    //print_flight_table(flight_table);
}


int main() 
{
    int table_size = 40 * 1000;
    int start, end;
    unsigned int choise, run = 1;

    vector<vector<int>> flight_table(table_size, vector<int>(table_size, INT_MAX));

    filling_table(flight_table);
    
    while (run)
    {
        std::cout << "choise: ";
        std::cin >> choise;

        switch (choise)
        {
        case 0:
            run = 0;
            break;
        case 1:
            cout << "start: ";
            cin >> start;
            cout << "end: ";
            cin >> end;
            Dijkstra(start, end, flight_table);
            break;
        }
    }
    return 0;
}
