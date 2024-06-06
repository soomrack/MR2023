#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &line, char delimiter) {
    vector<string> cells;
    string cell;
    bool inside_quotes = false;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '"') {
            inside_quotes = !inside_quotes;
        }
        if (!inside_quotes && line[i] == delimiter) {
            cells.push_back(cell);
            cell.clear();
        } else 
        {cell += line[i];}
    }
    cells.push_back(cell);//last string
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
            const string& originCityMarketID = columns[21];
            const string& destCityMarketID = columns[32];
            const string& airTime = columns[9];
            const string& airlineID = columns[11];
            const string& uniqueCarrierName = columns[12];
            const string& originCity = columns[23];
            const string& destCity= columns[34];
            if (!originCityMarketID.empty() && 
                !destCityMarketID.empty() &&
                !airTime.empty() && 
                !airlineID.empty() && 
                !uniqueCarrierName.empty() &&
                !originCity.empty() && 
                !destCity.empty()) {

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
