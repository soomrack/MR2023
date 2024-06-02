#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

class Flight
{
public:
    Flight(double FLIGHT_TIME, double AIRLINE_ID, string AIRLINE_NAME, double ORIGIN_AIRPORT_CODE,
        string ORIGIN_CITY, double DEST_AIRPORT_CODE, string DEST_CITY);

    void print();

    double time;
    double airline_id;
    string airline_name;
    double city_from_id;
    string city_from;
    double city_to_id;
    string city_to;
};


Flight::Flight(double FLIGHT_TIME, double AIRLINE_ID, string AIRLINE_NAME, double ORIGIN_AIRPORT_CODE, string ORIGIN_CITY, double DEST_AIRPORT_CODE, string DEST_CITY) {
    time = FLIGHT_TIME;
    airline_id = AIRLINE_ID;
    airline_name = AIRLINE_NAME;
    city_from_id = ORIGIN_AIRPORT_CODE;
    city_from = ORIGIN_CITY;
    city_to_id = DEST_AIRPORT_CODE;
    city_to = DEST_CITY;
}


void Flight::print() {

    cout << "Flight time: " << time << endl;
    cout << "Airline ID: " << airline_id << endl;
    cout << "Airline name: " << airline_name << endl;
    cout << "Origin IATA Airport code: " << city_from_id << endl;
    cout << "Origin city: " << city_from << endl;
    cout << "Destination IATA Airport code: " << city_to_id << endl;
    cout << "Dest city: " << city_to << endl;
    cout << endl;

}


void print_flights(vector<Flight>& Flights) {                      //print everything at once

    for (auto flight : Flights) {
        flight.print();
    }
}


void write_to_file(ofstream& new_file, vector<Flight>& Flights)
{
    new_file << "from.id" << "\t"                                    //headers
        << "to.id" << "\t"
        << "time" << "\t"
        << "airline.id" << "\t"
        << "airline.name" << "\t"
        << "city.fr." << "\t"
        << "city.to" << endl;
    for (auto flight : Flights) {
        new_file << flight.city_from_id << "\t"
            << flight.city_to_id << "\t"
            << flight.time << "\t"
            << flight.airline_id << "\t"
            << flight.airline_name << "\t"
            << flight.city_from << "\t"
            << flight.city_to << endl;
    }
}

void source_file_is_open(ifstream& datafile) {
    if (datafile.is_open()) {
        cerr << "File is open" << endl;
    }
    else {
        cerr << "File is not open" << endl;
    }
}


void target_file_is_open(ofstream& datafile) {
    if (datafile.is_open()) {
        cerr << "File is open" << endl;
    }
    else {
        cerr << "File is not open" << endl;
    }
}


void parsing(ifstream& datafile, ofstream& logfile) {

    source_file_is_open(datafile);
    target_file_is_open(logfile);

    vector<Flight> Flights;
    string line;


    while (!datafile.eof()) {                                     //whether the source file is finished
        getline(datafile, line);
        stringstream inputString(line);

        string tempString;
        int DEPARTURES_COMPLETE;
        string airline_name, city_from, city_to;
        double time, airline_id, city_from_id, city_to_id;

        size_t add = 0;

        for (size_t i = 0; i < 2; ++i) getline(inputString, tempString, ',');
        DEPARTURES_COMPLETE = stoi(tempString.c_str());

        for (size_t i = 0; i < 8; ++i) getline(inputString, tempString, ',');
        time = stof(tempString.c_str());

        for (size_t i = 0; i < 2; ++i) getline(inputString, tempString, ',');
        airline_id = stof(tempString.c_str());

        getline(inputString, airline_name, ',');
        if (airline_name[0] == '\"')
        {
            airline_name.erase(0, 1);
            add = 2;
        }

        for (size_t i = 0; i < 9 + add; ++i) getline(inputString, tempString, ',');
        city_from_id = stof(tempString.c_str());
        getline(inputString, city_from, ',');

        for (size_t i = 0; i < 11; ++i) getline(inputString, tempString, ',');
        city_to_id = stof(tempString.c_str());
        getline(inputString, city_to, ',');


        if (time > 0 && DEPARTURES_COMPLETE != 0)
        {
            Flight flight(time, airline_id, airline_name, city_from_id, city_from, city_to_id, city_to);
            Flights.push_back(flight);
        }
    }
    write_to_file(logfile, Flights);


    uint i = 0;


    datafile.close();
    logfile.close();

}


class Vertex {
public:
    int prev_vert = 0;
    int dist_from_start = INT_MAX;
};


class Neighbor {

public:
    int vertex_index;
    int dist;
    bool operator<(const Neighbor& other) const {
        return dist > other.dist;
    }

public:
    Neighbor(int v, int d) : vertex_index(v), dist(d) {}
};


void dijkstra(int start, int end, const vector<vector<int>>& fl_table)
{
    int table_size = fl_table.size();
    vector<Vertex> verts_obj(table_size);
    vector<int> stack_to_go;
    vector<bool> in_heap(table_size, false);
    MinHeap heap;

    heap.push({ start, 0 });
    verts_obj[start].dist_from_start = 0;

    while (!heap.empty()) {
        int current_vertex = heap.pop().vertex;

        for (int neighbor = 0; neighbor < table_size; ++neighbor) {
            if (fl_table[current_vertex][neighbor] != INT_MAX) { 
                stack_to_go.push_back(neighbor); 
            }
        }

        for (int neighbor : stack_to_go) {
            int new_dist = current_dist + fl_table[current_vertex][neighbor];
            if (new_dist < verts_obj[neighbor].dist_from_start) {
                verts_obj[neighbor].dist_from_start = new_dist;
                verts_obj[neighbor].prev_vert = current_vertex;
                if (in_heap[neighbor]) {
                    heap.push({ heighbor, new_dist });
                    in_heap[neighbor] = true;
                }
            }
        }
        stack_to_go.clear();
    }

    if (verts_obj[end].dist_from_start == INT_MAX) { cout << "No path found" << endl; }
    else {
        cout << "Shortest path: ";
        vector<int> path;

        for (int idx_vert = end; idx_vert != start; idx_vert = verts_obj[idx_vert].prev_vert)
            cout << idx_vert << " " << "<-" << " ";
        cout << start << endl;
        cout << "Time: " << verts_obj[end].dist_from_start << endl;
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
    datafile.open("new_data.txt");

    if (!datafile.is_open()) {
        cout << "Couldn't open datafile\n";
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

        if (flight_table[str][col] > time) { flight_table[str][col] = time; } //save only the min time
    }
}


void init() {
    int table_size = 40 * 1000;                                               //use only from ~ 30.000
    int start, end;
    unsigned int state, run = 1;

    vector<vector<int>> flight_table(table_size, vector<int>(table_size, INT_MAX));

    filling_table(flight_table);

    while (run) {                                                             //your choose
        cout << "to start press 1: ";
        cin >> state;

        switch (state) {
        case 0:
            run = 0;
            break;
        case 1:
            cout << "start: ";
            cin >> start;
            cout << "end: ";
            cin >> end;
            dijkstra(start, end, flight_table);
            break;
        }
    }
}


int main() {
    ifstream datafile("");
    ofstream logfile("new_data.txt");
    parsing(datafile, logfile);
    init();

    return 0;
}
