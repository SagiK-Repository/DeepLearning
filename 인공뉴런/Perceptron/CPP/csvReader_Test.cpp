// cd '/workspace/인공뉴런/Perceptron/CPP'
// g++ -std=c++11 -o csvReader_Test csvReader_Test.cpp
// ./csvReader_Test

#include "csvReader.h"

#define CATCH_CONFIG_MAIN
#include "/workspace/CPP Unit Test/catch.hpp"

TEST_CASE("Convert string to float", "[ConvertToFloat]") {
    REQUIRE(ConvertToFloat("0") == 0.0f);
    REQUIRE(ConvertToFloat("1.5") == 1.5f);
    REQUIRE(ConvertToFloat("150.55") == 150.55f);
}

TEST_CASE("Check Is Open File", "[IsOpenFile]") {
    // Arrange
    std::ifstream NoneFile("NoneFile");
    std::ifstream ExistFile("data.csv");

    // Act
    bool noneFileResult = IsOpenFile(NoneFile);
    bool existFileResult = IsOpenFile(ExistFile);

    // Assert
    REQUIRE(noneFileResult == false);
    REQUIRE(existFileResult == true);
}

TEST_CASE("CSV Vector Loading", "[processCSV_vector]") {
    // Arrange
    std::string filename = "data.csv";
    
    // Act
    std::vector<std::vector<float>> matrix = processCSV_vector(filename);

    // Assert
    REQUIRE(matrix[1][0] == 5.1f);
    REQUIRE(matrix[30][0] == 4.7f);
    REQUIRE(matrix[52][1] == 4.5f);
    REQUIRE(matrix[100][1] == 4.1f);
}

TEST_CASE("CSV Array Loading", "[processCSV_array]") {
    // Arrange
    std::string filename = "data.csv";
    
    // Act
    std::array<std::array<float, 2>, 101> array = processCSV_array<101>(filename);

    // Assert
    REQUIRE(array[1][0] == 5.1f);
    REQUIRE(array[30][0] == 4.7f);
    REQUIRE(array[52][1] == 4.5f);
    REQUIRE(array[100][1] == 4.1f);
}