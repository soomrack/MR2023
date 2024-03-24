#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::ifstream DATAFILE;
std::ofstream LOGFILE;


//номера необходимых параметров из каждой строки
//DISTANCE, AIR_TIME, AIRLINE_ID, UNIQUE_CARRIER_NAME, ORIGIN_CITY_NAME,
//ORIGIN_STATE_NM, ORIGIN_COUNTRY_NAME, DEST_CITY_NAME, DEST_STATE_NM, DEST_COUNTRY_NAME
std::vector <int> VALUES = {7, 9, 11, 12, 23, 26, 28, 34, 37, 39};


class record {
public:
    std::vector <std::string> line;
};

//инициализация файлов
int init_file_system(const char sourse_file[])
{
    DATAFILE.open(sourse_file);

    LOGFILE.open("logfile.txt");
    
    if (not LOGFILE.is_open()) {
        std::cout << "Couldn't open logfile\n";
        return 0;
    }

    if (not DATAFILE.is_open()) {
        std::cout << "Couldn't open datafile\n";
        return 0;
    }

    return 1;
}

//возвращение строки в случае ковычек
std::string get_string_on_quote(std::string par_str, size_t &index)
{
    std::string str_fnl;

    while (par_str[index] != '"' || par_str[index + 1] != '"') {
        str_fnl += par_str[index];
        index++;

        if (index == par_str.size()) return str_fnl;
    }

    str_fnl += par_str[index];

    index += 3;

    return str_fnl;
}

//возвращение строки от запятой до запятой
std::string get_string(std::string par_str, size_t &index)
{
    if (par_str[index] == '"') {
        index++;

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
    while (par_str[index] != '"' || par_str[index + 1] != '"') {
        index++;

        if (index >= par_str.size()) return;
    }

    index += 3;
}

//пропуск строки от запятой до запятой
void skip_string(std::string par_str, size_t &index)
{
    if (par_str[index] == '"') {
        index++;

        skip_string_on_quote(par_str, index);

        return;
    }

    while (par_str[index] != ',') {
        index++;

        if (index >= par_str.size()) return;
    }

    index++;
}

//проверка счётчика на соотвествие номерам нужных параметров
int check_value(int counter)
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

    /* for (size_t idx = 0; idx < string.line.size(); ++idx)
        std::cout << string.line[idx] << " ";
    
    std::cout << std::endl; */
}

//формирование первой строки с описанием параметров
void form_head_string(std::string par_str, record &rec)
{
    int counter = 0;
    size_t idx = 0;

    while (idx < par_str.size()) {
        if (counter == VALUES[VALUES.size() - 1]) {
            rec.line.push_back(get_string(par_str, idx));
            break;
        }

        if (check_value(counter) == 1) {
            rec.line.push_back(get_string(par_str, idx));
            counter++;
        } else {
            skip_string(par_str, idx);
            counter++;
        }
    }
}

//формирование остальных строк
void form_string(std::string par_str, record &rec)
{
    int counter = 0;
    size_t idx = 1;

    while (idx < par_str.size()) {
        if (counter == VALUES[VALUES.size() - 1]) {
            rec.line.push_back(get_string(par_str, idx));
            break;
        }

        if (check_value(counter) == 1) {
            rec.line.push_back(get_string(par_str, idx));
            counter++;
        } else {
            skip_string(par_str, idx);
            counter++;
        }
    }
}

//основная функция, формирующая логфайл
void get_parameters()
{
    record rec;
    std::string csvline;

    while(not DATAFILE.eof()) {
        std::getline(DATAFILE, csvline);

        if (csvline[1] == '0') continue;

        rec.line.clear();

        if(csvline[0] == 'D') {
            form_head_string(csvline, rec);

            write_to_file(rec);

            continue;
        }

        form_string(csvline, rec);

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
