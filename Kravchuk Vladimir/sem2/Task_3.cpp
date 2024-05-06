#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


class Flight {
public:
    double time;
    double airline_id;
    double city_from_id;
    double city_to_id;
    string carrier_name;
    string city_from;
    string city_to;

    Flight(double AIR_TIME, double AIRLINE_ID, string UNIQUE_CARRIER_NAME, double ORIGIN_CITY_MARKET_ID,
        string ORIGIN_CITY, double DEST_CITY_MARKET_ID, string DEST_CITY);
};


Flight::Flight(double AIR_TIME, double AIRLINE_ID, string UNIQUE_CARRIER_NAME, double ORIGIN_CITY_MARKET_ID,
    string ORIGIN_CITY, double DEST_CITY_MARKET_ID, string DEST_CITY)
{
    time = AIR_TIME;
    airline_id = AIRLINE_ID;
    city_from_id = ORIGIN_CITY_MARKET_ID;
    city_to_id = DEST_CITY_MARKET_ID;
    carrier_name = UNIQUE_CARRIER_NAME;
    city_from = ORIGIN_CITY;
    city_to = DEST_CITY;
}


void write_to_logfile(ofstream& logfile, vector<Flight>& Flights)
{
    logfile << "from_id" << "\t"
        << "to_id" << "\t"
        << "time" << "\t"
        << "city_from" << "\t"
        << "city_to" << "\t\t"
        << "airline_id" << "\t"
        << "carrier_name" << endl;

    for (auto flight : Flights) { // Change Flights->auto
        logfile << flight.city_from_id << "\t"
            << flight.city_to_id << "\t"
            << flight.time << "\t"
            << flight.city_from << "\t"
            << flight.city_to << "\t"
            << flight.airline_id << "\t"
            << flight.carrier_name << endl;
    }
}


int main()
{
    std::ifstream datafile;
    datafile.open("data.csv");

    std::ofstream logfile;
    logfile.open("logfile.txt");

    if (not logfile.is_open()) {
        std::cout << "Couldn't open logfile\n";
        return 0;
    }

    if (not datafile.is_open()) {
        std::cout << "Couldn't open datafile\n";
        return 0;
    }

    vector<Flight> Flights;
    std::string csvline;

    while (not datafile.eof()) {
        getline(datafile, csvline);
        stringstream inputString(csvline);

        string bufString;
        int DEPARTURES_PERFORMED;
        string carrier_name;
        string city_from;
        string city_to;
        double time, airline_id, city_from_id, city_to_id;

        size_t add = 0;

        for (size_t idx = 0; idx < 2; ++idx)
            getline(inputString, bufString, ',');
        DEPARTURES_PERFORMED = atoi(bufString.c_str());

        for (size_t idx = 0; idx < 8; ++idx)
            getline(inputString, bufString, ',');
        time = atof(bufString.c_str());

        for (size_t idx = 0; idx < 2; ++idx)
            getline(inputString, bufString, ',');
        airline_id = atof(bufString.c_str());

        getline(inputString, carrier_name, ',');
        if (carrier_name[0] == '\"')
        {
            carrier_name.erase(0, 1);
            add = 2;
        }

        for (size_t idx = 0; idx < 9 + add; ++idx)
            getline(inputString, bufString, ',');
        city_from_id = atof(bufString.c_str());
        getline(inputString, city_from, ',');

        for (size_t idx = 0; idx < 11; ++idx)
            getline(inputString, bufString, ',');
        city_to_id = atof(bufString.c_str());
        getline(inputString, city_to, ',');

        if (time > 0 && DEPARTURES_PERFORMED != 0)
        {
            Flight flight(time, airline_id, carrier_name, city_from_id, city_from, city_to_id, city_to);
            Flights.push_back(flight);
        }
    }

    write_to_logfile(logfile, Flights);

    datafile.close();
    logfile.close();
    return 0;
}
