#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


struct Flight {
    double time;

    double carrier_id;
    string carrier_name;

    double city_from_id;
    string city_from;

    double city_to_id;
    string city_to;

    Flight(double AIR_TIME, double AIRLINE_ID, string UNIQUE_CARRIER_NAME, double ORIGIN_CITY_MARKET_ID, string ORIGIN_CITY, double DEST_CITY_MARKET_ID, string DEST_CITY);
    void display();
};


Flight::Flight(double AIR_TIME, double AIRLINE_ID, string UNIQUE_CARRIER_NAME, double ORIGIN_CITY_MARKET_ID, string ORIGIN_CITY, double DEST_CITY_MARKET_ID, string DEST_CITY)
{
    time = AIR_TIME;
    carrier_id = AIRLINE_ID;
    carrier_name = UNIQUE_CARRIER_NAME;
    city_from_id = ORIGIN_CITY_MARKET_ID;
    city_from = ORIGIN_CITY;
    city_to_id = DEST_CITY_MARKET_ID;
    city_to = DEST_CITY;
}


void Flight::display(void)
{
    cout << "AIR_TIME: " << time << "\t";
    cout << "AIRLINE_ID: " << carrier_id << "\t";
    cout << "UNIQUE_CARRIER_NAME: " << carrier_name << "\t";
    cout << "ORIGIN_CITY_MARKET_ID: " << city_from_id << "\t";
    cout << "ORIGIN_CITY: " << city_from << "\t";
    cout << "DEST_CITY_MARKET_ID: " << city_to_id << "\t";
    cout << "DEST_CITY: " << city_to << endl;
}


void displayFlights(vector<Flight>& Flights) {

    for (auto flight : Flights) {
        flight.display();
    }
}


void Write_to_file(ofstream& logfile, vector<Flight>& Flights)
{
    logfile     << "fr.id" << "\t"                << "to.id" << "\t"                << "time" << "\t"
                << "car.id" << "\t"               << "carrier.name" << "\t"         << "ci.fr." << "\t"
                << "ci.to" << endl;

    for (auto flight : Flights) {
        logfile << flight.city_from_id << "\t"    << flight.city_to_id << "\t"      << flight.time << "\t"
                << flight.carrier_id << "\t"      << flight.carrier_name << "\t"    << flight.city_from << "\t"
                << flight.city_to << endl;
    }
}


int main()
{
    ifstream datafile;
    datafile.open("data.csv");

    if (not datafile.is_open()) {
        cout << "Couldn't open datafile\n";
        return 0;
    }

    ofstream logfile;
    logfile.open("data_after_parse_1.txt");

    if (not logfile.is_open()) {
        cout << "Couldn't open logfile\n";
        return 0;
    }

    vector<Flight> Flights;
    string csvline;

    while (not datafile.eof()) {
        getline(datafile, csvline);
        stringstream inputString(csvline);

        string tempString;
        int DEPARTURES_PERFORMED;
        string carrier_name;
        string city_from;
        string city_to;
        double time, carrier_id, city_from_id, city_to_id;

        size_t add = 0;

        for (size_t idx = 0; idx < 2; ++idx) { getline(inputString, tempString, ','); }
        DEPARTURES_PERFORMED = atoi(tempString.c_str());

        for (size_t idx = 0; idx < 8; ++idx) { getline(inputString, tempString, ','); }
        time = atof(tempString.c_str());

        for (size_t idx = 0; idx < 2; ++idx) {getline(inputString, tempString, ',');}
        carrier_id = atof(tempString.c_str());

        getline(inputString, carrier_name, ',');
        if (carrier_name[0] == '\"') {
            carrier_name.erase(0, 1);
            add = 2;
        }

        for (size_t idx = 0; idx < 9 + add; ++idx) { getline(inputString, tempString, ','); }
        city_from_id = atof(tempString.c_str());
        getline(inputString, city_from, ',');

        for (size_t idx = 0; idx < 11; ++idx) { getline(inputString, tempString, ','); }
        city_to_id = atof(tempString.c_str());
        getline(inputString, city_to, ',');


        if (time > 0 && DEPARTURES_PERFORMED != 0) {
            Flight flight(time, carrier_id, carrier_name, city_from_id, city_from, city_to_id, city_to);
            Flights.push_back(flight);
        }
    }
    Write_to_file(logfile, Flights);

    datafile.close();
    logfile.close();
    return 0;
}