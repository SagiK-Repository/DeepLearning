#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <string>
#include <algorithm>

// nomal methods
float ConvertToFloat(const std::string& str);

// csv reader methods
bool IsOpenFile(std::ifstream& file);
std::vector<std::vector<float>> processCSV_vector(const std::string& filename, int first_column = 0, int second_column = 2);
std::vector<std::vector<float>> get_vector(const std::string& filename, int first_column = 0, int second_column = 2);
std::vector<float> get_row_vector(std::istringstream& iss, int first_column = 0, int second_column = 2);
template <int N>
std::array<std::array<float, 2>, N> processCSV_array(const std::string& filename, int first_column = 0, int second_column = 2);


// normal methods
float ConvertToFloat(const std::string& str) {
    std::string trimmedStr = str;
    trimmedStr.erase(std::remove(trimmedStr.begin(), trimmedStr.end(), ' '), trimmedStr.end());
    float result = std::stof(trimmedStr);
    return result;
}

// csv reader methods
bool IsOpenFile(std::ifstream& file) {
    if (file.is_open())
        return true;

    std::cout << "can't csv open file" << std::endl;
    return false;
}

std::vector<std::vector<float>> processCSV_vector(const std::string& filename, int first_column, int second_column) {
    std::ifstream file(filename);
     if (IsOpenFile(file) == false)
        return {};

    std::vector<std::vector<float>> matrix = get_vector(filename, first_column, second_column);
    matrix.erase(matrix.begin()); // 첫 번 데이터 제외

    file.close();

    return matrix;
}

std::vector<std::vector<float>> get_vector(const std::string& filename, int first_column, int second_column) {
    std::vector<std::vector<float>> result;
    std::string line;

    std::ifstream file(filename);
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<float> row = get_row_vector(iss);
        result.push_back(row);
    }

    return result;
}

std::vector<float> get_row_vector(std::istringstream& iss, int first_column, int second_column) {
    std::vector<float> row;
    std::string token;
    int count = 0;

    while (std::getline(iss, token, ',')) {
        if (count == first_column || count == second_column) {
            float tokenInt = ConvertToFloat(token);
            row.push_back(tokenInt);
        }
        if (count == second_column)
            break;
        count++;
    }

    return row;
}

template <int N>
std::array<std::array<float, 2>, N> processCSV_array(const std::string& filename, int first_column, int second_column) {
    std::array<std::array<float, 2>, N> result{};

    std::ifstream file(filename);
    if (IsOpenFile(file) == false)
        return result;

    std::string line;
    int row_index = 0;
    
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        int count = 0;
        
        while (std::getline(iss, token, ',')) {
            if (count == 0 || count == 2) {
                float tokenInt = ConvertToFloat(token);
                result[row_index][count / 2] = tokenInt;
            }
            count++;
        }
        
        row_index++;

        if (row_index >= N)
            break;
    }

    file.close();

    return result;
}