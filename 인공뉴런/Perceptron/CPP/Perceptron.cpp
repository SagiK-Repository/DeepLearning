//     set     :      cd '/workspace/인공뉴런/Perceptron/CPP'
//   build     :      g++ ./Perceptron.cpp -o Perceptron_cpp
//     run     :      ./Perceptron_cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include "csvReader.h"
#include "getData.h"

// Main
int main() {
    // // Data Loading
    // std::string filename = "data.csv";
    // int seed = 1;
    // 
    // // =========== Vector =================
    // std::cout << "= Vector =" << std::endl;
    // std::vector<std::vector<float>> matrix = processCSV_vector(filename);
    // matrix.erase(matrix.begin()); // 첫 번 데이터는 x
    // 
    // 
    // // =========== Array ==================
    // std::cout << "= Array =" << std::endl;
    // std::array<std::array<float, 2>, 101> result = processCSV_array<101>(filename);
    // 
    // std::array<std::array<float, 2>, 100> newResult;
    // std::copy(result.begin() + 1, result.end(), newResult.begin()); // 첫 번 데이터는 x

    // Data Loading Test
    // std::cout << "10th value: " << matrix[99][0] << ", " << matrix[99][1] << std::endl;
    // std::cout << "10th value: " << result[100][0] << ", " << result[100][1] << std::endl;

    return 0;
}