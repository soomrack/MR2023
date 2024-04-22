#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>


std::ifstream NEW_DATAFILE;
std::ofstream GRAPH_FILE;


class Airline
{
public:
    int air_time;
    int airline_id;
    int origin_sity_market_id;
    std::string origin_city_name;
    int dest_sity_market_id;
    std::string dest_city_name;
public:
    Airline();
    ~Airline();
    void clear();
public:
    Airline& operator=(const Airline line);
};


class City
{
public:
    int id;
    std::string name;
    std::vector <Airline> airlines;
public:
    City();
    ~City();
    void clear();
};


class DijkstraResult
{
public:
    int total_air_time;
    std::vector <Airline> route;
public:
    DijkstraResult();
    ~DijkstraResult();
    void clear();
    void print();
};


class Graph 
{
private:
    std::vector <City> cities;
    int number_of_cities;
public:
    Graph();
    ~Graph();
    bool open_files(const char data_file[], const char graph_file[]);
    void form_graph();
    DijkstraResult find_way(const int origin, const int destination);
    void clear();
    void print();
private:
    void new_city(std::string txtline, Airline airline);
    void check_airline_id(Airline &airline, size_t idx);
    Airline get_airline(std::string txtline);
private:
    void add_ways(std::vector <Airline> &ways, City point, int current_time);
    int search_city(std::vector <Airline> &ways, const int city_id, int current_time);
    bool check_destination(std::vector <Airline> &ways, City point, size_t line, size_t size);
    void check_points(std::vector <Airline> &ways, City point, size_t line, size_t size, int current_time);
private:
    void heap_tree(std::vector <Airline> &ways, size_t size, int index);
    void swap_elements(Airline &a, Airline &b);
    std::string get_string(std::string par_str, size_t &index);
    std::string get_string_on_quote(std::string par_str, size_t &index);
};


Graph::Graph()
{
    clear();
}


Graph::~Graph()
{
    clear();
}


void Graph::clear()
{
    cities.clear();
    number_of_cities = 0;
}


City::City()
{
    clear();
}


City::~City()
{
    clear();
}


void City::clear()
{
    id = 0;
    name = " ";
    airlines.clear();
}


Airline::Airline()
{
    clear();
}


Airline::~Airline()
{
    clear();
}


void Airline::clear()
{
    air_time = 0;
    origin_city_name = " ";
    origin_sity_market_id = 0;
    dest_city_name = " ";
    dest_sity_market_id = 0;
}


Airline& Airline::operator=(const Airline line)
{
    air_time = line.air_time;
    airline_id = line.airline_id;
    origin_city_name = line.origin_city_name;
    origin_sity_market_id = line.origin_sity_market_id;
    dest_city_name = line.dest_city_name;
    dest_sity_market_id = line.dest_sity_market_id;
}


DijkstraResult::DijkstraResult()
{
    clear();
}


DijkstraResult::~DijkstraResult()
{
    clear();
}


void DijkstraResult::clear()
{
    total_air_time = 0;
    route.clear();
}


void DijkstraResult::print()
{
    std::cout << "Total air time: " << total_air_time << std::endl;

    std::cout << route[0].origin_city_name << std::endl;

    for (size_t idx = 0; idx < route.size(); ++idx) {
        std::cout << route[idx].dest_sity_market_id << std::endl;
    }
}


bool Graph::open_files(const char data_file[], const char graph_file[])
{
    NEW_DATAFILE.open(data_file);
    GRAPH_FILE.open(graph_file);

    if (!NEW_DATAFILE.is_open()) {
        std::cout << "Couldn't open datafile\n";
        return false;
    }

    if (!GRAPH_FILE.is_open()) {
        std::cout << "Couldn't open list_file\n";
        return false;
    }

    std::cout << "New Datafile is opened" << std::endl;

    return true;
}


void Graph::print()
{
    GRAPH_FILE << "Number of cities: " << number_of_cities << std::endl;
    GRAPH_FILE << "  " << std::endl;

    for (size_t city = 0; city < number_of_cities; city++) {
        GRAPH_FILE << cities[city].name << " ";
        GRAPH_FILE << "(" << cities[city].id << ")" << "  ";

        for (size_t line = 0; line < cities[city].airlines.size(); line++) {
            GRAPH_FILE << cities[city].airlines[line].dest_city_name << " ";
            GRAPH_FILE << "(" << cities[city].airlines[line].dest_sity_market_id << ")" << "  ";
        }

        GRAPH_FILE << std::endl;
    }
}


std::string Graph::get_string_on_quote(std::string par_str, size_t &index)
{
    std::string str_fnl;

    while (par_str[index] != '"') {
        str_fnl += par_str[index];
        index++;

        if (index >= par_str.size()) return str_fnl;
    }

    index += 2;

    return str_fnl;
}


std::string Graph::get_string(std::string par_str, size_t &index)
{
    if (par_str[index] == '"') {
        index++;

        return get_string_on_quote(par_str, index);
    }

    std::string str_fnl;

    while (par_str[index] != ',') {
        str_fnl += par_str[index];
        index++;

        if (index >= par_str.size()) return str_fnl;
    }

    index++;

    return str_fnl;
}


