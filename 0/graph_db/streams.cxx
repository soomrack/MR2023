#include <iostream>
#include <fstream>
#include <string>

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
    
    std::string csvline;
    while(not datafile.eof()) {
        std::getline(datafile, csvline);

        logfile << "[log]," << csvline << std::endl;
        
        std::cout << csvline << '\n';
    }

    datafile.close();
    logfile.close();
    return 0;
}
