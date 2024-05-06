#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ifstream inputFile("T_T100_SEGMENT_ALL_CARRIER.csv");
    ofstream outputFile("parsed.csv");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    string line;
    
    getline(inputFile, line); // Read and ignore the header line

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
