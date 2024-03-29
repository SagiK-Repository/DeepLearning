// cd '/workspace/인공뉴런/Perceptron/CPP'
// g++ -std=c++11 -o Perceptron_Test Perceptron_Test.cpp
// ./Perceptron_Test

#define CATCH_CONFIG_MAIN
#include "../../../CPP Unit Test/catch.hpp"

#include "Perceptron.h"
#include "csvReader.h"

TEST_CASE("Perceptron_Vector", "[Perceptron_Vector]") {
    // Arrange
    std::string filename = "data.csv";
    std::vector<std::vector<float>> input_data = processCSV_vector(filename);
    IRandomeVector* randomVectorPtr = new Normal_Distribution_Vector_Class(2, 1);
    IPerceptron_Vector* perceptronvector = new Perceptron_Vector(randomVectorPtr, 0.1, 10);
    std::vector<float> result_data;
    for(int i = 0; i < input_data.size(); i++)
        result_data.push_back((i >= 50)?1:0);

    // Act
    perceptronvector->fit(input_data, result_data);

    // Assert
    std::vector<float> myVector = {4.5, 1};
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 5.0, 2 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 6.0, 2 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 7.0, 2 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 7.0, 5 };
    REQUIRE(perceptronvector->Predict(myVector) == 1);
    myVector = { 7.0, 6 };
    REQUIRE(perceptronvector->Predict(myVector) == 1);
    myVector = { 5.0, 4 };
    REQUIRE(perceptronvector->Predict(myVector) == 1);
}

TEST_CASE("Perceptron_Array", "[Perceptron_Array]") {
    // Arrange
    std::string filename = "data.csv";
    std::array<std::array<float, 2>, 100> input_data = processCSV_array<100>(filename);
    IRandomeArray<2>* randomArrayPtr = new Normal_Distribution_Array_Class<2>(1);
    IPerceptron_Array<100, 10, 2>* perceptronvector = new Perceptron_Array<100, 10, 2>(randomArrayPtr, 0.1, 10);
    std::array<float, 100> result_data;
    for (int i = 0; i < input_data.size(); i++)
        result_data[i] = ((i >= 50) ? 1 : 0);

    // Act
    perceptronvector->fit(input_data, result_data);

    // Assert
    std::array<float, 2> myArray = { 4.5, 1 };
    REQUIRE(perceptronvector->Predict(myArray) == 0);
    myArray = { 5.0, 2 };
    REQUIRE(perceptronvector->Predict(myArray) == 0);
    myArray = { 6.0, 2 };
    REQUIRE(perceptronvector->Predict(myArray) == 0);
    myArray = { 7.0, 2 };
    REQUIRE(perceptronvector->Predict(myArray) == 0);
    myArray = { 7.0, 5 };
    REQUIRE(perceptronvector->Predict(myArray) == 1);
    myArray = { 7.0, 6 };
    REQUIRE(perceptronvector->Predict(myArray) == 1);
    myArray = { 5.0, 4 };
    REQUIRE(perceptronvector->Predict(myArray) == 1);
}