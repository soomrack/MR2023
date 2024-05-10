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
    unsigned int air_time;
    unsigned int airline_id;
    unsigned int origin_city_market_id;
    std::string origin_city_name;
    unsigned int dest_city_market_id;
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
    unsigned int id;
    std::string name;
    std::vector <Airline> airlines;
public:
    City();
    ~City();
    void clear();
};


class Route
{
public:
    unsigned int total_air_time;
    std::vector <Airline> routes;
public:
    Route();
    ~Route();
    void clear_route();
    void print_route();
    void add_point(std::vector <Airline> &ways, size_t &count);
    void swap_elements(Airline &a, Airline &b);
    void heapify(std::vector <Airline> &ways, size_t size, int index);
private:
    std::vector <Airline> find_shorter_ways(std::vector <Airline> ways, size_t count, Airline new_way);
    bool shortcut(std::vector <Airline> &ways, size_t &count, Airline new_way);
    bool cut_useless(std::vector <Airline> &ways, size_t &count, size_t &idx);
};


class Graph : private Route
{
private:
    std::vector <City> cities;
    unsigned int number_of_cities;
public:
    Graph();
    ~Graph();
    bool open_files(const char data_file[], const char graph_file[]);
    void create_graph();
    Route find_way(const int origin, const int destination);
    void clear();
    void print();
private:
    void add_city(std::string txtline, Airline airline);
    void check_airline_id(Airline &airline, size_t idx);
    Airline get_airline(std::string txtline);
    bool check_city_id(const int city_id);
private:
    void add_ways(std::vector <Airline> &ways, City point, unsigned int current_time);
    void search_city(std::vector <Airline> &ways, Route result, const unsigned int city_id, unsigned int current_time);
private:
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
    origin_city_market_id = 0;
    dest_city_name = " ";
    dest_city_market_id = 0;
}


Airline& Airline::operator=(const Airline line)
{
    air_time = line.air_time;
    airline_id = line.airline_id;
    origin_city_name = line.origin_city_name;
    origin_city_market_id = line.origin_city_market_id;
    dest_city_name = line.dest_city_name;
    dest_city_market_id = line.dest_city_market_id;
}


Route::Route()
{
    clear_route();
}


Route::~Route()
{
    clear_route();
}


void Route::clear_route()
{
    total_air_time = 0;
    routes.clear();
}


void Route::print_route()
{
    std::cout << "Total air time: " << total_air_time << std::endl;
    std::cout << std::endl;

    if (routes.empty()) return;

    for (size_t idx = 0; idx < routes.size(); ++idx) {
        std::cout << routes[idx].origin_city_name << "  --->  ";
        std::cout << routes[idx].dest_city_name << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Have a good trip :)" << std::endl;
}


void Route::swap_elements(Airline &a, Airline &b)
{
    Airline buff;

    buff = a;
    a = b;
    b = buff;
}


void Route::heapify(std::vector <Airline> &ways, size_t size, int index)
{
	size_t max = index;
	size_t left = 2 * index + 1;
	size_t right = 2 * index + 2;

	if (left < size && ways[left].air_time < ways[max].air_time) max = left;

	if (right < size && ways[right].air_time < ways[max].air_time) max = right;

	if (max != index) {
		swap_elements(ways[index], ways[max]);

		heapify(ways, size, max);
	}
}


std::vector <Airline> Route::find_shorter_ways(std::vector <Airline> ways, size_t count, Airline new_way)
{
    std::vector <Airline> shorter_ways;

    for (size_t idx = 0; idx < ways.size(); ++idx) {
        if (new_way.dest_city_market_id == ways[idx].dest_city_market_id) {
            for (size_t line = 0; line < routes.size(); ++line) {
                if (ways[idx].origin_city_market_id == routes[line].origin_city_market_id) {
                    if (new_way.air_time >= ways[idx].air_time) {
                        shorter_ways.push_back(ways[idx]);
                        heapify(shorter_ways, shorter_ways.size(), 0);
                    }

                    break;
                }
            }
        }
    }

    return shorter_ways;
}


bool Route::shortcut(std::vector <Airline> &ways, size_t &count, Airline new_way)
{
    std::vector <Airline> shorter_ways = find_shorter_ways(ways, count, new_way);

    if (shorter_ways.empty()) return false;

    size_t line = 0;

    while (routes[line].origin_city_market_id != shorter_ways[0].origin_city_market_id)
        line++;

    while (routes.size() > line) {
        routes.erase(routes.end() - 1);
        count--;
    }

    routes.push_back(shorter_ways[0]);
    count++;
    total_air_time = routes[count].air_time;

    for (size_t idx = 0; idx < ways.size(); ++idx) {
        if (shorter_ways[0].origin_city_market_id == ways[idx].origin_city_market_id &&
        shorter_ways[0].dest_city_market_id == ways[idx].dest_city_market_id) {
            ways.erase(ways.begin() + idx);
            break;
        }
    }

    return true;
}


bool Route::cut_useless(std::vector <Airline> &ways, size_t &count, size_t &idx)
{
    if (ways[idx].dest_city_market_id == routes[count].origin_city_market_id &&
    ways[idx].origin_city_market_id == routes[count].dest_city_market_id) {
        if (routes[count].dest_city_market_id != ways[idx + 1].origin_city_market_id) {
            routes.erase(routes.end() - 1);
            ways.erase(ways.begin() + idx);
            count--;
            return true;
        }
    }

    return false;
}


