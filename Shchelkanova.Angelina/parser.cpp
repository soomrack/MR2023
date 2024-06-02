#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
std::ifstream DATAFILE;
std::ofstream LOGFILE;

vector <int> VALUES = { 9, 11, 12, 21, 23, 32, 34 };

class record {
public: 
	vector <string> line;
};

//initializing files
int init_file_system(const char sourse_file[])
{
	DATAFILE.open(sourse_file);

	LOGFILE.open("logfile.txt");

	if (!LOGFILE.is_open()) {
		cout << "Couldn't open logfile\n";
		return 0;
	}

	if (!DATAFILE.is_open()) {
		cout << "Couldn't open datafile\n";
		return 0;
	}

	return 1;

}

//returning a string when quotation marks are detected
string get_string_quot(string par_str, size_t& index)
{
	string str_fnl;

	while (par_str[index] != '"') {
		str_fnl += par_str[index];
		index++;

		if (index == par_str.size()) return str_fnl;
	}

	str_fnl += par_str[index];

	if (par_str[index + 1] == '"') index++;

	index += 2;

	return str_fnl;
}

//returning a comma-to-comma string 
string get_string(string par_str, size_t& index)
{
	if (par_str[index] == '"') {
		if (par_str[index + 1] == '"') index++;

		return get_string_quot(par_str, index);
	}

	string str_fnl;

	while (par_str[index] != ',') {
		str_fnl += par_str[index];
		index++;

		if (index == par_str.size()) return str_fnl;
	}

	index++;

	return str_fnl;
}

//skipping string in case of quotation marks
void skip_string_quot(string par_str, size_t& index)
{
	while ((par_str[index] != '"') && (index + 1 < par_str.size())) index++;

	if (par_str[index + 1] == '"') index++;

	index += 2;
}

//skipping a comma-to-comma string
void skip_string(string par_str, size_t& index)
{
	if (par_str[index] == '"') {
		index++;

		if (par_str[index] == '"') index++;

		skip_string_quot(par_str, index);

		return;
	}

	while (par_str[index] != ',' && (index + 1 < par_str.size())) index++;

	index++;
}

//checking for compliance
int check(int counter)
{
	for (int i = 0; i < VALUES.size(); ++i)
		if (counter == VALUES[i]) return 1;

	return 0;
}

//writing file
void write(record string)
{
	for (size_t i = 0; i < string.line.size(); ++i) {
		LOGFILE << string.line[i];

		if (i + 1 < string.line.size()) LOGFILE << ",";
	}

	LOGFILE << endl;
}

//forming string
void form(string par_str, record& rec, size_t i)
{
	int counter = 0;

	while (i < par_str.size()) {
		if (counter == VALUES[VALUES.size() - 1]) {
			rec.line.push_back(get_string(par_str, i));
			break;
		}

		if (check(counter) == 1) {
			rec.line.push_back(get_string(par_str, i));
			counter++;
		}
		else {
			skip_string(par_str, i);
			counter++;
		}
	}
}

size_t air_time(string par_str)
{
	int counter = 0;
	size_t i = 1;

	while (i < par_str.size()) {
		if (counter < 9) {
			skip_string(par_str, i);
			counter++;
		}
		else break;
	}
	return i;
}

void get_parameters() 
{
	record rec;
	string csvline;

	while (!DATAFILE.eof()) {
		getline(DATAFILE, csvline);

		rec.line.clear();

		if (csvline[0] == 'A') {
			form(csvline, rec, 0);

			write(rec);

			continue;
		}

		if (csvline[1] == '0' || csvline[air_time(csvline)] == '0') continue;

		form(csvline, rec, 1);

		write(rec);
	}
}

int main()
{
	if (init_file_system("DATA_BASE.csv") == 0) {
		cout << "Error exit" << endl;
		return 0;
	}

	get_parameters();

	DATAFILE.close();
	LOGFILE.close();

	return 0;

}
