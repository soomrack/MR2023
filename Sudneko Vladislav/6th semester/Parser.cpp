#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> cells;
    std::string cell;
    bool insideQuotes = false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '"') {
            insideQuotes = !insideQuotes;
        }
        if (!insideQuotes && s[i] == delimiter) {
            cells.push_back(cell);
            cell.clear();
        } else {
            cell += s[i];
        }
    }
    cells.push_back(cell);
    return cells;
}



int main() {
    std::ifstream inputFile("data.csv");
    std::ofstream outputFile("parsed.csv");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    std::string line;
    
    std::getline(inputFile, line);

    while (std::getline(inputFile, line)) {
        std::vector<std::string> columns = split(line, ',');
            
        if (columns.size() == 36) {
            std::string originCityMarketID = columns[21];
            std::string destCityMarketID = columns[32];
            std::string airTime = columns[9];
            std::string airlineID = columns[11];
            std::string uniqueCarrierName = columns[12];
            std::string originCity = columns[23];
            std::string destCity = columns[34];
            if (originCityMarketID != "" && 
                destCityMarketID != "" &&
                airTime != "" && 
                airlineID != "" && 
                uniqueCarrierName != "" &&
                originCity != "" && 
                destCity != "") {

                outputFile << originCityMarketID << "," 
                           << destCityMarketID << "," 
                           << airTime << "," 
                           << airlineID << ","
                           << uniqueCarrierName << "," 
                           << originCity << "," 
                           << destCity << std::endl;    
            }
            
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Parsing success" << std::endl;

    return 0;
}