void Route::add_point(std::vector <Airline> &ways, size_t &count)
{
    size_t idx = 0;

    while (idx < ways.size()) {
        if (routes[count].dest_city_market_id == ways[idx].origin_city_market_id) break;
        idx++;
    }

    if (idx == ways.size()) {
        routes.erase(routes.begin() + count);
        count--;
        return;
    }

    if (shortcut(ways, count, ways[idx])) return;

    if (cut_useless(ways, count, idx)) return;

    routes.push_back(ways[idx]);
    ways.erase(ways.begin() + idx);
    count++;
    total_air_time = routes[count].air_time;
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
            GRAPH_FILE << "(" << cities[city].airlines[line].dest_city_market_id << ")" << " ";
            GRAPH_FILE << "[" << cities[city].airlines[line].air_time << "]" << "  ";
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
    flight.origin_city_market_id = std::stoi(get_string(txtline, idx));
    flight.origin_city_name = get_string(txtline, idx);
    flight.dest_city_market_id = std::stoi(get_string(txtline, idx));
    flight.dest_city_name = get_string(txtline, idx);

    return flight;
}


void Graph::add_city(std::string txtline, Airline airline)
{
    City city;

    city.id = airline.origin_city_market_id;
    city.name = airline.origin_city_name;
    city.airlines.push_back(airline);

    cities.push_back(city);
    number_of_cities++;
}


void Graph::check_airline_id(Airline &airline, size_t idx)
{
    for (size_t line = 0; line < cities[idx].airlines.size(); ++line) {
        if (airline.dest_city_market_id == cities[idx].airlines[line].dest_city_market_id &&
        airline.airline_id == cities[idx].airlines[line].airline_id) {
            airline.clear();
            return;
        }
    }
}


void Graph::create_graph()
{
    Airline airline;
    Graph graph;
    std::string txtline;

    while (!NEW_DATAFILE.eof()) {
        std::getline(NEW_DATAFILE, txtline);

        if (txtline.empty() || txtline[0] == ' ') break;
        if (txtline[0] == 'A') continue;

        airline = get_airline(txtline);
        if (airline.dest_city_market_id == airline.origin_city_market_id) continue;

        for (size_t idx = 0; idx < number_of_cities; idx++) {
            if (airline.origin_city_market_id == cities[idx].id) {
                check_airline_id(airline, idx);

                if (airline.air_time == 0) break;
 
                cities[idx].airlines.push_back(airline);
                airline.clear();
                break;
            }
        }

        if (airline.air_time == 0) continue;

        add_city(txtline, airline);

        airline.clear();
    }
}


void Graph::add_ways(std::vector <Airline> &ways, City point, unsigned int current_time)
{
    if (ways.empty()) {
        for (size_t line = 0; line < point.airlines.size(); ++line) {
            ways.insert(ways.begin(), point.airlines[line]);

            heapify(ways, ways.size(), 0);
        }

        return;
    }

    std::vector <Airline> new_ways;

    for (size_t line = 0; line < point.airlines.size(); ++line) {
        point.airlines[line].air_time += current_time;

        new_ways.insert(new_ways.begin(), point.airlines[line]);

        heapify(new_ways, new_ways.size(), 0);
    }

    ways.insert(ways.end(), new_ways.begin(), new_ways.end());
}


void Graph::search_city(std::vector <Airline> &ways, Route result, const unsigned int city_id, unsigned int current_time)
{
    if (!result.routes.empty() && !ways.empty())
        for (size_t idx = 0; idx < ways.size(); ++idx)
            if (city_id == ways[idx].origin_city_market_id) return;
        

    for (size_t city = 0; city < number_of_cities; ++city) {
        if (city_id == cities[city].id) {
            add_ways(ways, cities[city], current_time);
            return;
        }
    }
}


bool Graph::check_city_id(const int city_id)
{
    for (size_t city = 0; city < number_of_cities; ++city) {
        if (city_id == cities[city].id) {
            return false;
        }
    }

    std::cout << "Invalid City ID" << std::endl;

    return true;
}


Route Graph::find_way(const int origin, const int destination)
{
    Route result;

    if (check_city_id(origin)) return result;
    if (check_city_id(destination)) return result;

    std::vector <Airline> ways;

    search_city(ways, result, origin, 0);
    result.routes.push_back(ways[0]);
    result.total_air_time = ways[0].air_time;

    if (result.routes[0].dest_city_market_id == destination) return result;

    size_t count = 0;

    while (!ways.empty()) {
        search_city(ways, result, result.routes[count].dest_city_market_id, result.total_air_time);
        result.add_point(ways, count);

        if (result.routes.empty()) break;
        if (result.routes[count].dest_city_market_id == destination) return result;
    }

    result.clear_route();

    std::cout << "The route is not found" << std::endl;

    return result;
}


int main()
{
    Graph graph;

    if (!graph.open_files("log_test.txt", "adj_list.txt")) return 0;

    std::cout << "__________________" << std::endl;

    graph.create_graph();
    std::cout << "The Graph is created" << std::endl;
    graph.print();

    std::cout << "__________________" << std::endl;

    Route graph_result = graph.find_way(34614, 34027);
    graph_result.print_route();

    NEW_DATAFILE.close();
    GRAPH_FILE.close();

    std::cout << "__________________" << std::endl;
    std::cout << "Datafile is closed" << std::endl;
}
