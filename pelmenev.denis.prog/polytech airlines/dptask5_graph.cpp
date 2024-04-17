#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>


using namespace std;

ifstream NEW_DATAFILE;
ofstream GRAPH_FILE;


class Airline
{
public:
    int air_time;
    int origin_sity_market_id;
    string origin_city_name;
    int dest_sity_market_id;
    string dest_city_name;
public:
    Airline();
    ~Airline();
    void clear();
};


class City
{
public:
    int id;
    string name;
    vector <Airline> airlines;
public:
    City();
    ~City();
    void clear();
};


class Graph 
{
private:
    vector <City> cities;
    int number_of_cities;
public:
    Graph();
    ~Graph();
    bool open_files(string data_file, string graph_file);
    void form_graph();
    void clear();
    void print();
private:
    void new_city(string txtline, Airline airline);
    Airline get_airline(string txtline);
    string get_string(string par_str, size_t &index);
    string get_string_on_quote(string par_str, size_t &index);
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


bool Graph::open_files(string data_file, string graph_file)
{
    NEW_DATAFILE.open(data_file);
    GRAPH_FILE.open(graph_file);

    if (!NEW_DATAFILE.is_open()) {
        cout << "Couldn't open datafile\n";
        return true;
    }

    if (!GRAPH_FILE.is_open()) {
        cout << "Couldn't open list_file\n";
        return true;
    }

    cout << "New Datafile is opened" << endl;

    return false;
}


void Graph::print()
{
    GRAPH_FILE << "Number of cities: " << number_of_cities << endl;
    GRAPH_FILE << "  " << endl;

    for (size_t city = 0; city < number_of_cities; city++) {
        GRAPH_FILE << cities[city].name << "  ";

        for (size_t line = 0; line < cities[city].airlines.size(); line++) {
            GRAPH_FILE << cities[city].airlines[line].dest_city_name << "  ";
        }

        GRAPH_FILE << endl;
    }
}


string Graph::get_string_on_quote(string par_str, size_t &index)
{
    string str_fnl;

    while (par_str[index] != '"') {
        str_fnl += par_str[index];
        index++;

        if (index >= par_str.size()) return str_fnl;
    }

    index += 2;

    return str_fnl;
}


string Graph::get_string(string par_str, size_t &index)
{
    if (par_str[index] == '"') {
        index++;

        return get_string_on_quote(par_str, index);
    }

    string str_fnl;

    while (par_str[index] != ',') {
        str_fnl += par_str[index];
        index++;

        if (index >= par_str.size()) return str_fnl;
    }

    index++;

    return str_fnl;
}


Airline Graph::get_airline(string txtline)
{
    Airline flight;
    size_t idx = 0;

    flight.air_time = stoi(get_string(txtline, idx));
    flight.origin_sity_market_id = stoi(get_string(txtline, idx));
    flight.origin_city_name = get_string(txtline, idx);
    flight.dest_sity_market_id = stoi(get_string(txtline, idx));
    flight.dest_city_name = get_string(txtline, idx);

    return flight;
}


void Graph::new_city(string txtline, Airline airline)
{
    City city;

    city.id = airline.origin_sity_market_id;
    city.name = airline.origin_city_name;
    city.airlines.push_back(airline);

    cities.push_back(city);
    number_of_cities++;
}


void Graph::form_graph()
{
    Airline airline;
    Graph graph;
    string txtline;

    getline(NEW_DATAFILE, txtline);
    getline(NEW_DATAFILE, txtline);

    airline = get_airline(txtline);
    new_city(txtline, airline);

    while (!NEW_DATAFILE.eof()) {
        airline.clear();

        getline(NEW_DATAFILE, txtline);

        airline = get_airline(txtline);

        for (size_t idx = 0; idx < number_of_cities; idx++) {
            if (airline.origin_sity_market_id == cities[idx].id) {
                cities[idx].airlines.push_back(airline);
                airline.clear();
                break;
            }
        }

        if (airline.air_time == 0) continue;

        new_city(txtline, airline);
    }
}


int main()
{
    Graph graph;

    if (graph.open_files("logfile.txt", "adj_list.txt")) return 0;

    graph.form_graph();
    graph.print();

    NEW_DATAFILE.close();
}
