/*
start project: 14/04/2024
tg/inst/git/vk - simeonidi03
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


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

int main(){

std::cout<<"start project: 14/04/2024\n";
    return 0;
}