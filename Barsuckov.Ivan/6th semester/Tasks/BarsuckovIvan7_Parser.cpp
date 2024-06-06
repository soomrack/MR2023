#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;  // to avoid using standard objects and functions without the std prefix


/* The function splits a string into substrings separated by a separator character, 
   and at the same time takes into account the presence of quotation marks.*/
vector<string> split(const string& s, char delimiter) {
    vector<string> cells;
    string cell;
    bool insideQuotes = false;  // it's used to track whether the current character is inside quotation marks.
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '"') {
            insideQuotes = !insideQuotes;
        }
        if (!insideQuotes && s[i] == delimiter) {
            cells.push_back(cell);
            cell.clear();
        }
        else {
            cell += s[i];
        }
    }
    cells.push_back(cell);
    return cells;  // returns a vector from the received substrings
}



/* Reading data from the "data.csv" file, 
   processing it and writing it to a new "parse.csv" file*/
int main() {
    
    // Opens the data.csv file for reading and the parsed.csv file for writing
    ifstream inputFile("data.csv"); //
    ofstream outputFile("parsed.csv");


    /* Checks that both files have opened successfully, 
       otherwise outputs an error and terminates the program*/
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    string line;

    getline(inputFile, line);

    // Reading each line of the "data.csv" file.
    while (getline(inputFile, line)) {
        vector<string> columns = split(line, ',');

        if (columns.size() == 36) {
            // The necessary values are extracted from the columns
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


    // Closes both files
    inputFile.close();
    outputFile.close();

    cout << "Parsing success" << endl;

    return 0;
}