Airline Graph::get_airline(std::string txtline)
{
    Airline flight;
    size_t idx = 0;

    flight.air_time = std::stoi(get_string(txtline, idx));
    flight.airline_id = std::stoi(get_string(txtline, idx));
    flight.origin_sity_market_id = std::stoi(get_string(txtline, idx));
    flight.origin_city_name = get_string(txtline, idx);
    flight.dest_sity_market_id = std::stoi(get_string(txtline, idx));
    flight.dest_city_name = get_string(txtline, idx);

    return flight;
}


void Graph::new_city(std::string txtline, Airline airline)
{
    City city;

    city.id = airline.origin_sity_market_id;
    city.name = airline.origin_city_name;
    city.airlines.push_back(airline);

    cities.push_back(city);
    number_of_cities++;
}


void Graph::check_airline_id(Airline &airline, size_t idx)
{
    for (size_t line = 0; line < cities[idx].airlines.size(); ++line) {
        if (airline.dest_sity_market_id == cities[idx].airlines[line].dest_sity_market_id &&
        airline.airline_id == cities[idx].airlines[line].airline_id) {
            airline.clear();
            return;
        }
    }
}


void Graph::form_graph()
{
    Airline airline;
    Graph graph;
    std::string txtline;

    while (!NEW_DATAFILE.eof()) {
        std::getline(NEW_DATAFILE, txtline);

        if (txtline.empty()) break;
        if (txtline[0] == 'A') continue;

        airline = get_airline(txtline);

        for (size_t idx = 0; idx < number_of_cities; idx++) {
            if (airline.origin_sity_market_id == cities[idx].id) {
                check_airline_id(airline, idx);

                if (airline.air_time == 0) break;
 
                cities[idx].airlines.push_back(airline);
                airline.clear();
                break;
            }
        }

        if (airline.air_time == 0) continue;

        new_city(txtline, airline);

        airline.clear();
    }
}


void Graph::swap_elements(Airline &a, Airline &b)
{
    Airline buff;

    buff = a;
    a = b;
    b = buff;
}


void Graph::heap_tree(std::vector <Airline> &ways, size_t size, int index)
{
	size_t max = index;
	size_t left = 2 * index + 1;
	size_t right = 2 * index + 2;

	if (left < size && ways[left].air_time < ways[max].air_time) max = left;

	if (right < size && ways[right].air_time < ways[max].air_time) max = right;

	if (max != index) {
		swap_elements(ways[index], ways[max]);

		heap_tree(ways, size, max);
	}
}


bool Graph::check_destination(std::vector <Airline> &ways, City point, size_t line, size_t size)
{
    for (size_t idx = 0; idx < size; ++idx) {
        if (point.airlines[line].dest_sity_market_id == ways[idx].origin_sity_market_id &&
        point.airlines[line].origin_sity_market_id == ways[idx].dest_sity_market_id) {
            return true;
        }
    }

    return false;
}


void Graph::check_points(std::vector <Airline> &ways, City point, size_t line, size_t size, int current_time)
{
    for (size_t idx = 0; idx < size; ++idx) {
        if (point.airlines[line].dest_sity_market_id == ways[idx].dest_sity_market_id) {
            if (point.airlines[line].air_time + current_time < ways[idx].air_time) {
                ways[idx] = point.airlines[line];
                return;
            }
        }
    }
}


void Graph::add_ways(std::vector <Airline> &ways, City point, int current_time)
{
    if (ways.empty()) {
        for (size_t line = 0; line < point.airlines.size(); ++line) {
            ways.insert(ways.begin(), point.airlines[line]);

            heap_tree(ways, ways.size(), 0);
        }

        return;
    }

    size_t size = ways.size();

    for (size_t line = 0; line < point.airlines.size(); ++line) {
        if (check_destination(ways, point, line, size)) continue;

        check_points(ways, point, line, size, current_time);

        ways.insert(ways.begin(), point.airlines[line]);
        ways[0].air_time += current_time;

        heap_tree(ways, ways.size(), 0);
    }
}


int Graph::search_city(std::vector <Airline> &ways, const int city_id, int current_time)
{
    for (size_t city = 0; city < number_of_cities; ++city) {
        if (city_id == cities[city].id) {
            add_ways(ways, cities[city], current_time);
            return 1;
        }
    }

    return 0;
}


DijkstraResult Graph::find_way(const int origin, const int destination)
{
    DijkstraResult result;
    std::vector <Airline> ways;

    int mark;

    mark = search_city(ways, origin, 0);

    if (ways.empty()) {
        std::cout << "Invalid City ID" << std::endl;
        return result;
    }

    size_t count = 0;

    while (!ways.empty()) {
        result.route.push_back(ways[0]);
        result.total_air_time += ways[0].air_time;
        ways.erase(ways.begin());

        mark = search_city(ways, result.route[count].origin_sity_market_id, result.total_air_time);

        if (mark == 0) {
            result.route.erase(result.route.end() - 1);
            continue;
        }

        if (result.route[count].dest_sity_market_id == destination) return result;

        count++;
    }

    result.clear();

    std::cout << "The route is not found" << std::endl;

    return result;
}


int main()
{
    Graph graph;

    if (!graph.open_files("log_test.txt", "adj_list.txt")) return 0;

    graph.form_graph();
    graph.print();

    DijkstraResult graph_result = graph.find_way(34886, 34027);
    graph_result.print();

    NEW_DATAFILE.close();
    GRAPH_FILE.close();

    std::cout << "Datafile is closed" << std::endl;
}
