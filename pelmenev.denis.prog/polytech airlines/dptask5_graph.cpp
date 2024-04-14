#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>


using namespace std;

ifstream NEW_DATAFILE;


struct OneFlight
{
    int air_time;
    int airline_id;
    string unique_carrier_name;
    int origin_sity_market_id;
    string origin_city_name;
    int dest_sity_market_id;
    string dest_city_name;
};


struct Flights
{
    vector <OneFlight> flight;
    size_t number_of_flights = 0;
};


struct Vertex
{
    string city_name;
    int city_id;
    int weight;
    int marker;
    //Vertex* previous_vertex;
};


struct Edges
{
    vector <Vertex> line;
};


struct AdjencencyList
{
    size_t number_of_cities = 0;
    vector <Edges> list;
};


void print_one_flight(OneFlight flight)
{
    cout << flight.air_time << endl;
    cout << flight.airline_id << endl;
    cout << flight.unique_carrier_name << endl;
    cout << flight.origin_sity_market_id << endl;
    cout << flight.origin_city_name << endl;
    cout << flight.dest_sity_market_id << endl;
    cout << flight.dest_city_name << endl;
}


string get_string_on_quote(string par_str, size_t &index)
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


string get_string(string par_str, size_t &index)
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


struct OneFlight get_one_flight(string txtline)
{
    OneFlight flight;
    size_t idx = 0;

    flight.air_time = stoi(get_string(txtline, idx));
    flight.airline_id = stoi(get_string(txtline, idx));
    flight.unique_carrier_name = get_string(txtline, idx);
    flight.origin_sity_market_id = stoi(get_string(txtline, idx));
    flight.origin_city_name = get_string(txtline, idx);
    flight.dest_sity_market_id = stoi(get_string(txtline, idx));
    flight.dest_city_name = get_string(txtline, idx);

    return flight;
}


struct Flights get_flights()
{
    Flights flights;
    OneFlight one_flight;

    string txtline;

    while (!NEW_DATAFILE.eof()) {
        getline(NEW_DATAFILE, txtline);

        if (txtline[0] == 'A') continue;

        one_flight = get_one_flight(txtline);

        flights.flight.push_back(one_flight);

        flights.number_of_flights++;
    }

    return flights;
}


void list_set_vertex(Vertex &vertex, Flights flights, size_t idx)
{
    vertex.city_id = flights.flight[idx].origin_sity_market_id;
    vertex.city_name = flights.flight[idx].origin_city_name;
}


void list_set_link(Vertex &vertex, Flights flights, size_t idx)
{
    vertex.city_id = flights.flight[idx].dest_sity_market_id;
    vertex.city_name = flights.flight[idx].dest_city_name;
    vertex.weight = flights.flight[idx].air_time;
}


void list_set_new_city(Vertex &vertex, Edges &line, Flights flights, size_t idx)
{
    list_set_vertex(vertex, flights, idx);
    line.line.push_back(vertex);
    list_set_link(vertex, flights, idx);
    line.line.push_back(vertex);
}


struct AdjencencyList get_list(Flights flights)
{
    AdjencencyList fnl_list;
    Vertex vertex;
    Edges line;

    list_set_new_city(vertex, line, flights, 0);

    fnl_list.list.push_back(line);
    fnl_list.number_of_cities++;

    for (size_t idx = 1; idx < flights.number_of_flights; idx++) {
        line.line.clear();

        for (size_t city = 0; city < fnl_list.number_of_cities; city++) {
            if (flights.flight[idx].origin_sity_market_id == fnl_list.list[idx].line[0].city_id) {
                list_set_link(vertex, flights, idx);
                fnl_list.list[city].line.push_back(vertex);
                break;
            }

            list_set_new_city(vertex, line, flights, idx);

            fnl_list.list.push_back(line);
            fnl_list.number_of_cities++;
        }
    }

    return fnl_list;
}


int main()
{
    NEW_DATAFILE.open("log_test.txt");

    if (!NEW_DATAFILE.is_open()) {
        cout << "Couldn't open datafile\n";
        return 0;
    }

    cout << "New Datafile is opened" << endl;

    Flights flights = get_flights();
    AdjencencyList list = get_list(flights);

    NEW_DATAFILE.close();

    cout << flights.number_of_flights << endl;
    cout << list.number_of_cities << endl;
}