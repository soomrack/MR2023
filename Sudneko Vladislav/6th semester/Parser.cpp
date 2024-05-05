#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &s, char delimiter) {
    vector<string> cells;
    string cell;
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
    ifstream inputFile("data.csv");
    ofstream outputFile("parsed.csv");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    string line;
    
    getline(inputFile, line);

    while (getline(inputFile, line)) {
        vector<string> columns = split(line, ',');
            
        if (columns.size() == 36) {
            string originCityMarketID = columns[21];
            string destCityMarketID = columns[32];
            string airTime = columns[9];
            string airlineID = columns[11];
            string uniqueCarrierName = columns[12];
            string originCity = columns[23];
            string destCity = columns[34];
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
                           << destCity << endl;    
            }
            
        }
    }

    inputFile.close();
    outputFile.close();

    cout << "Parsing success" << endl;

    return 0;
}
