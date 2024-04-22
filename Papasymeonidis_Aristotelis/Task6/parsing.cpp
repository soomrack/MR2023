/*
start project: 14/04/2024
tg/inst/git/vk - simeonidi03
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <climits>


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


void deikstra(int start, int end, const std::vector<std::vector<int>>& fl_table)
{
    int table_size = fl_table.size();
    std::vector<Vertex> verts_obj(table_size);
    std::vector<int> stack_to_go;
    std::priority_queue<Neighbor> queue;

    queue.push({ start, 0 });
    verts_obj[start].dist_from_start = 0;

    while (!queue.empty()) {
        int current_vertex = queue.top().vertex_index;
        int current_dist = queue.top().dist;
        queue.pop();

        for (int neighbor = 0; neighbor < table_size; ++neighbor) {
            if (fl_table[current_vertex][neighbor] != INT_MAX) { stack_to_go.push_back(neighbor); }
        }

        for (int neighbor : stack_to_go) {
            int new_dist = current_dist + fl_table[current_vertex][neighbor];
            if (new_dist < verts_obj[neighbor].dist_from_start) {
                verts_obj[neighbor].dist_from_start = new_dist;
                verts_obj[neighbor].prev_vert = current_vertex;
                queue.push({ neighbor, new_dist });
            }
        }
        stack_to_go.clear();
    }


    if (verts_obj[end].dist_from_start == INT_MAX) { std::cout << "No path found" << std::endl; }
    else {
        std::cout << "Shortest path: ";
        std::vector<int> path;

        for (int idx_vert = end; idx_vert != start; idx_vert = verts_obj[idx_vert].prev_vert)
            std::cout << idx_vert << " " << "<-" << " ";
        std::cout << start << std::endl;
        std::cout << "Time: " << verts_obj[end].dist_from_start << std::endl;
    }
}


void print_flight_table(const std::vector<std::vector<int>>& flight_table)
{
    int table_size = flight_table.size();

    for (int i = 0; i < table_size; ++i) {
        std::cout << i << "  ";
        for (int j = 0; j < table_size; ++j) {
            if (flight_table[i][j] == INT_MAX) { std::cout << "INF "; }
            else { std::cout << flight_table[i][j] << "   "; }
        }
    }
}


void filling_table(std::vector<std::vector<int>>& flight_table)
{
    std::ifstream datafile;
    datafile.open("/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis_Aristotelis/Task6/build/new_data.txt");

    if (!datafile.is_open()) {
        std::cout << "Couldn't open datafile\n";
        return;
    }

    std::string txtline;
    while (!datafile.eof()) {
        getline(datafile, txtline);
        std::stringstream inputString(txtline);

        int str, col, time;
        std::string tempString;

        getline(inputString, tempString, '\t');
        str = atoi(tempString.c_str());

        getline(inputString, tempString, '\t');
        col = atoi(tempString.c_str());

        std::getline(inputString, tempString, '\t');
        time = atoi(tempString.c_str());

        if (flight_table[str][col] > time) { flight_table[str][col] = time; }
    }
}


void init() {
    int table_size = 40 * 1000;
    int start, end;
    unsigned int state, run = 1;

    std::vector<std::vector<int>> flight_table(table_size, std::vector<int>(table_size, INT_MAX));

    filling_table(flight_table);

    while (run) {
        std::cout << "to start press 1: ";
        std::cin >> state;

        switch (state) {
        case 0:
            run = 0;
            break;
        case 1:
            std::cout << "start: "; 
            std::cin >> start;
            std::cout << "end: ";
            std::cin >> end;
            deikstra(start, end, flight_table);
            break;
        }
    }
}

class Flight
{
public:
    Flight(double FLIGHT_TIME, double AIRLINE_ID, std::string UNIQUE_AIRLINES_NAME, double ORIGIN_IATA_AIRPORT_CODE,
           std::string ORIGIN_CITY, double DEST_IATA_AIRPORT_CODE, std::string DEST_CITY);

    void print();

    double time;
    double airline_id;
    std::string airline_name;
    double city_from_id;
    std::string city_from;
    double city_to_id;
    std::string city_to;
};


Flight::Flight(double FLIGHT_TIME, double AIRLINE_ID, std::string UNIQUE_AIRLINES_NAME, double ORIGIN_IATA_AIRPORT_CODE, std::string ORIGIN_CITY, double DEST_IATA_AIRPORT_CODE, std::string DEST_CITY){
    time = FLIGHT_TIME;
    airline_id = AIRLINE_ID;
    airline_name = UNIQUE_AIRLINES_NAME;
    city_from_id = ORIGIN_IATA_AIRPORT_CODE;
    city_from = ORIGIN_CITY;
    city_to_id = DEST_IATA_AIRPORT_CODE;
    city_to = DEST_CITY;
}


void Flight::print(){

   std::cout << "Flight time: " << time << std::endl;
   std::cout << "Airline ID: " << airline_id << std::endl;
   std::cout << "Airline name: " << airline_name << std::endl;
   std::cout << "Origin IATA Airport code: " << city_from_id << std::endl;
   std::cout << "Origin city: " << city_from << std::endl;
   std::cout << "Destination IATA Airport code: " << city_to_id << std::endl;
   std::cout << "Dest city: " << city_to << std::endl;
   std::cout << std::endl;

}


void print_flights(std::vector<Flight>& Flights){

    for (auto flight : Flights) {
        flight.print();
    }
}


void write_to_file(std::ofstream& new_file, std::vector<Flight>& Flights)
{
    new_file << "fr.id" << "\t" 
        << "to.id" << "\t" 
        << "time" << "\t" 
        << "car.id" << "\t" 
        << "carrier.name" << "\t" 
        << "ci.fr." << "\t" 
        << "ci.to" << std::endl;
    for (auto flight : Flights) {
        new_file << flight.city_from_id << "\t" 
            << flight.city_to_id << "\t" 
            << flight.time << "\t" 
            << flight.airline_id << "\t" 
            << flight.airline_name << "\t" 
            << flight.city_from << "\t" 
            << flight.city_to << std::endl;
    }
}

void source_file_is_open(std::ifstream& datafile){
    if(datafile.is_open()){
        std::cerr<<"File is open"<<std::endl;
    }else{
        std::cerr<<"File is not open"<<std::endl;
    }
}


void target_file_is_open(std::ofstream& datafile){
    if(datafile.is_open()){
        std::cerr<<"File is open"<<std::endl;
    }else{
        std::cerr<<"File is not open"<<std::endl;
    }
}


void parsing(std::ifstream& datafile, std::ofstream& logfile){

    source_file_is_open(datafile);
    target_file_is_open(logfile);

    std::vector<Flight> Flights;
    std::string line;


//закончился ли исходный файл
    while(!datafile.eof()){
        std::getline(datafile, line);
        std::stringstream inputString(line);
        
        std::string tempString;
        int DEPARTURES_COMPLETE;
        std::string carrier_name, city_from, city_to;
        double time, carrier_id, city_from_id, city_to_id;

        size_t add = 0;


        for (size_t i = 0; i < 2; ++i) getline(inputString, tempString, ',');
        DEPARTURES_COMPLETE = std::stoi(tempString.c_str()); 

        for (size_t i = 0; i < 8; ++i) getline(inputString, tempString, ',');
        time = std::stof(tempString.c_str()); 

        for (size_t i = 0; i < 2; ++i) getline(inputString, tempString, ',');
        carrier_id = std::stof(tempString.c_str()); 

        getline(inputString, carrier_name, ','); 
        if (carrier_name[0] == '\"') 
        {
            carrier_name.erase(0, 1);
            add = 2;
        }       

        for (size_t i = 0; i < 9 + add; ++i) getline(inputString, tempString, ',');
        city_from_id = std::stof(tempString.c_str()); 
        getline(inputString, city_from, ',');

        for (size_t i = 0; i < 11; ++i) getline(inputString, tempString, ',');
        city_to_id = std::stof(tempString.c_str()); 
        getline(inputString, city_to, ','); 


        if (time > 0 && DEPARTURES_COMPLETE != 0)
        {
            Flight flight(time, carrier_id, carrier_name, city_from_id, city_from, city_to_id, city_to);
            Flights.push_back(flight);
        }
    }
    //displayFlights(Flights);
    write_to_file(logfile, Flights);

    

    uint i = 0;



    datafile.close();
    logfile.close();

}

int main(){
    std::ifstream datafile("/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis_Aristotelis/Task6/dataterm.csv");
    std::ofstream logfile("new_data.txt");
    parsing(datafile, logfile);
    init();



    return 0;
}