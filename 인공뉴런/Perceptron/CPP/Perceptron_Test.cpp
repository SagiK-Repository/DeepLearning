// cd '/workspace/인공뉴런/Perceptron/CPP'
// g++ -std=c++11 -o Perceptron_Test Perceptron_Test.cpp
// ./Perceptron_Test

#define CATCH_CONFIG_MAIN
#include "/workspace/CPP Unit Test/catch.hpp"

#include "Perceptron.h"
#include "csvReader.h"
#include "getData.h"

TEST_CASE("Perceptron_Vector", "[Perceptron_Vector]") {
    // Arrange
    std::string filename = "data.csv";
    std::vector<std::vector<float>> input_data = processCSV_vector(filename);
    IRandomeVector* randomVectorPtr = new Normal_Distribution_Vector_Class(2, 1);
    IPerceptron_Vector* perceptronvector = new Perceptron_Vector(randomVectorPtr);
    std::vector<float> result_data;
    for(int i = 0; i < input_data.size(); i++)
        result_data.push_back((i >= 50)?1:0);
    std::vector<float> myVector = {1, 2};

    // Act
    perceptronvector.fit(input_data, result_data);

    // Assert
    REQUIRE(perceptronvector.Predict(myVector) == 1);
}