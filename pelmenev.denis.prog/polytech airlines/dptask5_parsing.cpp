#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


std::ifstream DATAFILE;
std::ofstream LOGFILE;


//номера необходимых параметров из каждой строки
std::vector <int> VALUES = {9, 11, 12, 21, 23, 32, 34};


class record {
public:
    std::vector <std::string> line;
};

//инициализация файлов
int init_file_system(const char sourse_file[])
{
    DATAFILE.open(sourse_file);

    LOGFILE.open("logfile.txt");
    
    if (!LOGFILE.is_open()) {
        std::cout << "Couldn't open logfile\n";
        return 0;
    }

    if (!DATAFILE.is_open()) {
        std::cout << "Couldn't open datafile\n";
        return 0;
    }

    return 1;
}

//возвращение строки в случае ковычек
std::string get_string_on_quote(std::string par_str, size_t &index)
{
    std::string str_fnl;

    do {
        str_fnl += par_str[index];
        index++;

        if (index == par_str.size()) return str_fnl;
    } while (par_str[index] != '"');

    str_fnl += par_str[index];

    if (par_str[index + 1] == '"') index++;

    index += 2;

    return str_fnl;
}

//возвращение строки от запятой до запятой
std::string get_string(std::string par_str, size_t &index)
{
    if (par_str[index] == '"') {
        if (par_str[index + 1] == '"') index++;

        return get_string_on_quote(par_str, index);
    }

    std::string str_fnl;

    while (par_str[index] != ',') {
        str_fnl += par_str[index];
        index++;

        if (index == par_str.size()) return str_fnl;
    }

    index++;

    return str_fnl;
}

//пропуск строки в случае ковычек
void skip_string_on_quote(std::string par_str, size_t &index)
{
    while ((par_str[index] != '"') && (index + 1 < par_str.size())) index++;

    if (par_str[index + 1] == '"') index++;

    index += 2;
}

//пропуск строки от запятой до запятой
void skip_string(std::string par_str, size_t &index)
{
    if (par_str[index] == '"') {
        index++;

        if (par_str[index] == '"') index++;

        skip_string_on_quote(par_str, index);

        return;
    }

    while (par_str[index] != ',' && (index + 1 < par_str.size())) index++;

    index++;
}

//проверка счётчика на соотвествие номерам нужных параметров
int check_counter(int counter)
{
    for (int idx = 0; idx < VALUES.size(); ++idx)
        if (counter == VALUES[idx]) return 1;
    
    return 0;
}

//запись строк в файл
void write_to_file(record string)
{
    for (size_t idx = 0; idx < string.line.size(); ++idx) {
        LOGFILE << string.line[idx];

        if (idx + 1 < string.line.size()) LOGFILE << ",";
    }

    LOGFILE << std::endl;

    /* for (size_t idx = 0; idx < string.line.size(); ++idx)         //DEBUG
        std::cout << string.line[idx] << " ";
    
    std::cout << std::endl; */
}

//формирование остальных строк
void form_string(std::string par_str, record &rec, size_t idx)
{
    int counter = 0;

    while (idx < par_str.size()) {
        if (counter == VALUES[VALUES.size() - 1]) {
            rec.line.push_back(get_string(par_str, idx));
            break;
        }

        if (check_counter(counter) == 1) {
            rec.line.push_back(get_string(par_str, idx));
            counter++;
        } else {
            skip_string(par_str, idx);
            counter++;
        }
    }
}


size_t air_time_index(std::string par_str)
{
    int counter = 0;
    size_t idx = 1;

    while (idx < par_str.size()) {
        if (counter < 9) {
            skip_string(par_str, idx);
            counter++;
        } else break;
    }

    return idx;
}

//основная функция, формирующая логфайл
void get_parameters()
{
    record rec;
    std::string csvline;

    while(!DATAFILE.eof()) {
        std::getline(DATAFILE, csvline);

        rec.line.clear();

        if(csvline[0] == 'A') {
            form_string(csvline, rec, 0);

            write_to_file(rec);

            continue;
        }

        if (csvline[1] == '0' || csvline[air_time_index(csvline)] == '0') continue;

        form_string(csvline, rec, 1);

        write_to_file(rec);
    }
}


int main()
{
    if (init_file_system("DATA_BASE.csv") == 0) {
        std::cout << "Error Exit" << std::endl;
        return 0;
    }

    get_parameters();

    DATAFILE.close();
    LOGFILE.close();

    return 0;
}
