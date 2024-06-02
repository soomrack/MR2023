#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


class Flight {
public:
    double time;
    double carrier_id;
    std::string carrier_name;
    double city_from_id;
    std::string city_from;
    double city_to_id;
    std::string city_to; 

    Flight(double air_time, double airline_id, std::string unique_carrier_name,
        double origin_city_market_id, std::string origin_city, double dest_city_market_id,
        std::string dest_city);

    void display() const;
};


Flight::Flight(double air_time, double airline_id, std::string airline_name,
    double origin_city_id, std::string origin_city, double destination_city_id,
    std::string destination_city)
{
    time = air_time;
    carrier_id = airline_id;
    carrier_name = airline_name;
    city_from_id = origin_city_id;
    city_from = origin_city;
    city_to_id = destination_city_id;
    city_to = destination_city;
}


void Flight::display() const
{
    std::cout << "Air time: " << time << "\t";
    std::cout << "Airline ID: " << carrier_id << "\t";
    std::cout << "Airline name: " << carrier_name << "\t";
    std::cout << "Origin city ID: " << city_from_id << "\t";
    std::cout << "Origin city: " << city_from << "\t";
    std::cout << "Destination city ID: " << city_to_id << "\t";
    std::cout << "Destination city: " << city_to << std::endl;
}


void display_flights(const std::vector<Flight>& Flights) 
{

    for (const auto& flight : Flights) 
    {
        flight.display();
    }
}


void Save_to_file(std::ofstream& logfile, const std::vector<Flight>& Flights)
{
    logfile << "fr.id" << "\t" << "to.id" << "\t" << "time" << "\t"
        << "car.id" << "\t" << "carrier.name" << "\t" << "ci.fr." << "\t"
        << "ci.to" << std::endl;

    for (const auto& flight : Flights) 
    {
        logfile << flight.city_from_id << "\t" << flight.city_to_id << "\t" << flight.time << "\t"
            << flight.carrier_id << "\t" << flight.carrier_name << "\t" << flight.city_from << "\t"
            << flight.city_to << std::endl;
    }
}


int main()
{
    std::ifstream datafile;
    datafile.open("data.csv");

    if (!datafile.is_open()) 
    {
        std::cout << "Unable to open data file\n";
        return 0;
    }

    std::ofstream logfile;
    logfile.open("logfile.txt");

    if (!logfile.is_open()) 
    {
        std::cout << "Unable to open data file\n";
        return 0;
    }

    std::vector<Flight> Flights;
    std::string csvline;

    while (getline(datafile, csvline))
    {
        std::stringstream inputString(csvline); 

        std::string tempString;
        int departures_performed;
        std::string carrier_name;
        std::string city_from;
        std::string city_to;
        double time, carrier_id, city_from_id, city_to_id;

        size_t add = 0;

        for (size_t idx = 0; idx < 2; ++idx) { getline(inputString, tempString, ','); }
        departures_performed = atoi(tempString.c_str());

        for (size_t idx = 0; idx < 8; ++idx) { getline(inputString, tempString, ','); }
        time = atof(tempString.c_str());

        for (size_t idx = 0; idx < 2; ++idx) { getline(inputString, tempString, ','); }
        carrier_id = atof(tempString.c_str());

        getline(inputString, carrier_name, ',');
        if (carrier_name[0] == '\"') 
        {
            carrier_name.erase(0, 1);
            add = 2;
        }

        for (size_t idx = 0; idx < 9 + add; ++idx) { getline(inputString, tempString, ','); }
        city_from_id = atof(tempString.c_str());
        getline(inputString, city_from, ',');

        for (size_t idx = 0; idx < 11; ++idx) { getline(inputString, tempString, ','); }
        city_to_id = atof(tempString.c_str());
        getline(inputString, city_to, ',');


        if (time > 0 && departures_performed != 0) 
        {
            Flight flight(time, carrier_id, carrier_name, city_from_id, city_from, city_to_id, city_to);
            Flights.push_back(flight);
        }
    }

    Save_to_file(logfile, Flights);

    datafile.close();
    logfile.close();
    return 0;
}